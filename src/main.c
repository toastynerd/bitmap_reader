#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "bitmap.h"

int disp_header = 0;
int disp_palette = 0;
int disp_pixels = 0;

int contains_arg(int argc, char **argv, char *string)
{
	int x;
	for (x = 0; x < argc; x++) {
		if (strcmp(argv[x], string) == 0)
			return 1;
	}
	return 0;
}

void parse_args(int argc, char **argv)
{
	if (contains_arg(argc, argv, "--header") == 1)
		disp_header = 1;
	if (contains_arg(argc, argv, "--palette") == 1)
		disp_palette = 1;
	if (contains_arg(argc, argv, "--pixels") == 1)
		disp_pixels = 1;
	return;
}

void usage()
{
	printf("usage: bitmap_reader file.bmp\n");
	return;
}

int main(int argc, char **argv)
{
	int fd, bytes_read;
	struct bitmap bitmap;

	if (argc == 1) {
		usage();
		return 1;
	}

	fd = open(argv[argc - 1], O_RDONLY);
	if (fd == 1) {
		printf("could not open file %s", argv[1]);
		return 1;
	}

	read_bitmap(fd, &bitmap);

	parse_args(argc, argv);

	if (disp_header == 1)
		print_bitmap_header(&bitmap);

	if (disp_palette == 1)
		print_palette(&bitmap.palette);

	if (disp_pixels == 1)
		print_8bit_pixel_map(&bitmap.pixel_map);

	return 0;
}
