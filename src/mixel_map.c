#include "pixel_map.h"

int read_pixel_8bit(int fd, struct pixel_map *map)
{
	struct pixel_8bit pixel;
	if (read(fd, pixel->color, 1) != 1)
		return -1;
	push_pixel_8bit(map, &color);
	return 1;
}

void push_pixel_8bit(struct pixel_map* map, struct pixel_8bit *pixel)
{
	*(map->data_store_8bit + size) = pixel;
	map->size++;
	return;
}
