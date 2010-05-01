TARGET = multimedia02
CC = gcc
CFLAGS = -g -Wall

SRCS = multimedia02.c

all: $(TARGET)

multimedia01:multimedia02.c
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)
	
clean:
	rm -rf $(TARGET)
