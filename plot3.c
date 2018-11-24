#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <sys/time.h>
#define GNUPLOT "gnuplot -persist"
#define FILEPLOT
#define PI 3.1415926
#define SAMPLETIME 0.001
#define C1 "set xrange [0:50]\n"
#define C2 "set xrange [30:80]\n"
#define C3 "set xrange [60:110]\n"
#define C4 "set xrange [90:140]\n"
int main()
	{
	int i,j,k;
        double x,y,timenow,timep;
	struct timeval timestart,t1;
printf("1\n");

	FILE *gp,*fp;
printf("2\n");
        gp=popen(GNUPLOT,"w");
printf("3\n");
	fp=fopen("gnuplot.dat","w");
printf("4\n");
	gettimeofday(&timestart,NULL);
printf("5\n");
	
timep=0;
printf("6\n");
gp=popen(GNUPLOT,"w");
fprintf(gp,C1);
for(j=0;j<=100;j++)
{
 	k=13000*j;
	if(j==0)
	{
	for(i=0;i<=1000;i++)
	{

	x=0.01*i;
	y=sin(x);
	fprintf(fp,"%lf %lf\n",x,y);
	

	do
	{
		gettimeofday(&t1,NULL);
		timenow=t1.tv_sec-timestart.tv_sec+((double)t1.tv_usec-(double)timestart.tv_usec)/1000000;
	}while((timenow-timep)<SAMPLETIME);
		timep=timenow;
	}
	fprintf(gp, "plot  \"gnuplot.dat\" using 1:2 with lines title 'angle_b'\n");
	fflush(gp);
	}

	for(i=k;i<=13000+k;i++)
	{
        
		x=0.01*i;
		y=sin(x);
		fprintf(fp,"%lf %lf\n",x,y);
	

		do
		{

			gettimeofday(&t1,NULL);
			timenow=t1.tv_sec-timestart.tv_sec+((double)t1.tv_usec-(double)timestart.tv_usec)/1000000;
		}while((timenow-timep)<SAMPLETIME);
		timep=timenow;
		if(i%100==0)
		{ 
		fprintf(gp,"replot\n");	
		printf("7\n");
		//fflush(gp);

		fprintf(gp,"set xrange [%f:%f]\n",0.01*i-30,0.01*i+80);
		fflush(gp);
		}

		//printf("set xrange [%d:%d]\n",50*i,150*i);
               /*if(i>=4000&&i<=7000)
		{
		fprintf(gp,C2);
		printf(C2);
		}
		if(i>=7000&&i<=10000)
		{
		fprintf(gp,C3);
		}
		if(i>=10000&&i<=13000)
		{
		fprintf(gp,C4);
		}*/
	}
}
	fclose(gp);
	fclose(fp);
	return 0;
	}
# gnuplot
