#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<cstring>
using namespace std;

#ifndef MSGMAX
#define MSGMAX 1024
#endif

typedef struct{ // структура для учета компл корней
	double first_compl;
	double second_compl;
}Elem;

typedef struct{
	long mtype;
	int procpid;
	int ratio[4];
	Elem ans[3]; // макс 3 корня
}mbuf;

double servroot(double x){
	if(x < 0) return -pow(-x, 1.0/3.0);
	return pow(x, 1.0/3.0);
}

int Method_of_Kardan(double a, double b, double c, double d, Elem* x){ // вычисение корней методом Кордана
	if (a == 0){
		return -1;
	}
	
	double p = (3.0*a*c - b*b)/(3.0*a*a);
	double q = (2.0*b*b*b - 9.0*a*b*c + 27.0*a*a*d)/(27.0*a*a*a);
	double s = q*q/4.0 + p*p*p/27.0;
	
	double  f;
	if (q == 0)
		f = M_PI/2.0;
	else if(q < 0)
		f = atan(-2.0*sqrt(-s)/q);
	else f = atan(-2.0*sqrt(-s)/q) + M_PI;
	
	for(int i=0;i<3;i++){
		x[i].first_compl = x[i].second_compl = 0.0;
	}
	
	if (s<0){
		x[0].first_compl = 2.0*sqrt(-p/3.0)*cos(f/3.0) - b/(3.0*a);
		x[1].first_compl = 2.0*sqrt(-p/3.0)*cos(f/3.0 + 2.0*M_PI/3.0) - b/(3.0*a);
		x[2].first_compl = 2.0*sqrt(-p/3.0)*cos(f/3.0 + 4.0*M_PI/3.0) - b/(3.0*a);
	}
	else if(s == 0){
		x[0].first_compl = 2.0*servroot(-q/2.0) - b/(3.0*a);
		x[1].first_compl = -servroot(-q/2.0) - b/(3.0*a);
		x[2].first_compl = -servroot(-q/2.0) - b/(3.0*a);
	}
	else {
		double tmp1, tmp2;
		tmp1 = servroot(-q/2.0 + sqrt(s)) + servroot(-q/2.0 - sqrt(s));
		tmp2 = servroot(-q/2.0 + sqrt(s)) - servroot(-q/2.0 - sqrt(s));
		x[0].first_compl = tmp1 - b/(3.0*a);
		x[1].first_compl = -tmp1/2.0 - b/(3.0*a);
		x[1].second_compl = sqrt(3)*tmp2/2.0;
		x[2].first_compl = -tmp1/2.0 - b/(3.0*a);
		x[2].second_compl = -sqrt(3)*tmp2/2.0;
	}
	return 0;
}

int main(){
	mbuf mobj;
	Elem x[3];
	int pid = getpid();
	int res;
	cout<<"Server: my pid is " << pid<<endl;
	
	int mqueueId;
	if((mqueueId = msgget(100, IPC_CREAT | 0666)) == -1) // создали очередь и получили ее дескриптор
		{perror("msgget"); exit(-1);}
	//cout<<mqueueId;
	while(1){
		if((res = msgrcv(mqueueId, &mobj, MSGMAX, 16, IPC_NOWAIT | MSG_NOERROR)) > 0){
			//cout<<"Server: recived from client "<< mobj.ratio[0]<<endl;
			if (Method_of_Kardan(mobj.ratio[0], mobj.ratio[1], mobj.ratio[2], mobj.ratio[3], x) == -1){
				perror("Invalid 'a'\n");
				mobj.ans[0].first_compl = mobj.ans[0].second_compl = 0.0;
				mobj.ans[1].first_compl = mobj.ans[1].second_compl = 0.0;
				mobj.ans[2].first_compl = mobj.ans[2].second_compl = 0.0;
				mobj.mtype = mobj.procpid;
				if(msgsnd(mqueueId, &mobj, sizeof(mbuf), IPC_NOWAIT)) perror("msgsnd");
			}
			else {
				mobj.ans[0] = x[0];
				mobj.ans[1] = x[1];
				mobj.ans[2] = x[2];
				mobj.mtype = mobj.procpid;
				if(msgsnd(mqueueId, &mobj, sizeof(mbuf), IPC_NOWAIT)) perror("msgsnd");
			}
		}
		//else if(res != 0) {perror("msgrcv"); break;}
	}
	msgctl(mqueueId, IPC_RMID, 0);
	return 0;
}

