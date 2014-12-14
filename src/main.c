#include <sys/stat.h>
#include <fcntl.h>
#include "bitmap.h"

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

	fd = open(argv[1], O_RDONLY);
	if (fd == 1) {
		printf("could not open file %s", argv[1]);
		return 1;
	}

	read_bitmap(fd, &bitmap);

	print_bitmap_header(&bitmap);
	print_palette(&bitmap.palette);
	return 0;
}
