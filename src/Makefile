EXE = final

# Main target
all: $(EXE)

#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG = -O3 -Wall
LIBS = -lglut32cu -lglu32 -lopengl32
CLEAN = del *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG = -O3 -Wall -Wno-deprecated-declarations
LIBS = -framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG = -O3 -Wall
LIBS = -lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN = rm -f $(EXE) *.o *.a
endif

# Dependencies
main.o: main.c main.h CSCIx229.h
vector.o: vector.c vector.h
fatal.o: fatal.c CSCIx229.h
loadtexbmp.o: loadtexbmp.c CSCIx229.h
print.o: print.c CSCIx229.h
project.o: project.c CSCIx229.h
errcheck.o: errcheck.c CSCIx229.h
object.o: object.c CSCIx229.h
house.o: house.c house.h
windmill.o: windmill.c
truck.o: truck.c
shapes.o: shapes.c shapes.h

#  Create archive
CSCIx229.a:fatal.o loadtexbmp.o print.o project.o errcheck.o object.o
	ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG) $< -DSDL
.cpp.o:
	g++ -c $(CFLG) $< -DSDL

#  Link
$(EXE): shapes.o house.o truck.o windmill.o main.o vector.o CSCIx229.a
	gcc -O3 -o $@ $^   $(LIBS) -lSDL -lSDL_mixer

#  Clean
clean:
	$(CLEAN)
