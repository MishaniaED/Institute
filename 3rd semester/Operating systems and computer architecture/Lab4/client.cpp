#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

using namespace std;

#define SEMKEY 78
#define SHMKEY 87
#define SEMSIZE 2

union semun{
    int val;
    semid_ds *mbuf;
    ushort *array;
    seminfo *ibuf;
}arg;

int is_double(string str){
    char *error_code = nullptr;
    double value = strtod(str.c_str(), &error_code); // strtod, string -> double
    if(error_code == str.c_str() || *error_code != '\0')
    	return 0;
    return 1;
}

int is_operation(string str){
    if(str.length() != 1)
    	return 0;
    if(str[0] != '+' && str[0] != '-' && str[0] != '/' && str[0] != '*')
    	return 0;
    return 1;
}

int main(){
    shmid_ds sbuf;
    double *operand1, *operand2;
    char *operation, *error_code;
    string tmpd1, tmpd2, tmpc;
    char *shm_ptr;
    int shm_desk, flag;
    int sem_deskid;
    ushort arr[BUFSIZ];
    arg.array = arr;

    sembuf sop1[2] {{0, 0, 0}, {1, -1, 0}};
    sembuf sop2[2] {{0, 1, 0 | IPC_NOWAIT}, {1, 0, 0 | IPC_NOWAIT}};
    sembuf sop3[2] {{0, -1, 0}, {1, -1, 0}};
    sembuf sop4[2] {{0, 0, 0 | IPC_NOWAIT}, {1, 1, 0 | IPC_NOWAIT}};

    while(1){
        flag = 0;
        while(!flag){
            cout << "Enter expression(A <op> B): " << endl;
            cout << "Enter A: ";
            getline(cin, tmpd1);
            cout << "Enter <op>: ";
            getline(cin, tmpc);
            cout << "Enter B: ";
            getline(cin, tmpd2);

            if(tmpd1.empty()){
            	cout << "Input string is empty. Completing programm..." << endl;
            	return 0;
            }

            if(is_double(tmpd1) && is_operation(tmpc) && is_double(tmpd2)) flag = 1;
            if(!flag) cout << "Incorrect input!" << endl;
            	
        }
        if((shm_desk = shmget(SHMKEY, (sizeof(double) * SEMSIZE + sizeof(char)), 0777 | IPC_CREAT)) == -1){
            perror("Shmget error");
            exit(-1);
        }

        if((sem_deskid = semget(SEMKEY, SEMSIZE, 0777)) == -1){
            perror("Semget error");
            exit(-2);
        }
        if (semop(sem_deskid, sop1, 2) == -1){
            perror("Semop error");
            exit(-3);
        }
        if (shmctl(shm_desk, SHM_UNLOCK, &sbuf) == -1){
            perror("Shmctl error");
            exit(-4);
        }

        shm_ptr = (char*)shmat(shm_desk, 0, 0);
        if(shm_ptr == ((char*)-1)){
            perror("Shmat error");
            exit(-5);
        }
        operand1 = (double*)shm_ptr;
        operation = (char*)(operand1 + sizeof(double));
        operand2 = (double*)(operation + sizeof(char));

        *operand1 = stod(tmpd1);
        *operation = tmpc[0];
        *operand2 = stod(tmpd2);

        if(shmdt(shm_ptr) == -1){
            perror("Shmdt error");
            exit(-6);
        }
        if (shmctl(shm_desk, SHM_LOCK, &sbuf) == -1){
            perror("Shmctl error");
            exit(-7);
        }
        if (semop(sem_deskid, sop2, 2) == -1 || semop(sem_deskid, sop3, 2) == -1){
            perror("Semop error");
            exit(-8);
        }
        if (shmctl(shm_desk, SHM_UNLOCK, &sbuf) == -1){
            perror("Shmctl error");
            exit(-9);
        }
        shm_ptr = (char*)shmat(shm_desk, 0, 0);
        if(shm_ptr == ((char*)-1)){
            perror("Shmat error");
            exit(-10);
        }

        operand1 = (double*)shm_ptr;
        cout << "Result = " << *operand1 << endl;

        if(shmdt(operand1) == -1){
            perror("Shmdt error");
            exit(-11);
        }
        if (shmctl(shm_desk, SHM_LOCK, &sbuf) == -1){
            perror("Shmctl error");
            exit(-12);
        }
        if (semop(sem_deskid, sop4, 2) == -1){
            perror("Semop error");
            exit(-13);
        }
    }
}


