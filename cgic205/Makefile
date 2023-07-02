CFLAGS=-g -Wall
CROSSCOMPILE=arm-none-linux-gnueabihf-
CC=$(CROSSCOMPILE)gcc
AR=$(CROSSCOMPILE)ar
RANLIB=$(CROSSCOMPILE)ranlib
LIBS=-L./ -lcgic -static
NFSBOA_CGIBIN=~/opt/rootfs/boa/cgi-bin

all: libcgic.a cgictest.cgi mytestcgi.cgi login.cgi capture

install: libcgic.a
	cp libcgic.a /usr/local/lib
	cp cgic.h /usr/local/include
	@echo libcgic.a is in /usr/local/lib. cgic.h is in /usr/local/include.

libcgic.a: cgic.o cgic.h
	rm -f libcgic.a
	$(AR) rc libcgic.a cgic.o
	$(RANLIB) libcgic.a

#mingw32 and cygwin users: replace .cgi with .exe

cgictest.cgi: cgictest.o libcgic.a
	$(CC) cgictest.o -o cgictest.cgi ${LIBS}

mytestcgi.cgi: mytestcgi.o libcgic.a
	$(CC) mytestcgi.o -o mytestcgi.cgi ${LIBS}

login.cgi: login.o libcgic.a
	$(CC) login.o -o login.cgi ${LIBS}

capture: capture.o libcgic.a
	$(CC) capture.o -o capture ${LIBS}

nfsdeal:
	mv *.o ./obj/
	mv *.a *.cgi capture ./cgi-bin/
	sudo cp ./cgi-bin/* $(NFSBOA_CGIBIN)
clean:
	rm -f *.o *.a cgictest.cgi capture

