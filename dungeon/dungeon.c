#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 128

struct room_t
{
	int x;
	int y;
	int w;
	int h;
};

struct dungeon_t
{
	int **map; //[MAP_SIZE][MAP_SIZE];
	int rooms[];
};

struct dungeon_t dungeon;

void generate()
{
	int room_count = 0;
	int min_size = 5;
	int max_size = 15;
	int x;
	int y;
	int i;

	dungeon.map = malloc(MAP_SIZE * sizeof(int *));
	//Check for null

	for (x = 0; x < MAP_SIZE; x++)
	{
		dungeon.map[x] = malloc(MAP_SIZE * sizeof(int));

		//check null
	}

	for (x = 0; x < MAP_SIZE; ++x)
	{
		for (y = 0; y < MAP_SIZE; ++y)
		{
			dungeon.map[x][y] = 0;
		}
	}

	room_count = get_random(20, 40);

	dungeon.rooms = malloc(room_count * sizeof(struct room_t));
	//Check Null

	for (i = 0; i < room_count; i++)
	{
		dungeon.rooms[i] = malloc(sizeof(struct room_t));
		//Check null

		dungeon.rooms[i].x = get_random(1, MAP_SIZE - max_size - 1);
		dungeon.rooms[i].y = get_random(1, MAP_SIZE - max_size - 1);
		dungeon.rooms[i].w = get_random(min_size, max_size);
		dungeon.rooms[i].h = get_random(min_size, max_size);

	}


}

void print_map()
{
	int x = 0;
	int y = 0;

	for (x = 0; x < MAP_SIZE; ++x)
	{
		for (y = 0; y < MAP_SIZE; ++y)
		{
			printf("%d", dungeon.map[x][y]);
		}

		printf("\n");
	}
}

void get_random(int low, int high)
{
	return (rand() * (high - low) + low);
}

int main(int argc, char const *argv[])
{

	generate();

	print_map();

	return 0;
}
