TARGET = final

LIBS = -lglut -lGLU -lGL -lm

ifeq "$(OS)" "Windows_NT"
LIBS = -lglut32cu -lglu32 -lopengl32
else
ifeq "$(shell uname)" "Darwin"
LIBS = -framework GLUT -framework OpenGL
endif
endif

.PHONY : all
all: ${TARGET}

include common.mk

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
CRUFT += ${TARGET}

LIB_ROOT = ./CSCIx229
HEADERS += -I ${LIB_ROOT}
LDFLAGS = -lSDL -lSDL_mixer

${TARGET}: ${OBJS} lib
	$(CC) -o $@ ${OBJS} $(LIBS) ${LDFLAGS} ${LIB_ROOT}/CSCIx229.a

.PHONY : lib
lib :
	${MAKE} -C CSCIx229

.PHONY : clean
clean : decruft
	${MAKE} -C CSCIx229 decruft
