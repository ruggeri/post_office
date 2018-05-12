pobox: obj/mailbox.o obj/post_office.o obj/random.o obj/main.o
	c++ -std=c++17 obj/mailbox.o obj/post_office.o obj/random.o obj/main.o -o pobox -lpthread

obj/main.o: src/mailbox.h src/post_office.h src/main.cpp
	c++ -std=c++17 -c src/main.cpp -o obj/main.o

obj/post_office.o: src/mailbox.h src/random.h src/post_office.cpp src/post_office.h
	c++ -std=c++17 -c src/post_office.cpp -o obj/post_office.o

obj/mailbox.o: src/mailbox.cpp src/mailbox.h
	c++ -std=c++17 -c src/mailbox.cpp -o obj/mailbox.o

obj/random.o: src/random.cpp src/random.h
	c++ -std=c++17 -c src/random.cpp -o obj/random.o

clean:
	rm obj/*.o main
