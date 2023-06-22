#include <stdio.h>
#include <iostream>
#include <dirent.h>
#include <cstring>
using namespace std;

int main()
{

        DIR* d;
        int iNum = 0;
        struct dirent *dir;
        char c[100];
		cin >> c;

        d = opendir(c);

        if (d)
        {
                while ((dir = readdir(d)) != NULL)
                {
                        if(dir->d_type != DT_DIR)
                        	cout << dir->d_name << endl;
                }
                closedir(d);
        }

        return(0);
}

