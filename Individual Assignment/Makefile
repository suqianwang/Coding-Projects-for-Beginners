# makefile

all: Book.o Course.o Database.o CmdLineHandler.o main.o
	c++ -std=c++11 Book.o Course.o Database.o CmdLineHandler.o main.o -o main
Book.o : Book.cpp Book.h
	c++ -std=c++11 -c -g Book.cpp
Course.o : Course.cpp Course.h
	c++ -std=c++11 -c -g Course.cpp
Database.o : Database.cpp Database.h
	c++ -std=c++11 -c -g Database.cpp
CmdLineHandler.o : CmdLineHandler.cpp CmdLineHandler.h
	c++ -std=c++11 -c -g CmdLineHandler.cpp
main.o: main.cpp Book.h Course.h Database.h CmdLineHandler.h
	c++ -std=c++11 -c -g main.cpp
clean:
	rm *.o main


