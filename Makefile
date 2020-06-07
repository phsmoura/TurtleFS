CC=gcc
CFLAGS=-Wall -g

all: clean install

install:
	mkdir hds
	$(CC) $(CFLAGS) main.c -o turtlefs.exe

clean:
	rm -f *.exe
	rm -rf hds/
