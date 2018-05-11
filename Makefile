main: mailbox.o post_office.o random.o main.o
	c++ -std=c++17 mailbox.o post_office.o random.o main.o -o main

main.o: mailbox.h post_office.h  main.cpp
	c++ -std=c++17 -c main.cpp -o main.o

post_office.o: mailbox.h random.h post_office.cpp post_office.h
	c++ -std=c++17 -c post_office.cpp -o post_office.o

mailbox.o: mailbox.cpp mailbox.h
	c++ -std=c++17 -c mailbox.cpp -o mailbox.o

random.o: random.cpp random.h
	c++ -std=c++17 -c random.cpp -o random.o

clean:
	rm *.o main
