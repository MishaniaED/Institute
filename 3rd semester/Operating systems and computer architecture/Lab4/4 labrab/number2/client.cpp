#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

using namespace std;

#define SEMKEY 88
#define SHMKEY 97
#define SEMSIZE 2

union   semun
{
    int         val;
    semid_ds    *mbuf;
    ushort      *array;
    seminfo     *ibuf;
}arg;

bool    is_double(string str);
bool    is_operation(string str);

int             main ()
{
    ushort arr[BUFSIZ];
    arg.array = arr;

    sembuf sop1[2] {{0, 0, 0}, {1, -1, 0}};
    sembuf sop2[2] {{0, 1, 0 | IPC_NOWAIT}, {1, 0, 0 | IPC_NOWAIT}};
    sembuf sop3[2] {{0, -1, 0}, {1, -1, 0}};
    sembuf sop4[2] {{0, 0, 0 | IPC_NOWAIT}, {1, 1, 0 | IPC_NOWAIT}};

    shmid_ds sbuf;
    double *operand1, *operand2;
    char *operation, *error_code;
    string tmpd1, tmpd2, tmpc;
    char *shm_ptr;
    int shm_desk, passed = 0;

    while(!passed)
    {
        cout << "Enter expression(A <op> B): ";
        cin >> tmpd1 >> tmpc >> tmpd2;
        if(is_double(tmpd1) && is_operation(tmpc) && is_double(tmpd2))
            passed = 1;
        if(!passed)
            cout << "Incorrect input!" << endl;
    }
    if((shm_desk = shmget(SHMKEY, (sizeof(double) * 2 + sizeof(char)), 0777 | IPC_CREAT)) == -1)
    {
        perror("Shmget error");
        exit(-1);
    }

    int sem_desk;

    if((sem_desk = semget(SEMKEY, SEMSIZE, 0777)) == -1)
    {
        perror("Semget error");
        exit(-2);
    }
    if (semop(sem_desk, sop1, 2) == -1)
    {
        perror("Semop error");
        exit(-3);
    }
    if (shmctl(shm_desk, SHM_UNLOCK, &sbuf) == -1)
    {
        perror("Shmctl error");
        exit(-4);
    }

    shm_ptr = (char*)shmat(shm_desk, 0, 0);
    if(shm_ptr == ((char*)-1))
    {
        perror("Shmat error");
        exit(-5);
    }
    operand1 = (double*)shm_ptr;
    operation = (char*)(operand1 + sizeof(double));
    operand2 = (double*)(operation + sizeof(char));

    *operand1 = stod(tmpd1);
    *operation = tmpc[0];
    *operand2 = stod(tmpd2);

    if(shmdt(shm_ptr) == -1)
    {
        perror("Shmdt error");
        exit(-6);
    }
    if (shmctl(shm_desk, SHM_LOCK, &sbuf) == -1)
    {
        perror("Shmctl error");
        exit(-7);
    }
    if (semop(sem_desk, sop2, 2) == -1)
    {
        perror("Semop error");
        exit(-8);
    }
    if (semop(sem_desk, sop3, 2) == -1)
    {
        perror("Semop error");
        exit(-9);
    }
    if (shmctl(shm_desk, SHM_UNLOCK, &sbuf) == -1)
    {
        perror("Shmctl error");
        exit(-10);
    }
    shm_ptr = (char*)shmat(shm_desk, 0, 0);
    if(shm_ptr == ((char*)-1))
    {
        perror("Shmat error");
        exit(-11);
    }

    operand1 = (double*)shm_ptr;
    cout << "Result = " << *operand1 << endl;

    if(shmdt(operand1) == -1)
    {
        perror("Shmdt error");
        exit(-12);
    }
    if (shmctl(shm_desk, SHM_LOCK, &sbuf) == -1)
    {
        perror("Shmctl error");
        exit(-13);
    }
    if (semop(sem_desk, sop4, 2) == -1)
    {
        perror("Semop error");
        exit(-14);
    }
    return (0);
}

bool    is_double(string str)
{
    char *error_code = nullptr;
    double value = strtod(str.c_str(), &error_code);

        if(error_code == str.c_str() || *error_code != '\0')
                return (0);
    return (1);
}

bool    is_operation(string str)
{
    if(str.length() != 1)
                return (0);
    if(str[0] != '+' && str[0] != '-' && str[0] != '/' && str[0] != '*')
                return (0);
    return (1);
}