#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main(int argc, char **argv)
{
  if (argc > 2 ){
  	cout<<"[ERROR]: wrong input!";
  	exit(-1);
  }	
  if (argc == 1){
  	cout<<argv[0]<<"\nNo arguments\n";
  	return 0;
  	}
  
  int counter = atoi(argv[1]);
  if (counter == 0){
   cout<<"You entered 0\n";
   return 0;
  }
  pid_t *pid = new pid_t [counter];
  
  cout<<"PARENT: PID -- "<< getpid()<<endl;
 
  for(int i=0;i<counter;i++){
  	switch(pid[i]=fork()) {
  	case -1:
      	    perror("fork"); // произошла ошибка
      	    exit(0); //выход из родительского процесса
  	case 0:
    	      cout<<"CHILD: Hello Mikhail\nCHILD: PID -- "<< getpid()<<endl;
     	     exit(0);
  	default:
    	      //cout<<"PARENT: Я жду, пока потомок не вызовет exit()...\n";
      	    wait(0);
 	}
  }
  delete [] pid;
  return 0;
}
