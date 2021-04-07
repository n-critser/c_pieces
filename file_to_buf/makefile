
CC=gcc
CFLAGS=-Wall -ggdb3 -pedantic -Werror -lm
SRCS= file_to_buf.c
OBJS:=$(SRCS:.c=.o)
all:$(OBJS)
	$(CC) $(CFLAGS) -o main.out $(OBJS)


%.o:%.c
	$(CC) -O -c $< -o $@ $(CFLAGS)

clean:
	rm -rf main.out $(OBJS)
