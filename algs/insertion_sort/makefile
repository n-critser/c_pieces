
CC=gcc
CFLAGS=-Wall -g -pedantic -Werror
SRCS= insertion_sort.c
OBJS:=$(SRCS:.c=.o)
all:$(OBJS)
	$(CC) $(CFLAGS) -o main.out $(OBJS)


%.o:%.c
	$(CC) -O -c $< -o $@ $(CFLAGS)

clean:
	rm -rf main.out $(OBJS)
