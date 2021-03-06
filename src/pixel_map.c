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
	map->data_store_8bit = malloc(count * sizeof(struct pxiel_8bit*));
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

void print_8bit_color(struct pixel_8bit *pixel)
{
	printf("color: %02x ", pixel->color);
}

void print_8bit_pixel_map(struct pixel_map* map) {
	int i;
	printf("8-Bit Pixel Map: %d\n", map->size);
	for (i = 0; i < map->size; i++) {
		print_8bit_color((struct pixel_8bit*)map->data_store_8bit + i);
	}
};

void deallocate_8bit_pixel_map(struct pixel_map* map)
{
	free(map->data_store_8bit);
	map->data_store_8bit = NULL;
	return;
}
