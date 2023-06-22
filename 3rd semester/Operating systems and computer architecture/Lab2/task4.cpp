#include <iostream>
#include <dirent.h>
#include <string.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;


int main() {
    string file_path, link_dir;
    struct stat buff;
    time_t last_modif;
    cout<<"Cin file puth: ";
    cin >> file_path ;
    cout<<"Cin link directory: ";
    cin>> link_dir;
    
    symlink(file_path.c_str(), link_dir.c_str());
    FILE* link_file;
    link_file = fopen(link_dir.c_str(), "r");
    char c;
    cout<<endl;
    
    lstat(link_dir.c_str(), &buff);

    cout<<"Устройство: "<<buff.st_dev<<", inode: "<<buff.st_ino<<", режим доступа: "<<buff.st_mode<<", количество жестких ссылок: "<<buff.st_nlink<<", идентификатор пользователя-владельца: "<<buff.st_uid<<", идентификатор группы-владельца: "<<buff.st_gid<<", тип устройства: "<<buff.st_rdev<<", общий размер в байтах: "<<buff.st_size<<", размер блока ввода-вывода в файловой системе: "<<buff.st_blksize<<", количество выделенных блоков: "<<buff.st_blocks<<endl;
    last_modif = buff.st_atime;
    cout<<"время последнего доступа: "<<last_modif<<endl;
    last_modif = buff.st_mtime;
    cout<<"время последней модификации: "<<last_modif<<endl;
    last_modif = buff.st_ctime;
    cout<<"время последнего изменения: "<<last_modif<<endl;
    if ((buff.st_mode & S_IFMT) == S_IFLNK) cout<<"Является символической ссылкой"<<endl;
    
    fclose(link_file);
}
