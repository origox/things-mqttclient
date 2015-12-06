CC=gcc
CFLAGS=-I.
LIBS= -lpaho-mqtt3c -lpthread
DEPS=

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: mqttpub.o 
	$(CC) -o mqttpub mqttpub.o $(LIBS)

.PHONY: clean

clean:
	rm -f mqttpub *.o *~
