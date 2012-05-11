CC=gcc
CPPCC=g++
CFLAGS=-g -Wall
LDFLAGS=-lpcap

all: pcap

pcap: pcap.c
	$(CC) $(CFLAGS) -o pcap pcap.c $(LDFLAGS)

clean:
	rm -rf *.dSYM
	rm pcap

