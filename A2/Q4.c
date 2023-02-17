#include <stdio.h> 
#include <stdlib.h>
#include <time.h>	//used for timing - see last lab.
#include <pthread.h>

#define ARRAY_SIZE 5000000

struct data {
  int* a;
  int start_idx;
  int* sum;
};
pthread_mutex_t lock; // Create
void* sum_array(void* arg) {
    struct data thread_data = *(struct data*) arg;

    // @TODO
    // Split the work of summing an input array.
    // HINT: Work should be split half-and-half. Use start_idx
    // to coordinate this.
    // HINT: Make sure to use a lock to synchronize work.
    // +5
    
    for (int i = 0; i < ARRAY_SIZE/2; i++)
    {
       pthread_mutex_lock(&lock);
      *thread_data.sum+=thread_data.a[thread_data.start_idx];
      pthread_mutex_unlock(&lock);
      thread_data.start_idx++;
    }
    
    pthread_exit(NULL);

}

int main(void) {
    // @TODO
    // Create and error check a lock
    // +2
    // Make sure to error check your lock
    if (pthread_mutex_init(&lock, NULL) != 0) {
    printf("Lock init failed\n");
    return 1;
  }

    // @TODO
    // Randomly initialize an array.
    // Make sure to error check.
    // +2
    int* a = malloc(ARRAY_SIZE*sizeof(int));
    if (a==NULL)
    {
      printf("Not enough memory.");
        exit(1);
    }
    int range_start = 0;
    int range_end = 9;
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        
        a[i]= range_start+ rand()%(range_end-range_start);
    }
  

    // @TODO
    // Create two pthreads and sum the contents of
    // the randomly initialized array. The time taken
    // and the sum should be recorded and printed.
    // HINT: Use the struct defined above.
    // HINT: Pass your sum variable as a pointer to
    // the threads.
    // +4
    int thread_sum=0;
    struct data d1;
    struct data d2;
    d1.a= a;
    d2.a= a;
    d1.sum=&thread_sum;
    d2.sum=&thread_sum;
    d1.start_idx=0;
    d2.start_idx=ARRAY_SIZE/2;

    clock_t t;
    t = clock();
    pthread_t p1;
    pthread_t p2;
    pthread_create(&p1,NULL,sum_array,&d1);
    pthread_create(&p2,NULL,sum_array,&d2);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_mutex_destroy(&lock);
    t=clock()-t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("\nThread sum: %d \n",thread_sum);
    printf("Total thread sum time: %.2f ms\n",(time_taken*1000));


    // @TODO
    // Without the use of threads, sum up the randomly initialized array,
    // time the operation, and print out the sum.
    // +2
    int serialsum=0;
    t = clock();

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
      serialsum+=a[i];
    }

    t=clock()-t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("Serial sum: %d\n",serialsum);
    printf("Total serial sum time: %.2f ms\n",(time_taken*1000));
    
    // @TODO
    // Check that your serial sum and threaded sum match.
    // If they don't, print an error message and exit (after freeing).
    // +1
    if(serialsum!=thread_sum){
      printf("ERROR: Summations do not match\n");
      free(a);
      exit(1);
    }

    // @TODO
    // Free the memory
    // +1
    free(a);
    return 0;
}
