#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int range_start = 40;
    int range_end = 100;
    printf("Generating numbers from %d to %d\n", range_start, range_end);

    // 1. Get the number of ints to generate from the user
    printf("Enter how many numbers you wish to generate: ");
    int int_length;
    scanf("%d",&int_length);
    // 2. Malloc an int array and fill with random numbers
    // Randomly generated numbers should fall within the defined range
    int *a = malloc(int_length*sizeof(int));
    srand(time(NULL));
    for(int i = 0; i < int_length; ++i) {
     a[i]= range_start+ rand()%(range_end-range_start);
  }
  printf("Generated numbers: ");
    //3. Print generated numbers
    for(int i = 0; i < int_length; ++i) {
     printf("%d ",a[i]);
  }
    // 4. Malloc a char array and fill by casting numbers from the int array
    char *b=malloc(int_length*sizeof(char));
    for(int i = 0; i < int_length; ++i) {
     b[i]=(char)a[i];
  }
  printf("\nRandom letters: ");
    // 5. Print the random letters (HINT: use %s)
    for(int i = 0; i < int_length; ++i) {
     printf("%c ",b[i]);
  }

  printf("\n");
  free(a);
  free(b);
    return 0;
}