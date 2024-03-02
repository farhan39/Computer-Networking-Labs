//Farhan Bukhari------BCS-5F-----21L-5247
//Q1 and Q2

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main ()
{
	char c[100];
	int fd = open("input_file.txt", O_RDONLY);
	int fd1 = open("numbers.txt", O_WRONLY || O_CREAT);
	
	//Following loop does task 1(a) and task(b)
	
	while (read(fd, c, 1))
	{	
		printf("%s", c);
		
		if (c[0] >= 48 && c[0] <= 57)
			write(fd1, c, 1);
	}
	
	close(fd);
	close(fd1);
	
	return 0;
}
