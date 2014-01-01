CC=gcc
CFLAGS=-I.
#DEPS = hellomake.h
OBJ = dungeon.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

dungeon: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o dungeon