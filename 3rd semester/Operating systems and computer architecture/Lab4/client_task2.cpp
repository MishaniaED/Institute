#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/ipc.h>
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

int main(){
	int a, b, c, d;
	int pid = getpid();
	mbuf mobj;
	//int len=0;
	
	cout<<"Client: my pid is "<<pid<<endl;
	
	while(1){
		cout<<"Enter ratio of cubic equation:\nEnter koef 'a': ";
		cin>>a;
		cout<<"\nEnter koef 'b': ";
		cin>>b;
		cout<<"\nEnter koef 'c': ";
		cin>>c;
		cout<<"\nEnter koef 'd': ";
		cin>>d;
		cout<<endl;
		
		int mqueueId = msgget(100, IPC_CREAT | 0666);
		//cout<<mqueueId;
		mobj.ratio[0] = a;
		mobj.ratio[1] = b;
		mobj.ratio[2] = c;
		mobj.ratio[3] = d;
		
		mobj.procpid = pid;
		mobj.mtype = 16;
		
		
		
		if (msgsnd(mqueueId, &mobj, MSGMAX, IPC_NOWAIT)) perror("msgsnd");
		
		sleep(1);
		if(msgrcv(mqueueId, &mobj, MSGMAX, pid, IPC_NOWAIT | MSG_NOERROR) > 0){
			for(int i=0;i<3;i++){
				if(mobj.ans[i].second_compl == 0.0)
					printf("x_%d = %.10lf\n", i, mobj.ans[i].first_compl); 
				else printf("x_%d = %.10lf + i*%.15lf\n", i, mobj.ans[i].first_compl, mobj.ans[i].second_compl); 
			}
			if(a == 0){printf("invalid a\n");}
		}
		break;
	}
	return 0;
}
