COMPILER=g++
RM=rm -f
LIBS=-lGL -lGLU -lglut

all: main

main: Block.o Ball.o main.o
	$(COMPILER) -o main Block.o Ball.o main.o $(LIBS)

main.o: main.cpp
	$(COMPILER) -c main.cpp $(LIBS)

Ball.o: Ball.cpp
	$(COMPILER) -c Ball.cpp $(LIBS)

Block.o: Block.cpp
	$(COMPILER) -c Block.cpp $(LIBS)

clean:
	$(RM) *.o

distclean: clean
	$(RM) main

remake: distclean all