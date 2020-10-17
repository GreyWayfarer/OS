#include <iostream>
#include <cstring>
#include <dirent.h>
#include <fstream>

using namespace std;

int main(int argc, char **argv) {
    string arg="";
    if (argc>1)
        arg=(string)argv[1];
    if ((arg=="--ProcCont") || (arg=="-pc")) {
        if (argc == 2 ){
            DIR *dir;
            dir = opendir("/proc/");
            struct dirent *pDir;
            cout << "PID\t" << "Name" << endl;
            while ((pDir=readdir(dir))){
                if (isdigit(pDir->d_name[0]) != 0) {
                    char pp[1024];
                    snprintf(pp, sizeof pp, "/proc/%s/status",pDir->d_name);
                    ifstream pi;
                    pi.open(pp);
                    string pn, temp;
                    pi >> temp >> pn;
                    cout << pDir->d_name << "\t" << pn << endl;
                    pi.close();
                }
            }
            closedir(dir);
        } else {
            cout << "Неверное количество аргументов" << endl;
            return 0;
        }
    } else if ((arg=="--Move") || (arg=="-m")) {
        if (argc == 4 ){
            if (rename(argv[2], argv[3]) == -1)
                cout <<"Файл не может быть перемещён" << endl << endl;
        } else {
            cout << "Неверное количество аргументов" << endl;
            return 0;
        }
    } else if ((arg== "--Copy") || (arg== "-c")) {

        if (argc == 4 ){
            char cp[1024];
            if (!fopen(argv[2], "r")) {
                cout << "Файл отсутствует" << endl;
            } else { 
                snprintf(cp,sizeof cp, "cp %s %s",argv[2], argv[3]);
                popen(cp,"r");
            }
        } else {
            cout << stderr << "Неверное количество аргументов" << endl;
            return 0;
        }
    } else if ((arg=="--Delete") || (arg=="-d")) {
            if (argc == 3 ){
                if (remove(argv[2]) == -1)
                    cout << "Ошибка удаления файла" << endl;
        } else {
            cout << stderr << "Неверное количество аргументов" << endl;
            return 0;
        }
    } else if ((arg=="--Size") || (arg=="-s")) {
        if (argc == 3 ){
            char sf[1024];
            if (!fopen(argv[2], "r")) {
                cout << "Объект отсутствует" << endl;
            } else { 
                snprintf(sf,sizeof sf, "du -b -h %s",argv[2]);
                FILE *pp=popen(sf,"w");
                pclose(pp);
            } 
        } else {
            cout << stderr << "Неверное количество аргументов" << endl;
            return 0;
        }
    } else if ((arg=="--DirCont") || (arg=="-dc")) {
        if (argc == 3 ){
            DIR *d;
            struct dirent *entry;
            if (argv[2] == NULL) return 1;
            d = opendir(argv[2]);
            if (d == NULL) return 1;
            while ((entry = readdir(d)) != NULL) {
                if (strcmp(".", entry->d_name) || strcmp("..", entry->d_name)) 
                    printf("%s\n", entry->d_name);
            }
            closedir(d);  
                } else {
                    cout << stderr << "Неверное количество аргументов" << endl;
                    return 0;
                }
    } else {
        cout << "Авторы: Сидоров Андрей, Скребнев Антон" << endl
        << "Программа для управления файловой системой" << endl
        << "--Move || -m Name /builds/Name1 - Перемещение файла в нужную директорию" << endl
        << "--Copy || -c Name /builds/Name1 - Копирование файла в нужную директорию" << endl
        << "--Delete || -d Name - Удалить файл из текущей директории" << endl
        << "--Size || -s Name - Размер объекта" << endl
        << "--DirCont || -dc ./directoryName/ - Содержание директории" << endl
        << "--ProcCont || -pc - Отображение всех процессов из файловой системы procfs" << endl
        ;
    }
    return 0;
}
