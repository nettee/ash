#include <stdio.h>
#include <stdlib.h>

char *ash_read_line()
{
    while (1) {
        ;
    }
}

void ash_loop() 
{
    do {
        printf("ash$ ");
        char *line = ash_read_line();
        free(line);
    } while (1);
}

int main(int argc, char **argv) 
{

    ash_loop();

    return 0;
}
