
CC := g++ -Wall -Werror
FLAGS := -std=c99
FLAG := -std=c11

.PHONY: all clean install uninstall rebuild

all: main

main: builds/main.o builds/LiteSH.o
	$(CC) builds/main.o builds/LiteSH.o -o main

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
