#include "bitmap.h"

int read_fileheader(int fd, struct bitmap* bitmap)
{
	int num_read = 0;
	num_read += read(fd, bitmap->fileheader.header_field, 2);
	num_read += read(fd, (void*)&bitmap->fileheader.size, 4);
	num_read += read(fd, (void*)&bitmap->fileheader.reserved1, 2);
	num_read += read(fd, (void*)&bitmap->fileheader.reserved2, 2);
	num_read += read(fd, (void*)&bitmap->fileheader.offset, 4);

	return num_read;
}

int read_infoheader(int fd, struct bitmap* bitmap)
{
	int num_read = 0;
	num_read += read(fd, (void*)&bitmap->infoheader.size, 4);
	num_read += read(fd, (void*)&bitmap->infoheader.width, 4);
	num_read += read(fd, (void*)&bitmap->infoheader.height, 4);
	num_read += read(fd, (void*)&bitmap->infoheader.color_planes, 2);
	num_read += read(fd, (void*)&bitmap->infoheader.color_depth
, 2);
	num_read += read(fd, (void*)&bitmap->infoheader.compression, 4);
	num_read += read(fd, (void*)&bitmap->infoheader.image_size, 4);
	num_read += read(fd, (void*)&bitmap->infoheader.horizontal_ppm, 4);
	num_read += read(fd, (void*)&bitmap->infoheader.verticle_ppm, 4);
	num_read += read(fd, (void*)&bitmap->infoheader.color_palette, 4);
	num_read += read(fd, (void*)&bitmap->infoheader.important_colors, 4);

	return num_read;
}

int read_bitmap(int fd, struct bitmap *bitmap)
{
	if (read_fileheader(fd, bitmap) != 14)
		return -1;
	if (read_infoheader(fd, bitmap) != 40)
		return -1;
	bitmap->palette.size = 0;
	if (read_palette(fd, &bitmap->palette, (int)bitmap->infoheader.color_palette) != bitmap->infoheader.color_palette) 
		return -1;

	bitmap->pixel_map.size = 0;
	if (read_pixel_map(fd, &(bitmap->pixel_map), bitmap->infoheader.width, bitmap->infoheader.height, bitmap->fileheader.size - bitmap->fileheader.offset) != bitmap->infoheader.width * bitmap->infoheader.width)
		return -1;
	return 0;
}

int write_fileheader(int fd, struct bitmap *bitmap)
{
	int num_written = 0;
	num_written += write(fd, bitmap->fileheader.header_field, 2);
	num_written += write(fd, &bitmap->fileheader.size, 4);
	num_written += write(fd, &bitmap->fileheader.reserved1, 2);
	num_written += write(fd, &bitmap->fileheader.reserved2, 2);
	num_written += write(fd, &bitmap->fileheader.offset, 4);

	return num_written;
}

int write_infoheader(int fd, struct bitmap* bitmap)
{
	int num_written = 0;
	num_written += write(fd, &bitmap->infoheader.size, 4);
	num_written += write(fd, &bitmap->infoheader.width, 4);
	num_written += write(fd, &bitmap->infoheader.height, 4);
	num_written += write(fd, &bitmap->infoheader.color_planes, 4);
	num_written += write(fd, &bitmap->infoheader.color_depth, 2);
	num_written += write(fd, &bitmap->infoheader.compression, 4);
	num_written += write(fd, &bitmap->infoheader.image_size, 4);
	num_written += write(fd, &bitmap->infoheader.horizontal_ppm, 4);
	num_written += write(fd, &bitmap->infoheader.verticle_ppm, 4);
	num_written += write(fd, &bitmap->infoheader.color_planes, 4);
	num_written += write(fd, &bitmap->infoheader.important_colors, 4);

	return num_written;
}

int write_bitmap(int fd, struct bitmap* bitmap)
{
	int num_written = 0;
	num_written += write_fileheader(fd, bitmap);
	num_written += write_infoheader(fd, bitmap);

	return num_written;
}

void print_bitmap_header(struct bitmap* bitmap)
{
	printf("fileheader:\n");
	printf("\theader_field: %c%c\n", bitmap->fileheader.header_field[0], bitmap->fileheader.header_field[1]);
	printf("\tsize: %d\n", bitmap->fileheader.size);
	printf("\treserved 1: %d\n", bitmap->fileheader.reserved1);
	printf("\treserved 2: %d\n", bitmap->fileheader.reserved2);
	printf("\toffset: %d\n", bitmap->fileheader.offset);
	printf("common_infoheader:\n");
	printf("\tsize: %d\n", bitmap->infoheader.size);
	printf("\twidth: %d\n", bitmap->infoheader.width);
	printf("\theight: %d\n", bitmap->infoheader.height);
	printf("\tcolor_planes: %d\n", bitmap->infoheader.color_planes);
	printf("\tcompression: %d\n", bitmap->infoheader.compression);
	printf("\thorizontal_ppm: %d\n", bitmap->infoheader.horizontal_ppm);
	printf("\tverticle_ppm: %d\n", bitmap->infoheader.verticle_ppm);
	printf("\tcolor_palette: %d\n", bitmap->infoheader.color_palette);
	printf("\timportant_colors: %d\n", bitmap->infoheader.important_colors);

	return;
}

void deallocate_bitmap(struct bitmap* bitmap)
{
	deallocate_8bit_pixel_map(&bitmap->pixel_map);
	deallocate_palette(&bitmap->palette);
	return;
}

