#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include "palette.h"
#include "pixel_map.h"

#define RB_BI_RGB            0
#define RB_BI_RLE8           1
#define RB_BI_RLE4           2
#define RB_BI_BITFIELDS      3
#define RB_BI_JPEG           4
#define RB_BI_PNG            5
#define RB_BI_ALPHABITFIELDS 6
#define RB_BI_CMYK           11
#define RB_BI_CMYKRLE8       12
#define RB_BI_CMYKRLE4       13

struct bitmap_fileheader {
	char header_field[2];
	uint32_t size;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t offset;
};

struct bitmap_infoheader {
	uint32_t size;
	uint32_t width;
	uint32_t height;
	uint16_t color_planes;
	uint16_t color_depth;
	uint32_t compression;
	uint32_t image_size;
	uint32_t horizontal_ppm;
	uint32_t verticle_ppm;
	uint32_t color_palette;
	uint32_t important_colors;
};

struct bitmap {
	struct bitmap_fileheader fileheader;
	struct bitmap_infoheader infoheader;
	struct palette palette;
	struct pixel_map pixel_map;
};

int read_fileheader(int fd, struct bitmap* bitmap);
int read_infoheader(int fd, struct bitmap* bitmap);
int read_v4infoheader(int fd, struct bitmap* bitmap);
int read_bitmap(int fd, struct bitmap* bitmap);

void print_bitmap_header(struct bitmap* bitmap);
void print_v4bitmap(struct bitmap* bitmap);

void deallocate_bitmap(struct bitmap* bitmap);
