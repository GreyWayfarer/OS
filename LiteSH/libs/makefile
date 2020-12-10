libinfo.so: info.o
	g++ -Wall -g -shared -o libinfo.so info.o

info.o: info.cpp
	g++ -c -fPIC info.cpp

clean:
	rm -rf *.o *.so
