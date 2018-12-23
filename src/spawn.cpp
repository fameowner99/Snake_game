#include "nibbler.hpp"

void	spawn_food(int level_size, int *level, eCells food)
{
	int level_point;

	while (level[(level_point = rand() % level_size)] != BACKGROUND)
		;
	level[level_point] = food;
}

void	spawn_walls(int *level, int snake1_head, int snake2_head, int width, int size, int dif)
{
	int i = size / (dif == 1 ? 16 : 8);

	for (int n = 1; n <= 4; n++)
	{
		level[snake1_head - width * n] = SNAKE_BODY;
		level[snake2_head - width * n] = SNAKE_BODY;
	}
	while (i >= 0)
	{
		int r = rand() % size;
		if (level[r] == 0)
		{
			level[r] = WALL;
			i--;
		}
	}
	for (int n = 1; n <= 4; n++)
	{
		level[snake1_head - width * n] = BACKGROUND;
		level[snake2_head - width * n] = BACKGROUND;
	}
}