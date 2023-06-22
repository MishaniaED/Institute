#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cmath>
#include <unistd.h>

using namespace std;

bool is_simple(int x){
	for (int i=2;i<=sqrt(x);i++){
		if (x%i==0) return false;
	}
	return true;
}

int search(int A, int B, vector <int> &ivector){
	if (B<2 && A<=B) return 0;
	if (A>B) return -1;
	int i;
	A >= 2 ? i = A : i = 2;
	for(i; i<=B;i++){
		if (is_simple(i)) ivector.push_back(i);
	}
	if (ivector.empty()) return 0;
	return 1;
}

int main()
{
    int client, server;
    int bufsize = 1024;
    int portNum = 1500;
    int counter = 0;
    int left_border;
    int right_border;
    int res;
    bool isExit = false;
    char* buffer = new char[bufsize];
    string str, strbuf1, strbuf2 = " ";
    vector <int> vec;

    struct sockaddr_in adr;
    socklen_t adr_len;
    pid_t pid;

    if ((client = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }

    cout << "\nSocket server has been created..." << endl;

    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = htons(INADDR_ANY);
    adr.sin_port = htons(portNum);

    if ((bind(client, (struct sockaddr*)&adr,sizeof(adr))) < 0) {
        cout << "\nError binding connection..." << endl;
        return -1;
    }

    adr_len = sizeof(adr);
    cout << "Looking for clients..." << endl;
    listen(client, 1);

    while ((server = accept(client,(struct sockaddr *)&adr,&adr_len)) > 0) { // пока есть соединение не прекращаем общение
        strcpy(buffer, "Server connected...\n");
        send(server, buffer, bufsize, 0);

        cout << "Client: ";
        counter = 0;
        do {
            recv(server, buffer, bufsize, 0); // получаем от клиента информацию
            //cout << buffer << endl;
            counter++;
            counter == 1? left_border = atoi(buffer) : right_border = atoi(buffer);
            if (*buffer == '#') isExit = true;
        } while (counter != 2 && *buffer != '#'); 
	
	
        do { 				// общаемся пока не введена команда стоп
	    //cout << "\nServer: "; 	// в буфер поместить простые числа из вектора
            res = search(left_border, right_border, vec);
            
            /*for(int i=0;i<vec.size();i++){
            	cout<<vec[i]<<" ";
            }*/
            
	    if (res == -1) strcpy(buffer, "Wrong borders. Left border bigger than right border");
	    else if(res == 0) strcpy(buffer, "There is not a single prime number in the given interval");
            else {
            	if (right_border - left_border > 1024){
			(right_border >= 2) && (right_border > left_border) ? bufsize = abs((right_border - left_border)*2) : bufsize = 1024;
			delete [] buffer;
			buffer = new char[bufsize];
		}
            	for(int i=0;i<vec.size();i++){
             		strbuf1 = to_string(vec[i]);
              		str = str + strbuf1 + strbuf2;
              	}
              	//if (str.lenght() >= 1024){
              		//while(str.lenght)
              	//}
            	strcpy(buffer, (char*)str.c_str());
            	str = "";
            }
             
            send(server, buffer, bufsize, 0); // отправляем информацию клиенту
            vec.clear();
            memset(buffer, 0, sizeof(buffer));

            cout << "Client: ";
            counter = 0;
            counter = 0;
            do {
           	 recv(server, buffer, bufsize, 0); // получаем от клиента информацию
           	 cout << buffer << " ";
           	 counter++;
           	 counter == 1? left_border = atoi(buffer) : right_border = atoi(buffer);
          	  if (*buffer == '#') isExit = true;
            } while (counter != 2 && *buffer != '#'); 
        } while (!isExit);

        cout << "\n=> Connection terminated... " << inet_ntoa(adr.sin_addr);
        close(server);
        cout << "\nGoodbye..." << endl;
        isExit = false;
        //break;
    }

    close(client);
    return 0;
}

