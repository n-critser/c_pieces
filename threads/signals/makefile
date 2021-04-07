
CC=gcc
CFLAGS=-Wall -pthread -ggdb3
SRCS= mask_ex.c
OBJS:=$(SRCS:.c=.o)

all:$(OBJS)
	$(CC) $(CFLAGS) -o main.out $(OBJS)

%.o:%.c
	$(CC) -O -c $< -o $@ $(CFLAGS)
clean:
	rm -f main.out $(OBJS)
