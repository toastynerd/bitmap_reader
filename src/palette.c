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
	palette->data_store = malloc(count * sizeof(struct palette_color*));
	for (i = 0; i < count; i++) {
		read_color(fd, palette);
	}

	return i;
}

int write_color(int fd, struct palette_color* color)
{
	int num_write = 0;
	num_write += write(fd, &color->red, 1);
	num_write += write(fd, &color->green, 1);
	num_write += write(fd, &color->blue, 1);
	num_write += write(fd, &color->alpha, 1);
	return num_write;
}

int write_palette(int fd, struct palette* palette)
{
	int i;
	int num_write = 0;
	for (i = 0; i < palette->size; i++) {
		num_write += write_color(fd, (struct palette_color*)*(palette->data_store + i));
	}

	return num_write;
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

void deallocate_palette(struct palette* palette)
{
	int i;
	for (i = 0; i < palette->size; i++) {
		free(*(palette->data_store + i));
		*(palette->data_store + i) = NULL;
	}
	free(palette->data_store);
	palette->data_store = NULL;
	return;
}
