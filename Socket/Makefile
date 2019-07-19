
TARGET= server client

all: ${TARGET}

server: server.c
	gcc -Wall -o $@ $^

client: client.c
	gcc -Wall -o $@ $^

.PHONY: clean

clean:
	rm -f ${TARGET}