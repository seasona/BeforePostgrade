cc=gcc

thread:thread.c
	$(cc) -pthread -g -o $@ $^

.PHONY: clean

clean:
	rm -f thread