CC=gcc
CPPCC=g++
CFLAGS=-g -Wall
LDFLAGS=-framework OpenGL -framework Glut

all: fullscreen vertexbuffer cubes floor firstperson map normals keyboard world

fullscreen: fullscreen.c
	$(CC) $(CFLAGS) -o fullscreen fullscreen.c $(LDFLAGS)

vertexbuffer: vertexbuffer.c
	$(CC) $(CFLAGS) -o vertexbuffer vertexbuffer.c $(LDFLAGS)

cubes: cubes.c
	$(CC) $(CFLAGS) -o cubes cubes.c $(LDFLAGS)	

floor: floor.c
	$(CC) $(CFLAGS) -o floor floor.c $(LDFLAGS)

firstperson: firstperson.c
	$(CC) $(CFLAGS) -o firstperson firstperson.c $(LDFLAGS)

map: map.c
	$(CC) $(CFLAGS) -o map map.c $(LDFLAGS)

normals: normals.c
	$(CC) $(CFLAGS) -o normals normals.c $(LDFLAGS)

keyboard: keyboard.c
	$(CC) $(CFLAGS) -o keyboard keyboard.c $(LDFLAGS)

world: world.c
	$(CC) $(CFLAGS) -o world world.c $(LDFLAGS)

clean:
	rm -rf *.dSYM
	rm fullscreen
	rm vertexbuffer
	rm cubes
	rm floor
	rm firstperson
	rm map
	rm normals
	rm keyboard
	rm world