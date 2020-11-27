#ifndef H_FILE
#define H_FILE

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string>
#include <sys/stat.h>
#include <cstdlib>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <csignal>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace std;

int filemanager(string adr);
int createprocess(char *adr,int *pid,int *ppid);
int createbackprocess(char *adr,int *pid,int *ppid);

void sigHandler(int signo);
int recivesignal(char *);

#endif
