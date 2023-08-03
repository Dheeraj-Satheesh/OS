#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/types.h>

#define MSG_SIZE 100

struct mymsg1
{
    long mtype;
    char mtext[MSG_SIZE];
};
int main()
{
    struct mymsg1 msgp;
    long msgtype = 0;

    key_t key = 1324;
    int msgid = msgget(key, IPC_CREAT | 0666);

    if (msgid==-1)
    {
        perror("MSGGET Error");
        exit(1);
    }

    int size = msgrcv(msgid, (void *)&msgp, MSG_SIZE, msgtype, IPC_NOWAIT);

    printf("\n Received msg is : \n");
    printf("%s:", msgp.mtext);

    //msgctl(msgid, IPC_RMID, (void *)&msgp);
}
