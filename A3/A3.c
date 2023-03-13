#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>	//used for timing - see last lab.
#include <pthread.h>
#include <semaphore.h>


pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int front=-1;
int rear=-1;
struct request* buffer;
int SIZE=6;
struct request
{
    int ID;
    int duration;
};
struct producer_info{
    int sleep_time;
    int max_duration;
};
struct consumer_info{
    int id;
};


void* producer(void* arg) {

    struct producer_info info = *(struct producer_info*) arg;
//change to get from arguments
int max_duration=info.max_duration;
int sleep_time=info.sleep_time;

//if full then wait
int request_id=1;

//if not full
while(1){
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

        struct request req={.ID=request_id, .duration=1+ rand()%max_duration};
        buffer[rear]=req;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        printf("Producer: produced request ID %d, duration %d seconds at time %.2f \n",req.ID,req.duration,((double)clock())/CLOCKS_PER_SEC*1000);
        request_id++;
        printf("Producer: sleeping for %d seconds\n",sleep_time);
        sleep(sleep_time);
        
}

}
void* consumer(void* arg){
    
    struct consumer_info info = *(struct consumer_info*) arg;
    while (1)
    {
        struct request req;
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        req=buffer[front];
        if(front==rear)
        {
            front=-1;
            rear=-1;
        }
        else if(front==SIZE-1){
            req=buffer[front];
            front=0;
        }
        else{
            front++;
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        printf("Consumer %d : assigned request ID %d, processing request for next %d seconds, current time is %.2f\n",info.id,req.ID,req.duration,((double)clock())/CLOCKS_PER_SEC*1000);
        sleep(3);
        printf("Consumer %d : completed request ID %d at time %.2f\n", info.id,req.ID,req.duration,((double)clock())*1000/CLOCKS_PER_SEC);
    }
    

}

int main(int argc,char* argv[]){
    if(argc!=4){
        printf("Wrong number of arguments. Exiting.");
        exit(1);
    }
    int num_servants=atoi(argv[1]);
    int max_duration=atoi(argv[2]);
    int sleep_time=atoi(argv[3]);
    printf("Number of servant threads will be: %d\n",num_servants);
    printf("Maximum duration of a request will be: %d\n",max_duration);
    printf("Time that the producer will sleep will be: %d\n",sleep_time);
    buffer=malloc(SIZE*sizeof(struct request));
    pthread_t master ,servant[num_servants];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,SIZE);
    sem_init(&full,0,0);
    struct producer_info pinfo={.max_duration=max_duration,.sleep_time=sleep_time};
    pthread_create(&master, NULL, (void *)producer, &pinfo);


    for (int i = 0; i <= num_servants; i++)
    {
        struct consumer_info cinfo={.id=i};
        pthread_create(&servant[i], NULL, (void *)consumer, &cinfo);
    }
    pthread_join(master, NULL);
    for(int i = 0; i < num_servants; i++) {
        pthread_join(servant[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    free(buffer);
    return 0;
    

}


