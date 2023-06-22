#include <iostream>
#include <fstream>
#include <time.h>
#include <random>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h>

using namespace std;

#define KEY 44
#define SEMSIZE 2

union semun
{
    int                 val;
    semid_ds            *mbuf;
    ushort              *array;
    seminfo             *ibuf;
} arg;

int     main (int argc, char** argv)
{
    srand(time(NULL));
    long long int st_time = time(NULL);
    ushort arr[BUFSIZ];
    arg.array = arr;

    if(argc != 2)
    {
        perror("Arguments error");
        exit(-1);
    }
    ofstream file(argv[1]);
    if(!file.is_open())
    {
        perror("File error");
        exit(-2);
    }
    file.close();

    sembuf sopS[1] = {{1, 1, 0}};
    sembuf sopr1[2] = {{0, 1, 0}, {1, -1, IPC_NOWAIT}};
    sembuf sopr2[1] = {{1, 1, 0}};
    sembuf sopr3[1] = {{0, -1, 0}};
    sembuf sopw1[1] {{1, -1, IPC_NOWAIT}};
    sembuf sopw2[1] {{0, 0, 0}};
    sembuf sopw3[1] = {{1, 1, 0}};

    int sem_desk;

    if((sem_desk = semget(KEY, SEMSIZE, IPC_CREAT | 0777)) == -1)
    {
        perror("Semget error");
        exit(-3);
    }
    if(semop(sem_desk, sopS, 1) == -1)
    {
        perror("Semop error");
        exit(-4);
    }

    pid_t pid;
    int ppid = getpid();
    int k, id;
    long long int count;

    //20 processes for task(10 writers and 10 readers)
    for(int i = 0; i < 20; i++)
    {
        pid = fork();
        if(pid == -1)
        {
            perror("Fork");
            exit(-5);
        }
        else if(pid == 0)
        {
            k = i % 2;
            id = i / 2;
            count = 0;
            break;
        }
    }

    if(getpid() == ppid)
    {
        sleep(32);

        if (semctl(sem_desk, 0, IPC_RMID, 0) == -1)
        {
            perror("Semctl error");
            exit(-6);
        }
        return (0);
    }

    //writers and readers
    while((time(0) - st_time) < 30)
    {
        usleep(rand() % 10000 + 10000);
        if(k)
        {
            //Writer code
            if (semop(sem_desk, sopw1, 1) != -1) {
                semop(sem_desk, sopw2, 1);

                    ofstream File(argv[1], ios::app);
                    File << random() % 1000 << endl;
                    count++;
                    if(!File.is_open())
                    {
                        File.close();
                    }
                semop(sem_desk, sopw3, 1);
            }
        }
        else
        {
            //Reader code
            if (semop(sem_desk, sopr1, 2) != -1) {
                semop(sem_desk, sopr2, 1);

                ifstream File(argv[1], ios::app);
                char curr;
                while(File >> curr)
                {
                    if((curr - '0') == id)
                    {
                        count++;
                    }
                }
                if(!File.is_open())
                {
                    File.close();
                }
                semop(sem_desk, sopr3, 1);
            }
        }
    }
    cout << "I am " << ((k == 1) ? "Writer" : "Reader") << ", my PID = " << getpid() << ", count = "<< count << endl;
    return (0);
}