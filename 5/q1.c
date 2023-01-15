// Arman Heydari 97521252

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    int fd[2];

    int p = pipe(fd);
    if(p == -1){
        printf("pipe error!");
        exit(1);
    }
    
    pid = fork();
    if (pid == -1){
        perror("fork failed\n");
        exit(1);
    }
    
    else if (pid == 0) {
        // child process
        close(1);
        dup(fd[1]);
        close(fd[0]);
        execlp("ps", "ps", "-A", "-T", NULL); 
        exit(0);
    }
    
    else {
        // parent process
        close(0);
        dup(fd[0]);
        close(fd[1]);
        execlp("grep", "grep", "chrome", NULL);
    }
    return 0;
}
