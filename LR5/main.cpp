#include <iostream>
#include <cstring>
#include <dlfcn.h>
#include "LiteSH.hpp"

int main(int argc, char **argv) {
    
    string arg="";
    int pid,ppid,rez;
        struct sockaddr_in server, client;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int enable = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(2019);

    bind(sock, (struct sockaddr *) &server, sizeof(server));
    listen(sock, 5);
    while(1){
        int newsock, size;
        socklen_t clnlen;
        char otv[1024];
        string obuf="";
        int numh,num;
        newsock = accept(sock, (struct sockaddr*)&client, &clnlen);
        printf("New client: %s\n",inet_ntoa(client.sin_addr));
        while((size = recv(newsock, &numh, 4, 0)) != 0) {
            num = ntohl(numh);
            char buf[num][255];
            for (int i=0;i< num;i++) {
                recv(newsock,buf[i], 255*sizeof(char),0);
                sleep(1);
            }
                arg=(string)buf[0];
            if ((arg=="--CreateProcess") || (arg=="-cp")) {
                if (num != 2){
                    obuf="Неверное количество аргументов";
                    strcpy(otv,obuf.c_str());
                    break;
                }
                if ((rez=createprocess(buf[1],&pid,&ppid)) == 0){
                    strcpy(otv,"Процесс не создан");
                } else if(rez==1) {
                    obuf="Процесс создан!\npid = "+ to_string(pid) +"\nppid = " +to_string(ppid);
                    strcpy(otv,obuf.c_str());
                }

            } else if ((arg=="--CreateBackProcess") || (arg=="-cbp")) {
                if (num != 2) {
                    obuf="Неверное количество аргументов";
                    strcpy(otv,obuf.c_str());
                    break;
                }
                if ((rez=createbackprocess(buf[1],&pid,&ppid)) == 0) {
                    //cout << "Фоновый процесс не создан";
                    strcpy(otv,obuf.c_str());
                } else if(rez==1) {
                    obuf="Фоновый процесс создан!\npid = "+ to_string(pid) +"\nppid = " +to_string(ppid);
                    strcpy(otv,obuf.c_str());
                }
            } else if ((arg=="--ReciveSignal") || (arg=="-rs")) {
                if (num != 1) {
                    obuf="Неверное количество аргументов";
                    strcpy(otv,obuf.c_str());;
                    break;
                }
                obuf="pid = "+to_string(getpid())+"\nОжидать сигнала?";
                strcpy(otv,obuf.c_str());
                send(newsock, otv, sizeof(otv), 0);
                sleep(1);
                recv(newsock,otv,sizeof(otv),0);
                if (!recivesignal(otv)) {
                } else {
                    strcpy(otv,"Сигнал не получен!\n");
                }
            } else {
		char *err;
		void *handle = dlopen("./libs/libinfo.so", RTLD_LAZY);
		if (!handle) {
			fputs(dlerror(), stderr);
			exit(-1);
		}
		if ((err = dlerror()) != NULL ) {
			fprintf(stderr, "%s\n", err);
			exit(-1);
		}
		typedef string (*f_info)();
		f_info info = (f_info)dlsym(handle,"info");
		if ((err = dlerror()) != NULL) {
			fprintf (stderr, "%s\n", err);
			exit(-1);
		}
		obuf = info();
                strcpy(otv,obuf.c_str());
		dlclose(handle);
            }
             send(newsock, otv, sizeof(otv), 0);
        }
        close(newsock);

    }
    close(sock);

}

