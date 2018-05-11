main: mailbox.o main.o
	c++ -std=c++17 mailbox.o main.o -o main

main.o: mailbox.h main.cpp
	c++ -std=c++17 -c main.cpp -o main.o

mailbox.o: mailbox.cpp mailbox.h
	c++ -std=c++17 -c mailbox.cpp -o mailbox.o

clean:
	rm *.o main
