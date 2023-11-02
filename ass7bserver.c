/*
Assignment No. 7:
Inter process communication in Linux using following.
B. Inter-process Communication using Shared Memory using System V. Application to demonstrate:
Client and Server Programs in which server process creates a shared memory segment and writes the
message to the shared memory segment. Client process reads the message from the shared memory
segment and displays it to the screen.
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXSIZE 27

void die(char *s)
{
    perror(s);
    exit(1);
}

int main()
{
    int shmid, retval;
    key_t key;
    char *shm, *s;

    key = 5678;

    if ((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)
        die("shmget");

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
        die("shmat");

    printf("Enter a string (up to 26 characters): ");
    if (fgets(shm, MAXSIZE, stdin) == NULL) {
        printf("Input error\n");
        exit(1);
    }

    /*
     * Wait until the other process
     * changes the first character of our memory
     * to '*', indicating that it has read what
     * we put there.
     */
    while (*shm != '*')
        sleep(1);
    retval = shmdt(shm);
    if (retval < 0)
    {
        printf("detachment failure");
        return 0;
    }

    exit(0);
}

