#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<string.h>
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
    key_t key = 1324;
    int msgid = msgget(key, IPC_CREAT | 0666);
    char msg[MSG_SIZE];
    msgp.mtype = 1;
    char endmsg[] = "end";
    for (; 1; )
    {
        printf("\n Enter Msg: ");
        fgets(msg, MSG_SIZE, stdin);
        printf("\n Entered msg is : %s",msg);
        strcpy(msgp.mtext, msg);
        printf("%d",strcmp(msg,endmsg));
        if(strcmp(msg,endmsg)!=10)
        {
            msgsnd(msgid, (void *)&msgp, MSG_SIZE, IPC_NOWAIT);
            printf("\n Sent Msg: %s",msg);
        }
        else
            break;
    }
    printf("\n Done with MsgSend");
}