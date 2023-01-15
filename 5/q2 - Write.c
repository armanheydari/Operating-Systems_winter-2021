#include <stdio.h>
#include <string.h>
#include <q2-linkedlist.h>
#include "boost/filesystem.hpp"

#define SHM_KEY 0x1234
#define ENCRYPT_KEY 10

void encrypt(char str[]) {
    for (int i=0; str[i] != '\0' && i<1000; i++) {
        str[i] = str[i] + ENCRYPT_KEY;
    }
}

void listdir(char buf[])
{
    FILE *proc = popen("/bin/ls -al","r");
	while ( !feof(proc) && fgets(buf,sizeof(buf),proc) )
	{
	}
}

int main(int argc, char *argv[])
{
    char *shmptr[*argv[1]][1000];
    int shmid;
    shmid = shmget(SHM_KEY, argv[1], 0644|IPC_CREAT);
    if (shmid == -1) {
        perror("Shared memory!");
        return 1;
    }
    
    shmptr = shmat(shmid, NULL, 0);
    if (shmptr == (void *) -1) {
        perror("Shared memory attach!");
        return 1;
    }
    
	for (int i = 0; i<*argv[1]; i++) {
		listdir(*shmptr[i]);
	}
	
	for (int i = 0; i<*argv[1]; i++) {
		encrypt(*shmptr[i]);
	}

    return 0;
}
