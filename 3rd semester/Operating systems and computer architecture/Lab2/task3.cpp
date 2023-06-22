#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;




int main()
{
	cout<<"Cin puth to file: ";
	struct stat buff;
	string file_path, str;
	int i = 99, j=0;
	char c[100];
	cin>>file_path;
	//strcpy(c, file_path);
	ifstream file(file_path); 
	ofstream fout;
	
	if(!file.is_open()){
		cout<<"There is no such file\nNew file will be created";	
		fout.open(file_path);
 		if(!fout){
			cout<<"Error: file not ctreated";
			exit(-1);
		}
		
		cout<<"To stop enter: stop\nEnter text:\n";
		do {
			getline(cin, str);
			if (str == "stop")
				break;
			fout<<str<<endl;
		} while(1);
	
		fout.close();
		return 0;		
	}
	
 	file.close();
 		
 	cout<<"The file already existed.\nFile will be cleared and opened for writing. A new hard link will be created\n";
 	fout.open(file_path, ios_base::out | ios_base::trunc);
 	if(!fout){
		cout<<"Error: file not ctreated";
		exit(-1);
	}
	
	cout<<"To stop enter: stop\nEnter text:\n";
	do {
			getline(cin, str);
			if (str == "stop")
				break;
			fout<<str<<endl;
		} while(1);
	fout.close();	
	
	string file_name, ext, tmp, file_name_tmp, link_path;
    string dir_path = file_path; 
 
    while(dir_path.back() != '/' && dir_path.length()) { //находим путь к дирректории в которой лежит файл и обратную запись имени файла с расширением
        tmp.push_back(dir_path.back());
        dir_path.pop_back();
    }
    
    while(tmp.length()) {
        file_name.push_back(tmp.back()); //Записываем  имя файла с расширением в нормальном виде
        tmp.pop_back();
    }
    file_name_tmp = file_name;
    while(file_name_tmp.back() != '.' && file_name_tmp.length()) { //Разбиваем расширение файла и его имя с точкой
        ext.push_back(file_name_tmp.back());
        file_name_tmp.pop_back();
    }
    
    if(file_name_tmp.back() == '.') //удаляем точку до расширения
        file_name_tmp.pop_back();
	
    if(file_name_tmp.length()){ // Если длина имени файла не нулевая записываем его, иначе файл без расширения 
        file_name = file_name_tmp;
        reverse(ext.begin(), ext.end());
        }
    else
        ext.clear();

    int num = 0;
    link_path = dir_path + file_name + "." + to_string(num) + "." + ext;
    if(!ext.length()) // Если длина расширения нулевая удаляем из пути ссылки точку
            link_path.pop_back();
            
    FILE* link_file;
    /*if(!dir_path.length()) // если длина пути к дирректории нулевая добовляем .
        dir_path.push_back('.');*/
        
    link_file = fopen(dir_path.c_str(), "r");
    while(link_file) { //пока возможно открыть файл по жесткой ссылке прибавляем счетчик
        fclose(link_file);
        num++;
        link_path = dir_path + file_name + "." + to_string(num) + "." + ext;
        
        if(!ext.length()) // Если длина расширения нулевая удаляем из пути ссылки точку
            link_path.pop_back();

        link_file = fopen(link_path.c_str(), "r");
    }
    //stat(file_path, &buff);
    //cout<<"scale hard linfs before: "<<buff.st_nlink<<endl;
    link(file_path.c_str(), link_path.c_str());	
    //stat(file_path, &buff);
    //cout<<"after: "<<buff.st_nlink<<endl;
}
