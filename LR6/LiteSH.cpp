#include "LiteSH.hpp"

int filemanager(string adr) {
    string str;
    int status;
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        cout << "Введите аргумент: ";
        getline(cin,str);
        execl(adr.c_str(), adr.c_str(), str.c_str(), NULL);
        _exit (EXIT_FAILURE);
    } else if (pid < 0)
        status = -1;
    else if (waitpid (pid, &status, 0) != pid)
        status = -1;

    return status;
}

int createprocess(char *adr,int *pid,int *ppid) {
    int rez;
    pid_t pidt;
    pidt = fork();
    if (pidt==-1){
        return 0;
    } else if (pidt == 0) {
        *pid=getpid();
        *ppid=getppid();
        execlp(adr, adr, NULL);
        return 1;
    } else{
        wait(&rez);
    }
    return -1;
}

int createbackprocess(char *adr,int *pid,int *ppid) {
    int rez;
    pid_t pidt;
    pidt = fork();
    if (pidt==-1){
        return 0;
    } else if (pidt == 0) {
        setsid();
        *pid=getpid();
        *ppid=getppid();
        chdir("/");
        execl(adr, adr, NULL);
        wait(&rez);
        return 1;
    }
    return -1;
}
void sigHandler(int signo) {
    cout << "Сигнал "<< signo <<" получен" << endl;
}
int recivesignal(char *yes) {
    if (strcmp(yes,"YES")==0) {
        signal(SIGABRT , sigHandler);
        sleep(20);
        return 0;
    }
    return 1;
}