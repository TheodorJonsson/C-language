CC = gcc
CFLAGS = -g -std=gnu11 -Werror -Wall -Wextra -Wpedantic -Wmissing-declarations -Wmissing-prototypes -Wold-style-definition

mexec: mexec.o
	$(CC) -o mexec mexec.o $(CFLAGS)
mexec.o: mexec.c mexec.h
	$(CC) -c mexec.c $(CFLAGS)