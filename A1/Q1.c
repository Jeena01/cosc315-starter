#include <stdio.h>
#include <stdlib.h>

int main() {
    // 1. Get the number of inputs from the user
    printf("Enter how many numbers: ");
    int int_length;
    scanf("%d",&int_length);
    // 2. Read the number of inputs from the user
    // You will need to use an array to handle all of the inputs.
    // Basic array can be defined as such: int a[int_length]
    
    int *a = malloc(int_length*sizeof(int));
    printf("Enter the numbers: ");
    for(int i = 0; i < int_length; ++i) {
     scanf("%d", &a[i]);

  }

    // 3. Calculate the min, max, sum and average
    // Make sure to cast ints to floats for proper decimal output
    int min=a[0];
    int max=a[0];
    float sum=0;
    float average=0;
    for (int i = 0; i < int_length; i++)
    {
        if (min>a[i])
        {
            min=a[i];
        }
        if (max<a[i])
        {
            max=a[i];
        }
        sum=sum + a[i];
        
    }
    average=(float)sum / (float) int_length;
    printf("Min: %d Max: %d Sum: %d Average: %f \n",min,max,sum,average);
   free(a);

    // 4. Correctly print the stats

    return 0;
}