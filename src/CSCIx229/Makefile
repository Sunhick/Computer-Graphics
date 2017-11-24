LIB = CSCIx229.a
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

.PHONY : all
all : ${LIB}

include ../common.mk
CRUFT += ${LIB}

${LIB} : ${OBJS}
	$(AR) -rcs $@ $^
