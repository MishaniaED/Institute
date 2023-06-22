#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]){

	int i, j, m, n, p, s, counter = 0, flag = 0, k = 5;
	pid_t pid, cpid1, cpid2, cpid3, cpid4;
    int *pp;
    char name[BUFSIZ], command[BUFSIZ] = "pstree -p > ";

    pp = (int *)malloc(6 * sizeof(int));

    if(argc > 2){
        perror("[Error]: too much arguments");
        return -1;
    }
    if(argc == 2)
    {
        flag = 1;
        strcat(command, argv[1]);
    }
    else flag = 0;

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);

    pid = getpid();
    pp[0] = pid;
    printf("I am parent of all PIDs - %d\n\n", pid);
    for(i = 0; i < k; i++){ // 
            pid = fork();
            counter += 65;
            pp[i + 1] = pid;
            if(pid == 0){
                cpid1 = getpid();
                pp[0] = cpid1;
                for(j = 0; j < k - 1; j++){
                    cpid1 = fork();
                    pp[j + 1] = cpid1;
                    if(cpid1 == 0){
                            cpid2 = getpid();
                            pp[0] = cpid2;
                            for(m = 0; m < k - 2; m++){
                                cpid2 = fork();
                                pp[m + 1] = cpid2;
                                if(cpid2 == 0){
                                    cpid3 = getpid();
                                    pp[0] = cpid3;
                                    for(n = 0; n < k - 3; n++){
                                        cpid3 = fork();
                                        pp[n + 1] = cpid3;
                                        if(cpid3 == 0){
                                            cpid4 = getpid();
                                            pp[0] = cpid4;
                                            for(p = 0; p < k - 4; p++){
                                                    cpid4 = fork();
                                                    pp[p + 1] = cpid4;
                                                    if(cpid4 == 0){
                                                        sleep(10);
                                                        printf("<Parent %d>: ", pp[0]);
                                                        for(s = 1; s < 6; s++){
                                                                if(pp[s] != 0)
                                                                printf("<%d child %d> ", s, pp[s]);
                                                            }
                                                        printf("\n");
                                                        exit(0);
                                                    }
                                                }
                                                sleep(10);
                                                printf("<Parent %d>: ", pp[0]);
                                                for(s = 1; s < 6; s++){
                                                        if(pp[s] != 0)
                                                        	printf("<%d child %d> ", s, pp[s]);
                                                }
                                                printf("\n");
                                                exit(0);
                                        }
                                    }
                                    sleep(10);
                                    printf("<Parent %d>: ", pp[0]);
                                    for(s = 1; s < 6; s++){
                                            if(pp[s] != 0)
                                            printf("<%d child %d> ", s, pp[s]);
                            }
                            printf("\n");
                            exit (0);
                        }
                    }
                    sleep(10);
                    printf("<Parent %d>: ", pp[0]);
                    for(s = 1; s < 6; s++){
                            if(pp[s] != 0)
                            printf("<%d child %d> ", s, pp[s]);
                        }
                            printf("\n");
                            exit (0);
                }
            }
            sleep(10);
            printf("<Parent %d>: ", pp[0]);
            for(s = 1; s < 6; s++){
                if(pp[s] != 0)
                printf("<%d child %d>: ", s, pp[s]);
            }
                    printf("\n");
                    exit (0);
          }
    }
    printf("\n");
    sleep(2);
    if(flag){
        system(command);
        printf("Check result tree in '%s' file\n", argv[1]);
    }
    else system("pstree -p");

    printf("\n%s %d processes have been created!\n", name, counter);
    printf("<Parent %d> ", pp[0]);
    
    for(s = 1; s < 6; s++)
        if(pp[s] != 0)
           printf("<%d child %d> ", s, pp[s]);
  
    printf("\n");
	return 0;
}
