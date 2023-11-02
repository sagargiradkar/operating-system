/*
Assignment No. 7:
Inter process communication in Linux using following.
A. FIFOS: Full duplex communication between two independent processes. First process accepts
sentences and writes on one pipe to be read by second process and second process counts number of
characters, number of words and number of lines in accepted sentences, writes this output in a text file
and writes the contents of the file on second pipe to be read by first process and displays onstandard
output.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int fd1,fd2;

	// FIFO file path
	char * FIFO1 = "FIFO1";
	char * FIFO2 = "FIFO2";
	

	// Creating the named file(FIFO)
	// mkfifo(<pathname>, <permission>)
	mkfifo(FIFO1, 0666);
	mkfifo(FIFO2, 0666);

	char arr1[80], arr2[80];
	while (1)
	{
		// Open FIFO for write only
		fd1 = open(FIFO1, O_WRONLY);

		// Take an input arr2ing from user.
		// 80 is maximum length
		fgets(arr2, 80, stdin);

		// Write the input arr2ing on FIFO
		// and close it
		write(fd1, arr2, strlen(arr2)+1);
		close(fd1);

		// Open FIFO for Read only
		fd2 = open(FIFO2, O_RDONLY);

		// Read from FIFO
		read(fd2, arr1, sizeof(arr1));

		// Print the read message
		printf("User2: %s\n", arr1);
		close(fd2);
	}
	return 0;
}

