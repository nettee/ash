#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <memory.h>

#include <iostream>
#include <string>
#include <vector>

#include <readline/readline.h>
#include <readline/history.h>

using namespace std;

vector<char*> split(char *cmd) {
    static const char* sep = " ";
    vector<char *> tokens;
    char *token;
    token = strtok(cmd, sep);
    while (token != nullptr) {
        tokens.push_back(token);
        token = strtok(nullptr, sep);
    }
    tokens.push_back(nullptr);
    return tokens;
}

void ash_execute(char **args) {
    if (args[0] == nullptr) {
        return;
    }

    pid_t pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        execvp(args[0], args);
        // execvp returns only when an error occurs.
        perror("Ash");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        // Wait for the child to finish
        int status;
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

// Read a line from stdin, using readline lib.
char *rl_gets() {
    static char *line_read = nullptr;

    if (line_read) {
        free(line_read);
        line_read = nullptr;
    }

    line_read = readline("ash$ ");

    if (line_read && *line_read) {
        add_history(line_read);
    }
    return line_read;
}

void ash_loop() 
{
    char *cmd;

    while ((cmd = rl_gets())) {

        vector<char *> tokens = split(cmd);
        char **args = tokens.data();

        ash_execute(args);
    }

    // End of file
    cout << endl;
}

int main(int argc, char **argv) 
{

    ash_loop();

    return 0;
}
