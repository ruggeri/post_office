FLAGS=-std=c++17 -O3

pobox: \
	obj/mailbox.o \
	obj/mailbox_listener.o \
	obj/mailbox_producer.o \
	obj/main.o \
	obj/post_office.o \
	obj/random.o
	c++ ${FLAGS} \
		obj/mailbox.o \
		obj/mailbox_listener.o \
		obj/mailbox_producer.o \
		obj/post_office.o \
		obj/random.o \
		obj/main.o \
		-lpthread \
		-o pobox

obj/main.o: src/mailbox.h src/post_office.h src/main.cpp
	c++ ${FLAGS} -c src/main.cpp -o obj/main.o

obj/mailbox_listener.o: \
	src/mailbox.h \
	src/mailbox_listener.cpp \
	src/mailbox_listener.h \
	src/post_office.h
	c++ ${FLAGS} -c src/mailbox_listener.cpp -o obj/mailbox_listener.o

obj/mailbox_producer.o: \
	src/mailbox.h \
	src/mailbox_producer.cpp \
	src/mailbox_producer.h \
	src/post_office.h
	c++ ${FLAGS} -c src/mailbox_producer.cpp -o obj/mailbox_producer.o

obj/post_office.o: \
	src/mailbox.h \
	src/post_office.cpp \
	src/post_office.h \
	src/random.h
	c++ ${FLAGS} -c src/post_office.cpp -o obj/post_office.o

obj/mailbox.o: src/mailbox.cpp src/mailbox.h
	c++ ${FLAGS} -c src/mailbox.cpp -o obj/mailbox.o

obj/random.o: src/random.cpp src/random.h
	c++ ${FLAGS} -c src/random.cpp -o obj/random.o

clean:
	rm obj/*.o pobox
