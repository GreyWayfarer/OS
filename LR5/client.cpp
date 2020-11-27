#include <iostream>
#include <arpa/inet.h>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(2019);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    int sock = socket(AF_INET,SOCK_STREAM,0);

    if (connect(sock, (struct  sockaddr*)&server, sizeof(server)) < 0) {
        cout << "Connection failed" << endl;
        return -1;
    } else {
        cout << "Connection ok" << endl;
    }
    int arg=htonl(argc-1);
    send(sock, (const char*)&arg, 4, 0);
    for (int i=1;i<argc;i++) {
        send(sock,argv[i],sizeof(argv[i]),0);
        sleep(1);
    }
    char buf[1024];
    recv(sock, buf, sizeof(buf),0);
    cout << "Server send: " << buf << endl;
    if(buf[0]=='p') {
        cin >> buf;
        send(sock, buf,sizeof(buf),0);
        recv(sock, buf, sizeof(buf),0);
        cout << "Server send: " << buf << endl;
    }
    
    close(sock);
}