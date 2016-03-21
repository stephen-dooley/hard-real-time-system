#include<stdio.h>
#include<time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  struct timeval tv;
  struct timezone tz;
  int i,iterations;
  double num,num2;
  double now,init;

  if (argc!=3) {
    fprintf(stderr, "Usage: %s <No of iterations><start num>\n", argv[0]);
    exit(1);
  }

  // progname=argv[0];
  iterations=atoi(argv[1]);
  num=atof(argv[2]);
  num2=num; // 2nd step
  printf("Iterations = %d, start num is %lf \n",iterations,num);

  gettimeofday(&tv,&tz);
  init=tv.tv_sec + tv.tv_usec*0.000001;

  for(i=0;i<iterations;++i) { num=num*0.5; }

  gettimeofday(&tv,&tz);
  now=tv.tv_sec + tv.tv_usec*0.000001;
  printf("Run time to multiply is %lf ms\n",(now-init)*1000);
  // Now divide .. use initial number .. num2
  gettimeofday( &tv,&tz);
  init=tv.tv_sec + tv.tv_usec*0.000001;

  for(i=0;i<iterations;++i) { num2=num2/2; }

  gettimeofday(&tv,&tz);
  now=tv.tv_sec + tv.tv_usec*0.000001;
  printf("Run time to divide is %lf ms\n",(now-init)*1000);

  return 0;
}
