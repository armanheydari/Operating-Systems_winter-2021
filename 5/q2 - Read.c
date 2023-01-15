#include <stdio.h>
#include <string.h>
#include <q2-linkedlist.h>

#define SHM_KEY 0x1234
#define ENCRYPT_KEY 10

void decrypt(char str[]) {
    for (int i=0; str[i] != '\0' && i<1000; i++) {
        str[i] = str[i] + ENCRYPT_KEY;
    }
}

int main(int argc, char *argv[])
{
    char array[*argv[1]][1000];
    int shmid;
    shmid = shmget(SHM_KEY, argv[1], 0644|IPC_CREAT);
    if (shmid == -1) {
        perror("Shared memory!");
        return 1;
    }
    
	char *shmptr[*argv[1]][1000];    
	shmptr = shmat(shmid, NULL, 0);
    if (shmptr == (void *) -1) {
        perror("Shared memory attach!");
        return 1;
    }
	for(int i=0;i<*argv[1];i++) {
		for(int j=0; j<1000 && j!='\0'; j++)
			printf("%s", *shmptr[i][j]);
	}
    
    for (int i = 0; i<*argv[1]; i++) {
		decrypt(*shmptr[i]);
	}

    return 0;
}
