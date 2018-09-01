COMPILER=g++
RM=rm -f
LIBS=-lGL -lGLU -lglut

all: main

main: Ball.o main.o
	$(COMPILER) -o main Ball.o main.o $(LIBS)

main.o: main.cpp
	$(COMPILER) -c main.cpp $(LIBS)

Ball.o: Ball.cpp
	$(COMPILER) -c Ball.cpp $(LIBS)

clean:
	$(RM) *.o

distclean: clean
	$(RM) main