#include <linux/msg.h>
#include <sys/types.h>
#include<stdio.h>
#include<stdlib.h>
struct mymsgbuf
{
    long mtype;
    int request;
    double salary;
} msg;
int open_queue(key_t keyval)
{
    int qid;

    if ((qid = msgget(keyval, IPC_CREAT | 0660)) == -1)
    {
        return (-1);
    }
    return (qid);
}
int send_message(int qid, struct msg *qbuf)
{
    int result, length;
    length = sizeof(msg) - sizeof(long);
    if ((result = msgsnd(qid, qbuf, length, 0)) == -1)
    {
        return (-1);
    }
    return (result);
}
int read_message(int qid, long type, struct mymsgbuf *qbuf)
{
    int result, length;
    /* The length is essentially the size of the structure minus sizeof(mtype) */
    length = sizeof(struct mymsgbuf) - sizeof(long);
    if ((result = msgrcv(qid, qbuf, length, type, 0)) == -1)
    {
        return (-1);
    }

    return (result);
}
int peek_message(int qid, long type)
{
    int result, length;
    if ((result = msgrcv(qid, NULL, 0, type, IPC_NOWAIT)) == -1)
    {
        if (result== 1)
            return (1);
    }

    return (0);
}
main()
{
    int qid;
    key_t msgkey;

    msgkey = ftok(".", 'm');
    if ((qid = open_queue(msgkey)) == -1)
    {
        perror("open_queue");
        exit(1);
    }

    msg.mtype = 1;        /* Message type must be a positive number! */
    msg.request = 1;      /* Data element #1 */
    msg.salary = 1000.00; /* Data element #2 (my yearly salary!) */

    if ((send_message(qid, &msg)) == -1)
    {
        perror("send_message");
        exit(1);
    }
}