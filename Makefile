CC := g++ -Wall -Werror
FLAGS := -std=c99
FLAG := -std=c11

.PHONY: all clean install uninstall rebuild

all: LiteSH/bin/main LiteSH/bin/client

client:	LiteSH/builds/client.o
	$(CC) LiteSH/builds/client.o -o LiteSH/bin/client

main: LiteSH/builds/main.o LiteSH/builds/LiteSH.o
	$(CC) LiteSH/builds/main.o LiteSH/builds/LiteSH.o -I home/wanderer/OS/LiteSH/libs/libinfo.so -ldl -o LiteSH/bin/main

LiteSH/builds/client.o: LiteSH/client.cpp
	$(CC) -c LiteSH/client.cpp -o LiteSH/builds/client.o

LiteSH/builds/main.o: LiteSH/main.cpp
	$(CC) -c LiteSH/main.cpp -o LiteSH/builds/main.o

LiteSH/builds/LiteSH.o: LiteSH/LiteSH.cpp
	$(CC) -c LiteSH/LiteSH.cpp -o LiteSH/builds/LiteSH.o

clean:
	find -name "*.o" -exec rm -rf {} +
	rm -rf ./bin/main

install:
	sudo cp ./bin/proc /usr/bin/main

uninstall:
	sudo rm -f /usr/bin/main

rebuild: clean all
