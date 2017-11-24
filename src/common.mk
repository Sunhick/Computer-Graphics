CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

CFLAGS = -O3 -Wall -Wno-deprecated-declarations
CRUFT = $(wildcard *.o *.a *.c~ *.h~ *.exe)
HEADERS = -I .

# Compile rules
%.o : %.c
	$(CC) -c $(CFLAGS) $< -DSDL ${HEADERS}

.PHONY : decruft
decruft :
	$(RM) -- ${CRUFT}
