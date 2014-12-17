#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct pixel_8bit{
	char color;
};

struct pixel_map {
	int size;
	struct pixel_8bit** data_store_8bit;
};

int read_pixel_8bit(int fd, struct pixel_map* map);
void push_pixel_8bit(struct pixel_map* map, struct pixel_8bit *pixel);
int read_pixel_map_8bit(int fd, struct pixel_map* map, int count);
int read_pixel_map(int fd, struct pixel_map* map, int width, int height, int size);

void print_8bit_color(struct pixel_8bit *pixel);
void print_8bit_pixel_map(struct pixel_map* map);

void deallocate_8bit_pixel_map(struct pixel_map* map);
