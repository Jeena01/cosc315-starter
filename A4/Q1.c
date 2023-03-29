#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    // Implementation goes here.
    
    char* filename=argv[1];
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
    while(fscanf(f,"%d",&x)==1){

        d= x & (pow(2,m)-1);
        p=x >> m;
        printf("Virtual address %d is in page number %d and offset %d",x,p,d);

    }
}