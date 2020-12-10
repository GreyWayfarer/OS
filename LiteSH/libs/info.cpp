#include <iostream>
#include <fstream>

using namespace std;

extern "C" {
string info() {
                return "Авторы: Сидоров Андрей, Скребнев Антон\n"
                "--CreateProcess || -cp - Порождение процесса\n--CreateBackProcess || -cbp - Перевод процесса в фоновый режим"
                "--ReciveSignal || -rs - Получение сигнала от процесса\n";
}

}
int main() {
    return 0;
}
