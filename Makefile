CC=gcc
CFLAGS=-I.
LIBS= -lpaho-mqtt3c -lpthread
DEPS=
PREFIX=/usr/local

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: mqttpub.o 
	$(CC) -o mqttpub mqttpub.o $(LIBS)

clean:
	rm -f mqttpub *.o *~

install: all
	mkdir -p $(PREFIX)/bin
	cp mqttpub $(PREFIX)/bin

test:

.PHONY: clean test install all