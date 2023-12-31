#include <iostream>
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

int     main ()
{
    ushort arr[BUFSIZ];
    arg.array = arr;

    sembuf sopS[1] = {{1, 1, 0}};
    sembuf sop1[2] {{0, -1, 0}, {1, 0, 0}};
    sembuf sop2[2] {{0, 0, 0 | IPC_NOWAIT}, {1, 0, 0 | IPC_NOWAIT}};
    sembuf sop3[2] {{0, 1, 0 | IPC_NOWAIT}, {1, 1, 0 | IPC_NOWAIT}};

    shmid_ds sbuf;
    double *operand1, *operand2;
    char *operation, *shm_ptr;
    int shm_desk;

    if((shm_desk = shmget(SHMKEY, (sizeof(double) * 2 + sizeof(char)), 0777)) != -1)
    {
        if (shmctl(shm_desk, IPC_RMID, &sbuf) == -1)
        {
            perror("Shmctl error");
            exit(-1);
        }
    }
    if((shm_desk = shmget(SHMKEY, (sizeof(double) * 2 + sizeof(char)), 0777 | IPC_CREAT)) == -1)
    {
        perror("Shmget error");
        exit(-2);
    }
    if(shmctl(shm_desk, SHM_LOCK, &sbuf) == -1)
    {
        perror("Shmctl error");
        exit(-3);
    }

    int sem_desk;
    if((sem_desk = semget(SEMKEY, SEMSIZE, 0777)) != -1)
    {
        if(semctl(sem_desk, 0, IPC_RMID, 0) == -1)
        {
            perror("Semctl error");
            exit(-4);
        }
    }
    if((sem_desk = semget(SEMKEY, SEMSIZE, IPC_CREAT | 0777)) == -1)
    {
        perror("Semget error");
        exit(-5);
    }
    if(semop(sem_desk, sopS, 1) == -1)
    {
        perror("Semop error");
        exit(-6);
    }
    while(1)
    {
        if(semop(sem_desk, sop1, 2) == -1)
        {
            perror("Semop fail");
            exit(-7);
        }
        shm_ptr = (char*)shmat(shm_desk, 0, 0);
        if(shm_ptr == ((char*)-1))
        {
            perror("Shmat error");
            exit(-8);
        }

        operand1 = (double*)shm_ptr;
        operation = (char*)(operand1 + sizeof(double));
        operand2 = (double*)(operation + sizeof(char));

        if(*operation == '+')
            *operand1 = *operand1 + *operand2;
        else if(*operation == '-')
            *operand1 = *operand1 - *operand2;
        else if(*operation == '*')
            *operand1 = *operand1 * *operand2;
        else if(*operation == '/')
            *operand1 = *operand1 / *operand2;

        if(shmdt(shm_ptr) == -1)
        {
            perror("Shmdt error");
            exit(-9);
        }
        if (semop(sem_desk, sop2, 2) == -1)
        {
            perror("Semop error");
            exit(-10);
        }
        if (semop(sem_desk, sop3, 2) == -1)
        {
            perror("Semop error");
            exit(-12);
        }
        sleep(1);
    }
    return (0);
}