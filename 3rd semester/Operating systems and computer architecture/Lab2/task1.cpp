#include <iostream>
#include <dirent.h>
#include <cstring>
#include <sys/stat.h>
using namespace std;

int main()
{
        DIR* dir;
        int time;
        struct dirent *ent;
        struct stat buf;
        char c[100];
		cin >> c;

        dir = opendir(c);

        if (dir)
        {
                while ((ent = readdir(dir)) != NULL)
                {                 
                				stat(ent->d_name, &buf);
                				time = buf.st_mtime;
                                cout << ent->d_name <<" "<<time<< endl;
                }
                closedir(dir);
        }
        else { 
    		cout<<"Error";
    		exit(-1);
    	}
        return(0);
}
