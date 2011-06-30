CC=gcc
CFLAGS=-g -Wall
LDFLAGS=-framework OpenGL -framework Glut

all: fullscreen vertexbuffer cubes

fullscreen: fullscreen.c
	$(CC) $(CFLAGS) -o fullscreen fullscreen.c $(LDFLAGS)

vertexbuffer: vertexbuffer.c
	$(CC) $(CFLAGS) -o vertexbuffer vertexbuffer.c $(LDFLAGS)

cubes: cubes.c
	$(CC) $(CFLAGS) -o cubes cubes.c $(LDFLAGS)	

clean:
	rm -rf *.dSYM
	rm fullscreen
	rm vertexbuffer
	rm cubes