#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

int main(int argc, char** argv) {

  struct timeval tv;
  struct timezone tz;
  int i,delay,num_iter;
  double init,start,stop;

  if (argc!=3) {
    fprintf(stderr, "Usage: %s <sleep time..msec><num_iteration>\n", argv[0]);
    exit(0);
  }

  // progname=argv[0];
  delay=atoi(argv[1]);
  num_iter=atoi(argv[2]);
  printf("Delay is %d..num_iter is %d\n",delay,num_iter);
  gettimeofday( &tv,&tz);
  init=tv.tv_sec + tv.tv_usec*0.000001;

  for(i=0;i<num_iter;++i) {
    gettimeofday( &tv,&tz);
    start=tv.tv_sec + tv.tv_usec*0.000001;
    // Now sleep
    usleep(delay*1000);
    gettimeofday( &tv,&tz);
    stop=tv.tv_sec + tv.tv_usec*0.000001;
    printf("Time is %ld : %ld..slept for %lf ms\n",tv.tv_sec,tv.tv_usec,(stop-start)*1000);
  }
  printf("Total time taken : actual %lf theory(excl. runtime): %d, ms \n",(stop)*1000,num_iter*delay);

  return 0;
}

