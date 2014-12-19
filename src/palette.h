#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

struct palette_color {
	char red;
	char green;
	char blue;
	char alpha;
};

struct palette {
	int size;
	struct palette_color** data_store;
};

int read_color(int fd, struct palette* palette);
void palette_push_color(struct palette* palette, struct palette_color* color);
int read_palette(int fd, struct palette* palette, int count);

int write_color(int fd, struct palette_color* color);
int write_palette(int fd, struct palette* palette);

void print_color(struct palette_color* color);
void print_palette(struct palette* palette);

void deallocate_palette(struct palette* palette);
