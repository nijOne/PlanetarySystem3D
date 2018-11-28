LDLIBS=-lglut -lGL -lGLEW
all: main
clean:
	rm -f *.o main
.PHONY: all clean