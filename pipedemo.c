#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
    int pfds[2];
    int status = pipe(pfds);

    if (status == -1)
    {
        perror("Pipe Creation Error");
        exit(1);
    }
    pid_t pid = fork();

    if (pid == 0)
    {
        printf("\n Parent Process.");

        char msg1[20];
        printf("\n Parent reading ...");
        read(pfds[0], msg1, sizeof(msg1));
        printf("\n Message Received: %s \n ",msg1);
    }
    else
    {
        printf("\n Child Process.");

        char *msg = "PlzExit";
        printf("\n Child Writing .");
        write(pfds[1], msg, sizeof(msg));
        printf("\n Child written \n");
    }
}