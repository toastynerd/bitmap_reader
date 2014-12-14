#include "pixel_map.h"

int read_pixel_8bit(int fd, struct pixel_map *map)
{
	struct pixel_8bit pixel;
	if (read(fd, &pixel.color, 1) != 1)
		return -1;
	push_pixel_8bit(map, &pixel);
	return 1;
}

void push_pixel_8bit(struct pixel_map* map, struct pixel_8bit *pixel)
{
	*(map->data_store_8bit + map->size) = pixel;
	map->size++;
	return;
}

int read_pixel_map_8bit(int fd, struct pixel_map* map, int count)
{
	int i;
	for (i = 0; i < count; i++) {
		read_pixel_8bit(fd, map);
	}
	return i;
}

int read_pixel_map(int fd, struct pixel_map* map, int width, int height, int size)
{
	int num_pixels, bit_depth; //size in bytes vs num pixels
	num_pixels = width * height;
	bit_depth = ((size * 8) / num_pixels);
	if (bit_depth == 8) 
		return read_pixel_map_8bit(fd, map, num_pixels);
	return -1;
}
