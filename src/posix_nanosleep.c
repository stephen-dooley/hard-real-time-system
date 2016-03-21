#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
// nanosleep to delay process between successive calls to print out time
// uses timespec structure

int main(int argc, char** argv) {
  struct timespec curr_time1,curr_time2, sleeptime;
  //struct timezone tz;
  int i,delay,num_iter;
  double now1,now2,init;
  if (argc!=3) {
    fprintf(stderr, "Usage: %s <sleep time..msec><num_iterations>\n", argv[0]);
    exit(1);
  }

  // progname=argv[0];
  delay=atoi(argv[1]);
  num_iter=atoi(argv[2]);
  printf("Delay is %d msec ..num_iter is %d\n",delay,num_iter);

  // set up sleeptime struct
  sleeptime.tv_sec=0;

  while(delay>=1000) { // overflow if >=1sec
    sleeptime.tv_sec++;
    delay=delay-1000;
  }

  sleeptime.tv_nsec=delay*1000000;
  printf("Sleeptime struct is %d sec: %d nsec\n",sleeptime.tv_sec,sleeptime.tv_nsec);
  clock_gettime(CLOCK_REALTIME, &curr_time1);
  init=curr_time1.tv_sec + curr_time1.tv_nsec*0.000000001;

  for(i=0;i<num_iter;++i) {
    clock_gettime(CLOCK_REALTIME, &curr_time1);
    //now=curr_time.tv_sec + curr_time.tv_nsec*0.000000001;
    //prev=now;
    //wakeup=now+delay*0.001;
    nanosleep(&sleeptime,NULL);
    clock_gettime(CLOCK_REALTIME, &curr_time2);
    now1=curr_time1.tv_sec + curr_time1.tv_nsec*0.000000001;
    now2=curr_time2.tv_sec + curr_time2.tv_nsec*0.000000001;
    printf("Time is %ld : %ld..slept for %lf nsec\n",curr_time2.tv_sec,curr_time2.tv_nsec,(now2-now1)*1000000000);
  }

  printf("Total time taken : actual %lf msec theory(excl. runtime): %d msec\n",(now2-init)*1000,num_iter*atoi(argv[1]));

  return 0;
}
