COMPILER=g++
RM=rm -f
LIBS=-lGL -lGLU -lglut

all: main

main: main.o
	$(COMPILER) -o main main.o $(LIBS)

main.o: main.cpp
	$(COMPILER) -c main.cpp $(LIBS)

clean:
	$(RM) *.o

distclean: clean
	$(RM) main