#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

#define ARRAY_SIZE 500000

// The following is a struct in C.
// This paradigm allows for arbitrary data to be stored
// in a structured way. This also allows for multiple
// parameters to be passed to a thread function.
// You should use this struct with the add_arrays
// function when running using threads.
struct data {
  int* a;
  int* b;
  int* c;
  int start_idx; // Where the thread should start in an array
};

void* add_arrays(void* arg) {
	struct data thread_data = *(struct data*) arg;
    // Elements from the thread_data struct can be accessed here
    // Ex thread_data.a
    // @TODO
    // Split the work of c[i] = a[i] + b[i] between two threads.
    // HINT: Work should be split half-and-half. Use start_idx
    // to coordinate this.
    // +5
    for (int i = 0; i < ARRAY_SIZE/2; i++)
    {
        thread_data.c[thread_data.start_idx]=thread_data.a[thread_data.start_idx]+thread_data.b[thread_data.start_idx];
        thread_data.start_idx++;
    }
    
    pthread_exit(NULL);
}

void* rand_init(void* arg) {
    int range_start = 0;
    int range_end = 9;

    // @TODO
    // Fill an array with random variables using a thread.
    // Remember to use rand_r and not rand. You will also need to
    // change how the random seed is calculated such that it is unique
    // for each thread. For more details, see the assignment PDF or README.
    // HINT: The input parameter should be an array, not a struct.
    // +5

     int **val_p = (int **) arg;
     int* array = *val_p;
     int seed=time(NULL);
        seed += pthread_self()+ getpid();
     for (int i = 0; i < ARRAY_SIZE; i++)
    {
        
        //array[i]= range_start+ rand()%(range_end-range_start);
        array[i]= range_start+ rand_r(&seed)%(range_end-range_start);
    }

    pthread_exit(NULL);
}

int main(void) {
	// @TODO done
	// Allocate the source arrays (a, b, c)
    // a and b are the source arrays.
    // c is the result storage array.
    // c[i] should equal a[i] + b[i]
    // Make sure to error check.
    // +1
    int* a = malloc(ARRAY_SIZE*sizeof(int));
    int* b = malloc(ARRAY_SIZE*sizeof(int));
    int* c = malloc(ARRAY_SIZE*sizeof(int));
    
    if(a==NULL||b==NULL||c==NULL){
        printf("Not enough memory.");
        exit(1);
    }

    // @TODO
    // Create two pthreads and initialize a and b with
    // random numbers using both threads. The full operation
    // should be timed and the period printed.
    // +4

    
    clock_t t;

    t = clock();
    pthread_t p1;
    pthread_t p2;
    pthread_create(&p1,NULL,rand_init,&a);
    pthread_create(&p2,NULL,rand_init,&b);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    
    t=clock()-t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    
    printf("Total init time: %.2f ms\n",(time_taken*1000));
    // @TODO
    // Define and prepare two structs for each thread.
    // The structs should contain data relevent to the add operation.
    // +2
    
    struct data d1;
    struct data d2;
    d1.a= a;
    d2.a= a;
    d1.b=b;
    d2.b=b;
    d1.c=c;
    d2.c=c;
    d1.start_idx=0;
    d2.start_idx=ARRAY_SIZE/2;
    

    // @TODO
    // Reuse your pthreads from earlier and time your add_arrays function
    // as it runs on both threads.
    // +2
    t = clock();
    pthread_create(&p1,NULL,add_arrays,&d1);
    pthread_create(&p2,NULL,add_arrays,&d2);
    pthread_join(p2, NULL);
    pthread_join(p1, NULL);
    t=clock()-t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    // @TODO
    // Print out the first 10 elements of the result array and the final
    // period for the add_arrays threaded function runs.
    // +2    
    for (int i = 0; i < 10; i++) {     
        printf("%d ", c[i]);     
    }      
    printf("\nTotal add time: %.2fms \n",(time_taken*1000));

    // Free the memory
    // +1
    free(a);
    free(b);
    free(c);
    return 0;
}
