/* Assignment No.2 A 

A. Implement the C program in which main program accepts the integers to be sorted. Main program
uses the FORK system call to create a new process called a child process. Parent process sorts the
integers using sorting algorithm and waits for child process using WAIT system call to sort the integers
using any sorting algorithm. Also demonstrate zombie and orphan states.
*/
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void childprocess(int n , int arr[]){
  //bubble sort  
  for(int i=0;i<n;i++){
    for(int j=i+1 ; j<n;j++){
      if(arr[i]>arr[j]){
         int temp=arr[i];
         arr[i]=arr[j];
         arr[j]=temp;
      }
   }
 }
}
 // Quick Sort function
void parentprocess(int arr[], int low, int high)
{
	 int pivot , temp , i ,j;
       if(low < high){
          pivot=low;
          i=low;
          j=high;
          while(i<j){
             while(arr[i]<=arr[pivot] && i<high){
                i++;
             }
             while(arr[j]>arr[pivot]){
                j--;
             }
             if(i<j){
               temp=arr[i];
               arr[i]=arr[j];
               arr[j]=temp;
             }
          }
          temp=arr[pivot];
          arr[pivot]=arr[j];
          arr[j]=temp;
          parentprocess(arr,low,j-1);
          parentprocess(arr,j+1,high);
       }
}

int main(void){
 
  int n;
  
  printf("Enter the Number of elements:\n");
  scanf("%d",&n);
  
  int arr[n];
  printf("Enter the Numbers:\n");
  for(int i=0;i<n;i++){
     scanf("%d",&arr[i]);
} 
  int p;
  p=fork();
  if(p==-1){
    printf("There is an error while calling fork()\n");
    }
  if(p==0){
    printf("We are in the child process (Bubble Sort) \n");
    printf("child  => PID:%d\n",getpid());
    printf("Parent => PID: %d\n", getppid());
    childprocess(n,arr);
    for(int i=0 ;i<n;i++){
    printf("%d\n",arr[i]);
   
  }
    }
  else{
     wait(NULL);
     printf("We are in the parent process (Quick sort)\n");
     printf("Parent => PID: %d\n", getpid());
     parentprocess(arr,0,n-1);
     for(int i=0 ;i<n;i++){
     printf("%d\n",arr[i]);
   
  }
 }
  
  return 0;
}



