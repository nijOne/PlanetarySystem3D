LDLIBS=-lglut -lGL -lGLEW -lGLU
all: main
clean:
	rm -f *.o main
.PHONY: all clean