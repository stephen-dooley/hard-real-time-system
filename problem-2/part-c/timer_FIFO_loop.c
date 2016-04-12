#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sched.h>
int main(int argc, char** argv){
struct timeval tv;
struct timezone tz;
int i,delay,num_iter,run_id,k;
 double init,start,stop,now;
 double avg_delay[1000], sum, avg;
// FIFO stuff
 int j;
 struct sched_param my_sched_params;
int scheduler,prio;
// Start
// Set this process to highest priority FIFO
my_sched_params.sched_priority=sched_get_priority_max(SCHED_FIFO);
j=sched_setscheduler(getpid(),SCHED_FIFO,&my_sched_params);
// Now check actual parameters

 scheduler=sched_getscheduler(0); // 0 is shorthand for calling process ID
prio=sched_getparam(getpid(),&my_sched_params);
if (argc!=3) {
 fprintf(stderr, "Usage: %s <sleep time..msec><num_iter>\n", argv[0]);
 exit(1);
 }
 
// progname=argv[0];
 delay=atoi(argv[1]);
 num_iter=atoi(argv[2]);
 gettimeofday( &tv,&tz);
 printf("%d,",run_id);
 printf("Loop,");
 init=tv.tv_sec + tv.tv_usec*0.000001;
 for(i=0;i<num_iter;++i)
 {
 gettimeofday( &tv,&tz);
 start=tv.tv_sec + tv.tv_usec*0.000001;
 // now loop continuously until time elapsed
 //usleep(delay*1000);
 stop = start + delay*0.001;
 do{
 gettimeofday( &tv,&tz);
 now=tv.tv_sec + tv.tv_usec*0.000001;
 }
 while (now<stop);
 avg_delay[i] = (stop-start)*1000;

}
 for(k=0;k<num_iter;++k)
  {
    sum+=avg_delay[k];
  }
 avg = sum/num_iter;
 printf("%lf,%lf,%d\n", avg, (stop-init)*1000, num_iter*delay);
return 0;
}
