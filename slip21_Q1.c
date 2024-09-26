#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{

 int pid = fork();
 if (pid > 0) {
 printf("I am Parent process\n");
 printf("ID : %d\n\n", getpid());
 }
 else if (pid == 0) {
 printf("I am Child process\n");

 printf("ID: %d\n", getpid());

 }
 else {
 printf("Failed to create child process");
 }
 return 0;
}
