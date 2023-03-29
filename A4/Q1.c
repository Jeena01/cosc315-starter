#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    // Implementation goes here.
    
    char* filename=argv[1];
    printf("Reading file: %s\n",filename);
    FILE* f=fopen(filename,"r");
    if(f==NULL){
        printf("Invalid file.");
        exit(1);
    }
    unsigned int n=8;
    unsigned int m=8;
    unsigned int p;
    unsigned int d;
    unsigned int x;
    fscanf(f,"%d",&n);
    fscanf(f,"%d",&m);
    unsigned int mask= (1 << m )-1;
    int i=1;
    while(fscanf(f,"%d",&x)==1){

        d= x & mask;
        p=x >> m;
        printf("Virtual address v%d %d is in page number %d and offset %d\n",i++,x,p,d);

    }
    fclose(f);
    return (0);
}