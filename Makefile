CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89

all: simple_shell

simple_shell: main.o execute.o parse.o utility.o
	$(CC) $(CFLAGS) -o simple_shell main.o execute.o parse.o utility.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o simple_shell
