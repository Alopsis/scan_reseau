CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS =

TARGET = scanner
SRCS = scan.c main.c
OBJS = $(SRCS:.c=.o)


make: $(OBJS)
	$(CC) $(LDFLAGS) -o scan $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS)
	rm scan
