#include <iostream>
#include <dirent.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

int main()
{
	DIR* dir;
	int i = 0, l=0, tmp, last_modif[100];
	struct stat buff;
    struct dirent *ent;
    char c[100], names[100][20], chr[20];
	cin >> c;

    dir = opendir(c);

    if (dir)
    {
    	while ((ent = readdir(dir)) != NULL){
    		strncpy(names[i], ent->d_name, 20); 
    		cout<<names[i]<<" ";
    		stat(ent->d_name, &buff);
            last_modif[i] = buff.st_mtime;
    		cout<<last_modif[i]<<endl;
    		i++;
        }
		closedir(dir);
    }
    else { 
    	cout<<"Error";
    	exit(-1);
    }
    
    while (l < i) {
        if (l == 0 || last_modif[l - 1] <= last_modif[l])
            ++l;
        else {
            tmp = last_modif[l];
            last_modif[l] = last_modif[l - 1];
            last_modif[l - 1] = tmp;
            strcpy(chr, names[l]);
            strcpy(names[l], names[l - 1]);
            strcpy(names[l - 1], chr);
            --l;
        }}
    cout<<"Sorted:"<<endl;
    for(l=0;l<i;l++){
    	cout<<names[l]<<" ";
    	cout<<last_modif[l]<<endl;
    }
	return(0);
}
