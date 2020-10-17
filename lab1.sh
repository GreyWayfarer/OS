#!/bin/bash
chmod +x lab1.sh
if [ $1 == "--help" -o $1 == "-h" ]
    then 
                echo "Авторы: Сидоров Андрей, Скребнев Антон"
        echo -e "\nДоступные аргументы: " 
        echo -e "\nВывод справки: --help | -h"
        echo "Примеры: ./lab1.sh --help | ./lab1.sh -h"
        echo -e "\nВывод сетевых интерфейсов: --output | -o"
        echo "Добавьте -n для вывода только имён интерфейсов"
        echo "Примеры: ./lab1.sh --output 1 lo| ./lab1.sh -o -n"
        echo -e "\nВключение сетевых интерфейсов: --up | -u"
        echo "2-ой аргумент- количество интерфейсов, которые необходимо включить, далее перечисление интерфейсов"
        echo "Примеры: ./lab1.sh --up 1 lo| ./lab1.sh -u 2 lo enp0s3"
        echo -e "\nВыключение сетевых интерфейсов: --down | -d"
        echo "2-ой аргумент- количество интерфейсов, которые необходимо выключить, далее перечисление интерфейсов"
        echo "Примеры: ./lab1.sh --down 1 lo| ./lab1.sh -d 2 lo enp0s3"
        echo -e "\nУстановка IP: --ip | -i"
        echo "Пример: ./lab1.sh -i lo 127.0.0.1"
        echo -e "\nУстановка mask: --mask | -m"
        echo "Пример: ./lab1.sh -m lo 255.255.255.0"
        echo -e "\nУстановка Gateway: --gateway | -g"
        echo "Пример: ./lab1.sh -g enp0s3 192.168.0.1"
fi
if [ $1 == "--output" -o $1 == "-o" ]
    then 
        if [ $2 == "--name" -o $2 == "-n" ]
            then 
                echo $2
                iface=$(ls /sys/class/net/)
                echo $iface
            else
                ip a
        fi
fi
if [ $1 == "--up" -o $1 == "-u" ]
    then
    N=$2
    for ((i=0 ; i<$N ; i++))
    do
    sudo ip link set dev $3 up
    echo "$3 up"
    shift
    done

fi
if [ $1 == "--down" -o $1 == "-d" ]
    then
    N=$2
    for ((i=0 ; i<$N ; i++))
    do
    sudo ip link set dev $3 down
    echo "$3 down"
    shift
    done
fi
if [ $1 == "--ip" -o $1 == "-i" ]
    then
    sudo ip a add $3 dev $2
fi
if [ $1 == "--mask" -o $1 == "-m" ]
    then
    sudo ifconfig $2 netmask $3
fi
if [ $1 == "--gateway" -o $1 == "-g" ]
    then
    sudo route add default gw $3 $2
fi
