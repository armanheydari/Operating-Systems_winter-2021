#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;
typedef struct semaphore semaphore, *pno;

struct semaphore
{
        int value;

        pno (*wait)(semaphore *);
        pno (*post)(semaphore *);
};

pno semaphore_wait(semaphore *self) {
    self->value -= 1;
	while (self->value <= 0) {
        pthread_mutex_lock(&lock);
    }
}

pno semaphore_post(semaphore *self) {
    self->value += 1;
    if (self->value > 0) {
        pthread_mutex_unlock(&lock);
    }
}

int main()
{
    semaphore example = {.value = 3};
    example.wait = semaphore_wait;
    example.post = semaphore_post;
    example.wait(&example);
    example.wait(&example);
    example.wait(&example);
    example.wait(&example);
    example.post(&example);
    example.post(&example);
    printf("%d", example.value);
    return 0;
}
