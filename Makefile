CFLAGS=-lpthread -ldl -I/usr/include/

init: 
	@echo $(CFLAGS)

compile: sqlite3.o
	g++ test.cpp sqlite3.o $(CFLAGS) -o test

sqlite3.o:
	gcc /usr/include/sqlite3.c -c