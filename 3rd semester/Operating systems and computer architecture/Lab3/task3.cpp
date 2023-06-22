/*
Пример ввода ./a.out -noc 3 1.txt
             ./a.out -oc 1.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <cstdlib>
#include <sys/wait.h>
#include <iostream>
#include <dirent.h>

using namespace std;

int main(int argc, char* argv[])
{
    
int i = 0, n = 0, pid, ppid, fact_base, fact = 1;
FILE* output, *tmp;
string pid_string, filename;
char buf [BUFSIZ], line [BUFSIZ];
DIR* d;
struct dirent *dir;


if (argc>5 || argc < 2) perror ("Wrong args");

char * flags_c = (char*)malloc(4*sizeof(char));
strcpy(flags_c,argv[1]);

int flags = strlen(argv[1]);

if ((flags_c[1] == 'n')||(flags_c[2] == 'n')||(flags_c[3] == 'n')){ // если указан ключ "-n"
    n = atoi(argv[2]);
    
    filename.assign(argv[3], strlen(argv[3]));
    for (i = 0; i < n; i++){
        pid = fork();
        sleep(1);
        if (pid == 0) break;
    }
}
else {   // Если не указан
    filename.assign(argv[2], strlen(argv[2])); // копируем argv[2] в filename
    pid = fork();
}

if (pid == 0){  // Ребенок
    if ((flags_c[1] == 'o')||(flags_c[2] == 'o')||(flags_c[3] == 'o')){ // Вывод в файл
        pid = getpid();
        fact_base = getpid() - getppid();
        //cout << pid1 <<endl;
        pid_string = to_string(pid);
        filename = filename + "." + pid_string;
        const char * filename_c = filename.c_str();             // конвертируем стринг в const char*, чтобы нормально открыть файл
        if(!(output = fopen(filename_c, "w"))){
        	printf("[ERROR]: Can't open file %d", pid);
        	exit (-1);
        }
        
        for (i = 1; i <= fact_base; i++)
            fact = fact*i;
            
        fprintf(output,"%s ",filename.c_str());
        fprintf(output," Mikhail (PPid: %d - Pid: %d) = %d", getppid(), getpid(), fact);
        fclose(output);
        
    }
    else // Вывод в консоль
    {
        pid = getpid();
        fact_base = getpid() - getppid();
        for (i = 1; i <= fact_base; i++)
        {
            fact = fact*i;
        }
        //sleep(1);
        cout << filename.c_str() << " "; 
        printf(" Mikhail (PPid(%d) - Pid(%d))! = %d\n", getppid(), getpid(), fact);
    }
    
}
else // Если родитель
{
    printf("PPID: %d\n", getpid());
    wait(0);
    sleep(3);
    if(!(output = fopen("output.txt", "w"))){ 
      printf("[ERROR] Can't open file %d", pid);
      exit (-2);
    }
    d = opendir("."); // открываем текущую деррикторию
    if (d){
            while ((dir = readdir(d)) != NULL){
                    {
                        strcpy(buf, dir->d_name); // В буфер записываем имя текущего файла
                        if (!strncmp(buf,filename.c_str(),strlen(filename.c_str()))){ 
                            if(!(tmp = fopen(buf, "r"))){ 
                               printf("Error to open file");
                               exit (-4);
                            }
                            fscanf(tmp,"%[^\n]",line); // считать все до первого "\n"
                            fprintf(output,"%s \n", line);
                            fclose(tmp);
                            if ((flags_c[1] == 'c')||(flags_c[2] == 'c')||(flags_c[3] == 'c')) // удаление промежуточных файлов
                                if(remove(buf) == -1) perror ("Remove Error"); 
                        }
                    }
                }
            closedir(d);
        }
    free(flags_c);
}
return 0;
}
