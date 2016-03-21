#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include<unistd.h>
#include<sys/mman.h>

int main(int argc, char** argv){
  struct timeval tv;
  struct timezone tz;
  int i,j,index,iterations,array_size;
  float *arrayPtr;
  double stop,start,init;

  // Lock down all memory for this process
  if(mlockall(MCL_CURRENT|MCL_FUTURE)<0){
    fprintf(stderr,"Memlock error\n");
    exit(1);
  }

  if (argc!=3) {
    fprintf(stderr, "Usage: %s <Size of array><no of iterations>\n", argv[0]);
    exit(1);
  }

  // progname=argv[0];
  array_size=atoi(argv[1]);

  iterations=atoi(argv[2]);
  // Record start
  gettimeofday(&tv,&tz);
  init=tv.tv_sec + tv.tv_usec*0.000001;
  // create large float arrays
  arrayPtr=calloc(array_size,sizeof(float));

  //initialise array
  for(i=0;i<array_size;++i) { arrayPtr[i]=9999.99; }
  // Main loop
  // Process full array and time each pass.. Use random no
  // generator to access array randomly .. greater liklihood of paging in unlocked version

  for(j=0;j<iterations;++j) {
    gettimeofday(&tv,&tz);
    start=tv.tv_sec + tv.tv_usec*0.000001;
    // random seed
    srand(time(NULL));

    for(i=0;i<array_size;++i) {
      // generate random index
      index = rand() % array_size;
      arrayPtr[index]=arrayPtr[index]/0.9999;
    }

    gettimeofday(&tv,&tz);
    stop=tv.tv_sec + tv.tv_usec*0.000001;
    printf("Run time for pass %d is %lf ms\n",j+1, (stop-start)*1000);
    // sleep for 10 sec
    sleep(10); // Run multiple versions so unlocked versions may be paged during sleep period between passes
  }

  // release memory
  free(arrayPtr);
  munlockall(); // unlock memory
  gettimeofday(&tv,&tz);
  stop=tv.tv_sec + tv.tv_usec*0.000001;
  printf("Total Run time is %lf ms\n", (stop-init)*1000);

  return 0;
}
