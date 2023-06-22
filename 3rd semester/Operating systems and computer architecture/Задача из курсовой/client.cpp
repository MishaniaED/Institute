#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main()
{
    char a;
    int client;
    int portNum = 1500;
    int bufsize = 1024;
    int counter = 0;
    int left_border;
    int right_border;
    char* buffer = new char[bufsize];
    bool isExit = false;
    char* ip = "127.0.0.1";

    struct sockaddr_in direc;

    if ((client = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "\nError creating socket..." << endl;
        exit(0);
    }

    cout << "\nSocket created successfully..." << endl;
    direc.sin_family = AF_INET;
    direc.sin_port = htons(portNum);
    inet_pton(AF_INET, ip, &direc.sin_addr);

    if (connect(client,(struct sockaddr *)&direc, sizeof(direc)) == 0)
        cout << "Connection to the server " << inet_ntoa(direc.sin_addr) << endl;

    cout << "Awaiting confirmation from the server..." << endl; //line 40
    recv(client, buffer, bufsize, 0);

    cout << "\n=> Enter # to terminate the connection\n" << endl;

    do {	
        cout << "Server: enter left and right border\nClient: ";
        counter = 0;
        do {
            memset(buffer, 0, sizeof(buffer));
            cin >> buffer;
            
            send(client, buffer, bufsize, 0); // отправляем серверу информацию
            counter++;
            counter == 1? left_border = atoi(buffer) : right_border = atoi(buffer);
            if (*buffer == '#') {
                isExit = true;
                break;
            }
        } while (counter != 2);
	
	if (right_border - left_border > 1024){
		(right_border >= 2) && (right_border > left_border) ? bufsize = abs((right_border - left_border)*2) : bufsize = 1024;
		delete [] buffer;
		buffer = new char[bufsize];
	}
        cout << "Server: ";
        recv(client, buffer, bufsize, 0);	// получаем от сервера информацию
        cout << buffer;
        if (*buffer == '#') isExit = true;
        cout << endl;

    } while (!isExit);
    cout << "=> Connection terminated.\nGoodbye\n";

    close(client);
    return 0;
}
