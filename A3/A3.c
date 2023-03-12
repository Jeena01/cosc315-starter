#include <stdio.h> 
#include <stdlib.h>
#include <time.h>	//used for timing - see last lab.
#include <pthread.h>
#include <semaphore.h>

#define SIZE 10

Mutex mutex;
sem_t empty=SIZE;
sem_t full=0;
int front=-1;
int rear=-1;
struct request buffer[SIZE];
struct request
{
    int ID;
    int duration;
};

int main(){
    int num_servants=10;
    pthread_t master ,servant[num_servants];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,SIZE);
    sem_init(&full,0,0);
    pthread_create(&master, NULL, (void *)producer, NULL);
    for (int i = 0; i < num_servants; i++)
    {
        pthread_create(&servant[i], NULL, (void *)consumer, NULL);
    }
    pthread_join(master, NULL);
    for(int i = 0; i < num_servants; i++) {
        pthread_join(servant[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
    

}

void* producer(void* arg) {

//change to get from arguments
int max_duration=5;
int sleep_time=3;


//if full then wait
int request_id=1;

//if not full
while(true){
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    if(front==-1){
        front=0;
        rear=0;
    }
    else if(rear==SIZE-1&&front!=0){
        rear=0;
        }
    else{
        rear++;
        }
        //make request
        struct request req={.ID=request_id, .duration=(rand()%max_duration)};
        buffer[rear]=req;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        printf("Producer made request id %d",request_id);
        request_id++;
        sleep(sleep_time);
        

}

}

void* consumer(void* arg){
    int consumer_id=0;

    while (true)
    {
        struct request req;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        req=buffer[front];
        if(front==rear)
        {
            front=-1;
            rear=-1;
        }
        else if(front==size-1){
            req=buffer[front];
            front=0;
        }
        else{
            front++;
        }
        printf("Consumer completed request %d",req.ID);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(req.duration);
    }
    

}