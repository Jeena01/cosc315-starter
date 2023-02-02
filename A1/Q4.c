#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
//#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    // argv[1] gets us the path passed as an argument to
    // our executed program.
    char *filename = argv[1];
    int nums_to_read;

    // 1. Get how many numbers we want to read
    printf("How many numbers do you want to read: ");

    scanf("%d",&nums_to_read);
    // 2. Attempt to get the file descriptor for our file
    // HINT: Make sure to properly error check the output
    // from the system call.
    printf("Getting a file descriptor for %s\n", filename);
    int fd= open(filename, O_RDONLY);
    if (fd==-1)
    {
        perror("Error ");
        exit(1);
        /* code */
    }
    
    // 3. Attempt to read the file's contents
    // HINT: A calloc-made char array can be used as a buffer
    //      An example for a float array follows:
    //      float *a = (float *) calloc(num_of_floats, sizeof(float));

    // HINT: Make sure to properly error check the output from the
    // system call.

    printf("Reading up to %d numbers from the file\n", nums_to_read);
    char *a = (char *) calloc(nums_to_read, sizeof(char));
    int ba=read(fd,a,nums_to_read);
    if(ba<0){
        perror("Error ");
        exit(1);
    }
    else{
        printf("%d bytes read.\n",nums_to_read);
    }


    // 4. Check that the read content is an integer
    int x=(int)1;
    for (int i = 0; i < nums_to_read; i++)
    {
        if (!isdigit(a[i]))
        {
            x=0;
            break;
        }
        
    }
    printf("File contents: %s\n",a);
    
    // 5. Reverse and print the file content, if it is a number
     char *b = (char *) calloc(nums_to_read, sizeof(char));
    if (x==1)
    {
       
        for (int i = 0; i < nums_to_read; i++)
        {
            b[nums_to_read-i-1]=a[i];
        }
        printf("Reversed contents are: %s\n",b);
    }
    else{
        printf("They were not integers.\n");
        exit(1);
    }
    
    // 6. Free memory from calloc and close open file descriptors
    free(a);
    free(b);
    close(fd);
    return 0;
}