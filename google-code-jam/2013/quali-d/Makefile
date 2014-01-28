CC=gcc
#CFLAGS=-std=gnu99 -Wall -g -O3 -pg
CFLAGS=-std=gnu99 -Wall -g -O3

all: quali-d

quali-d: quali-d.c

xs: quali-d
	@./$^ quali-d-input-xs

s: quali-d
	@./$^ quali-d-input-s

l: quali-d
	@./$^ quali-d-input-l

.PHONY: clean
clean:
	rm -f quali-d
