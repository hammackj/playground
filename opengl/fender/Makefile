CC=gcc
CPPCC=g++
CFLAGS=-g -Wall
LDFLAGS=-framework OpenGL -framework Glut
CODE_FILES=main.c flog.c fvector3.c frenderer.c finput.c fender.c
OUTPUT_BINARY=fender_test

all: fender

fender: $(CODE_FILES)
	$(CC) $(CFLAGS) -o $(OUTPUT_BINARY) $(CODE_FILES) $(LDFLAGS)

clean:
	rm -rf *.dSYM
	rm $(OUTPUT_BINARY)
