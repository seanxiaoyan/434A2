# Name: Xiaoyan Xu
# Student  Number: 11229743
# NSID: xix799

CC=gcc
CFLAGS=-g
CPPFLAGS= -std=gnu90 -Wall -pedantic

build: serverudp clientudp proxyudp servertcp clienttcp proxytcp
serverudp: serverudp.o
	$(CC) -o serverudp serverudp.o
serverudp.o: serverudp.c
	$(CC) -o serverudp.o -c $(CFLAGS) $(CPPFLAGS) serverudp.c
clientudp: clientudp.o
	$(CC) -o clientudp clientudp.o
clientudp.o: clientudp.c
	$(CC) -o clientudp.o -c $(CFLAGS) $(CPPFLAGS) clientudp.c

.PHONY: clean
clean: 
	rm -f serverudp.o clientudp.o serverudp clientudp
