#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

char *myThreadFunP1t1()
{
    printf("please enter your student number: \n");
    long int std_number;
    scanf("%ld", &std_number);
    char *result;
    if(std_number % 2 == 0)
    {
        result = "number is even \n";
    }
    else
    {
        result = "number is odd \n";
    }
    return result;
}

void *myThreadFunP1t2(void *tid)
{
    fork();
    fork();
    printf("process id: %d   thread id: %ld\n",getpid(),gettid());
}

int idx=0, array[100];

void *myThreadFunP2t1(void *tid)
{
    int *myid = (int *)tid;
    while(idx<100)
    {
        array[idx++] = *myid;
    }
}

void *myThreadFunP2t2(void *tid)
{
    int *myid = (int *)tid;
    while(idx<100)
    {
        array[idx++] = *myid;
    }
}
  
int main()
{
    int r = fork();
    if(r>0)
    {
        pthread_t p1tid1;
        pthread_t p1tid2;
        
        pthread_create(&p1tid1, NULL, myThreadFunP1t1, NULL);
        pthread_create(&p1tid2, NULL, myThreadFunP1t2, (void *)&p1tid2);
        
        char *std_result;
        pthread_join(p1tid1, &std_result);
        printf("%s\n", std_result);
        pthread_join(p1tid2, NULL);
    }
    else if(r==0)
    {
        pthread_t p2tid1;
        pthread_t p2tid2;
        pthread_create(&p2tid1, NULL, myThreadFunP2t1, (void *)&p2tid1);
        pthread_create(&p2tid2, NULL, myThreadFunP2t2, (void *)&p2tid2);
        pthread_join(p2tid1, NULL);
        pthread_join(p2tid2, NULL);
        for(int i=0;i<100;i++)
            printf("%d\n",array[i]);
        printf("\n");
    }
    else
    {
        printf("error while create new process");
    }
    return 0;
}