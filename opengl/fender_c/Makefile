CC=gcc
CFLAGS=-g -Wall
#LDFLAGS=-framework OpenGL -framework Glut
LDFLAGS=-lGL -lglut -lGLU -lGLEW
CODE_FILES=main.c flog.c fmath.c fvector3.c fmatrix4.c frenderer.c finput.c fender.c fcamera.c
OUTPUT_BINARY=fender_test

all: fender

fender: $(CODE_FILES)
	$(CC) $(CFLAGS) -o $(OUTPUT_BINARY) $(CODE_FILES) $(LDFLAGS)

clean:
	rm -rf *.dSYM
	rm $(OUTPUT_BINARY)
	rm log.txt
