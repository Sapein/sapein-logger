.POSIX:
.SUFFIXES:
CC = gcc
AR = ar
CFLAGS = -Wall -Wpedantic -Wextra -O -fPIC
ARFLAGS = rcs
LDLIBS = 
LDFLAGS = -shared
PREFIX = /usr/local
OUTPUT_NAME = libsapeintlogger

all: logger
logger: libsapeintlogger.so libsapeintlogger.a

libsapeintlogger.so: src/logger.o
	$(CC) $(LDFLAGS) logger.o -o $(OUTPUT_NAME).so $(LDLIBS)

libsapeintlogger.a: src/logger.o
	$(AR) $(ARFLAGS) $(OUTPUT_NAME).a logger.o

src/logger.o: src/logger.c src/logger.h

clean:
	rm *.o

fullclean: clean
	rm *.so *.a

docs: 
	doxygen

install:
	cp src/logger.h $(DESTDIR)$(PREFIX)/include/sapeint_logger.h
	cp $(OUTPUT_NAME).so $(DESTDIR)$(PREFIX)/lib
	cp $(OUTPUT_NAME).a $(DESTDIR)$(PREFIX)/lib
	ldconfig

uninstall:
	rm $(DESTDIR)$(PREFIX)/include/logger.h
	rm $(DESTDIR)$(PREFIX)/lib/$(OUTPUT_NAME).so
	rm $(DESTDIR)$(PREFIX)/lib/$(OUTPUT_NAME).a
	ldconfig

.SUFFIXES: .c .o 
.c.o:
	$(CC) $(CFLAGS) $(DEBUG) -c $<
