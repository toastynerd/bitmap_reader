#include "palette.h"

int read_color(int fd, struct palette* palette)
{
	struct palette_color* color = malloc(4); //4 bytes per palette color
	if (read(fd, (void*)&color->red, 1) != 1)
		return -1;
	if (read(fd, (void*)&color->green, 1) != 1)
		return -1;
	if (read(fd, (void*)&color->blue, 1) != 1)
		return -1;
	if (read(fd, (void*)&color->alpha, 1) != 1)
		return -1;
	palette_push_color(palette, color);

	return 4;
}

void palette_push_color(struct palette* palette, struct palette_color* color)
{
	*(palette->data_store + palette->size) = color;	
	palette->size++;
	return;
}

int read_palette(int fd, struct palette* palette, int count)
{
	int i;
	for (i = 0; i < count; i++) {
		read_color(fd, palette);
	}

	return i;
}

void print_color(struct palette_color* color) {
	printf("red: %02x green: %02x blue: %02x alpha: %02x", color->red, color->green, color->blue, color->alpha);
	return;
};

void print_palette(struct palette* palette)
{
	printf("Number of Colors: %d\n", palette->size);
	int i;
	for (i = 0; i < palette->size; i++) {
		print_color(*(palette->data_store + i));
	}
	printf("\n");
	return;
}
