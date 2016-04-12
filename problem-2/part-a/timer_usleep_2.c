#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

int main(int argc, char** argv) {

  struct timeval tv;
  struct timezone tz;
  int i,j,delay,num_iter,run_id;
  double init,start,stop;
  double avg_delay[1000], sum, avg;

  if (argc!=4) {
    fprintf(stderr, "Usage: %s <sleep time..msec><num_iteration>\n", argv[0]);
    exit(0);
  }

  // progname=argv[0];
  delay=atoi(argv[1]);
  num_iter=atoi(argv[2]);
  run_id=atoi(argv[3]);
  gettimeofday(&tv,&tz);
  init=tv.tv_sec + tv.tv_usec*0.000001;
  printf("%d,",run_id);
  for(i=0;i<num_iter;++i) {
    gettimeofday(&tv,&tz);
    start=tv.tv_sec + tv.tv_usec*0.000001;
    // Now sleep
    usleep(delay*1000);
    gettimeofday(&tv,&tz);
    stop=tv.tv_sec + tv.tv_usec*0.000001;
    avg_delay[i] = (stop-start)*1000;
  }

  for(j=0;j<num_iter;++j) {
    sum+=avg_delay[j];
  }
  avg = sum/num_iter;
  printf("%lf,%lf,%d\n", avg, (stop-init)*1000, num_iter*delay);

  return 0;
}

