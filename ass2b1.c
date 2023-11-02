/* Assignment No.2 B 
    Implement the C program in which main program accepts an array. Main program uses the FORK
system call to create a new process called a child process. Parent process sorts an array and passes
the sorted array to child process through the command line arguments of EXECVE system call. The
child process uses EXECVE system call to load new program which display array in reverse order.
*/

#include<stdio.h> 
#include<stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h> 
void bubbleSort(int arr[],int n)
{
    printf("\n Sorting Started \n");
     
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-1;j++)
        {
            if(arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
     
    printf("\n\n Sorting Completed! \n"); 
    for(int i=0 ;i<n;i++){
     printf("%d\n",arr[i]);
  }  
}
 
// To Convert Integer to Char*
void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
  
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}
 
int main(int argc, char *argv[])
{
    printf("\n This is the main process: ");
    printf("\n Process Id: %d",getpid());
    printf("\n Parent Id: %d",getppid());
     
    int n;
  
    printf("\n Enter the Number of elements:\n");
    scanf("%d",&n);
  
    int arr[n];
    printf("Enter the Numbers:\n");
    for(int i=0;i<n;i++){
     scanf("%d",&arr[i]);
    } 
    printf("\n\n Sorting Array using Bubble Sort:");
    bubbleSort(arr,n);
 
 
    printf("\n Forking the current process:");
    pid_t cpid = fork();
    //The pid_t data type is a signed integer type which is capable of representing a process ID. 
 
 
    if(cpid > 0)//parent process
    {
        printf("\n\n Parent is Running:\n ParentID: %d \n It's ID: %d \n",getppid(),getpid());
 
        printf("\n Parent is waiting for child to Complete! \n\n");
         
        wait(NULL);
  
        printf("\n\n Parent is Exiting!!\n"); 
    }
    else if(cpid == 0)//child process
    {
        printf("\n\n Child is running:\n ParentID: %d \n It's ID: %d \n",getppid(),getpid());
 
        char *arrChar[n+1];
 
        //Creating Ascii Character Array to Pass as command line Argument
        arrChar[0] = (char *) "child";   // Arg 0 = name of executable file
        for(int i=0;i<n;i++)
        {
            char *string = (char *)malloc (sizeof(char) * (20));
            tostring(string,arr[i]);
            arrChar[i+1] = string;
        }
        arrChar[n+1] = NULL;
 
        printf("\n\n Child Calling EXECV System Call:\n");
        execv("./child",arrChar);
 
        printf("\n\n Child EXECV Call Complete\n");
        printf("\n\n Child Execution Complete \n");
    }   
    else if(cpid < 0)
    {
        printf("Error");
    }
}
