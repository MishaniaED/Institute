#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

double function(double x){
	return (4.0/(1+x*x));
}

double integr(double a, double b, int n){
	double s = (function(a) + function(b))/2;
	double h = (b-a)/n;
	for(int j = 1; j < n; j++)
		s += function(j*h + a);
	double res = h*s;
	return res;
}

int main(int argc, char **argv)
{
	if (argc < 3){
	  	perror("[ERROR]: wrong arguments!");
	  	exit(-1);
	  }	
	
	pid_t pid;
	int fifo[2];
	int i, parts, n;
	double curr_pi, pi=0, k, step;
	
	parts = atoi(argv[1]);  // кол-во процессов
	n = atoi(argv[2]);	// кол-во разбиений
	step = 1/n;		// шаг
	
	if(pipe(fifo) == -1){
		perror("[ERROR]: pipe!");
		exit(-1);
	}
	
	for(i=0;i<parts;i++){
		pid = fork();
		if(!pid){
			curr_pi = integr(i*(1.0/parts), (i+1)*(1.0/parts), n);
			close(fifo[0]);
			write(fifo[1], &curr_pi, sizeof(curr_pi));
			close(fifo[1]);
			exit(0);
		}
	}
	if(pid){
		double y=0;
		close(fifo[1]);
		while(read(fifo[0], &y, sizeof(y))){
			pi+=y;
			//cout<<"y = "<<y<<endl;
		}
		cout.precision(20);	
		cout<< pi <<endl;
		close(fifo[0]);
	}
	return 0;
}
