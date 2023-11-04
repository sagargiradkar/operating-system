/* Assignment No.2 B 
    Implement the C program in which main program accepts an array. Main program uses the FORK
system call to create a new process called a child process. Parent process sorts an array and passes
the sorted array to child process through the command line arguments of EXECVE system call. The
child process uses EXECVE system call to load new program which display array in reverse order.
*/


#include <stdio.h>
#include<stdlib.h>
 
void main(int argc, char *argv[])
{ 
    /* argv[0] is the program name */
     
    int *data = (int *) malloc((argc) * sizeof(int));
     
    printf("\n Argc:%d",argc);
    for(int i = 0;i < argc;i++) 
    {
        data[i] = atoi(argv[i]);
    }
 
    // Printing Element in Reverse
    printf("\n Printing Element in Reverse:");
    for(int i = argc-1; i>0;i--)
    {
        printf(" %d ",data[i]);
    }
     
    printf("\n\n EXCEV task Completed \n");
}
