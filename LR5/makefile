CC := g++ -Wall -Werror
FLAGS := -std=c99
FLAG := -std=c11

.PHONY: all clean install uninstall rebuild

all: main client

client:	builds/client.o
	$(CC) builds/client.o -o client

main: builds/main.o builds/LiteSH.o
	$(CC) builds/main.o builds/LiteSH.o -I ~/OS/LR5/libs/libinfo.so -ldl -o main

builds/client.o: client.cpp
	$(CC) -c client.cpp -o builds/client.o

builds/main.o: main.cpp
	$(CC) -c main.cpp -o builds/main.o

builds/LiteSH.o: LiteSH.cpp
	$(CC) -c LiteSH.cpp -o builds/LiteSH.o

clean:
	find -name "*.o" -exec rm -rf {} +
	rm -rf ./bin/main

install:
	sudo cp ./bin/proc /usr/bin/main

uninstall:
	sudo rm -f /usr/bin/main

rebuild: clean all
