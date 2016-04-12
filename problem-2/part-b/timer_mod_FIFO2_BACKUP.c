#include<stdio.h>
#include<time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sched.h>
int main(int argc, char** argv){
struct timeval tv;
struct timezone tz;
int i,delay,num_iter,run_id,k;
double init,start,stop;
double avg_delay[1000], sum, avg;

// FIFO stuff
int j;
struct sched_param my_sched_params;
int scheduler,prio;
// Start
// Set this process to highest priority FIFO
my_sched_params.sched_priority=sched_get_priority_max(SCHED_FIFO);
//printf("Max FIFO priority is %d \n",my_sched_params.sched_priority);
//j=sched_setscheduler(getpid(),SCHED_FIFO,&my_sched_params);
// Now check actual parameters

scheduler=sched_getscheduler(0); // 0 is shorthand for calling process ID
prio=sched_getparam(getpid(),&my_sched_params);
//printf("Scheduler is %d (0=TS, 1=FIFO, 2=RR)and priority is %d\n",scheduler,my_sched_params.sched_priority);
if (argc!=4) {
 fprintf(stderr, "Usage: %s <sleep time..msec><num_iter>\n", argv[0]);
 exit(1);
 }

// progname=argv[0];
 delay=atoi(argv[1]);
 num_iter=atoi(argv[2]);
// printf("Delay is %d..num_iter is%d\n",delay,num_iter);
 gettimeofday( &tv,&tz);
 init=tv.tv_sec + tv.tv_usec*0.000001;
 run_id=atoi(argv[3]);
 printf("%d,",run_id);
 printf("FIFO,");
 for(i=0;i<num_iter;++i)
 {
 gettimeofday( &tv,&tz);
 start=tv.tv_sec + tv.tv_usec*0.000001;
 // now sleep
 usleep(delay*1000);
 gettimeofday( &tv,&tz);
 stop=tv.tv_sec + tv.tv_usec*0.000001;
 avg_delay[i] = (stop-start)*1000;
// printf("%lf,",(stop - start)*1000);
// fprintf(f, "%lf\n", (stop-start)*1000);
 }
//printf("Total time taken : actual %lf theory(excl. runtime): %d, ms \n",(stop - init)*1000,num_iter*delay);

for(k=0;k<num_iter;++k) {
    sum+=avg_delay[k];
  }
  avg = sum/num_iter;
  printf("%lf,%lf,%d\n", avg, (stop-init)*1000, num_iter*delay);

return 0;
}
