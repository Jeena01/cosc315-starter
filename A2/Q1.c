#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 50000000

void add_arrays(int* result, int* a, int* b, int array_size) {
    // @TODO
	// Add a + b together and store in the result array.
    // DO NOT create any local variables in this function.
    // +4
    while (array_size>0)
    {
        result[array_size-1]=a[array_size-1]+b[array_size-1];
        array_size=array_size-1;
    }

}

void rand_init(int* a, int array_size) {
    int range_start = 0;
    int range_end = 9;

    // @TODO
    // Randomly initialize an array of size array_size
    // using numbers between 0 and 9.
    // +2
    for (int i = 0; i < array_size; i++)
    {
        a[i]= range_start+ rand()%(range_end-range_start);
    }
    
}

int main(void) {
    // @TODO
	// Allocate the source arrays (a, b, c)
    // a and b are the source arrays.
    // c is the result storage array.
    // c[i] should equal a[i] + b[i]
    // Make sure to error check.
    // +1
    
    // @TODO
    // Initialize the two arrays, a and b, with random values 
    // of size ARRAY_SIZE and measure the time it takes to do so.
    // +1

    // @TODO
    // Print the total time for initialization
    // +1

    // @TODO
    // Run and time the add operation, print the first ten elements
    // of the result array, and print the total add time.
    // +2

    return 0;
}
