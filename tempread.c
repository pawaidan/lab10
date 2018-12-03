#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#define SIZE 100

int tempread(char *device, int verbose){
  
  FILE *fptr;
  char c[SIZE];
  char a[SIZE] = "/sys/bus/w1/devices/";
  char b[SIZE] = "/w1_slave";
  strcat(a,device);
  strcat(a,b);
  
  if( access( a, F_OK ) != -1 ) {

    fptr = fopen(a,"r");
    if(verbose == 1 ){
      printf("Open file pointer at directory: %s\n", a);
    }
  
    fseek(fptr,69,SEEK_SET);
    if(verbose == 1 ){
      printf("Seek to index 69\n");
    }
    
    fscanf(fptr,"%[^\n]", c);
    if(verbose == 1 ){
      printf("Scan for temperature: %s\n", c);
    }
    
    fclose(fptr);
    if(verbose == 1 ){
      printf("Close the file pointer\n");
    }
    
    printf("%s\n", c);
    
    return 0;
      
  } else {
    printf("file does not exists\n");
    return 1;
  }
}

int main(int argc, char **argv){
  
  int exitCode = 0;
  
  char *device = "28-01131bd2dd62";
  
   int verbose = 0;
   /* process the arguments */
   argc--; argv++;
  
   while(argc > 0) {
    
    /* printf("%d %s\n", argc, argv[0]); */
    
    if(!strcmp("-v", argv[0])) {
      verbose = 1;
      argc--;
      argv++;
      
      if(argc == 0){
        break;
      }
    } 
    
    if(!strcmp("-d", argv[0])) {
      argc--; argv++;
      if(argc == 0){
        printf("must have device serial after the -d \n");
        break;
      }else{
          device = argv[0];
          argc--; 
          
          if(argc == 0){
            break;
          }

          argv++;
        }
      }
   }
    
  exitCode = tempread(device, verbose);
  exit(exitCode);
}