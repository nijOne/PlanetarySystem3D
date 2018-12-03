LDLIBS=-lglut -lGL -lGLEW -lGLU
all: main
CFLAGS = -Wall -Werror -g
clean:
	rm -f *.o main
.PHONY: all clean