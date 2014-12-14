CFLAGS=-g
.PHONY: clean debug

all: bitmap_reader

bitmap_reader: src/bitmap.o src/main.o src/palette.o src/pixel_map.o
	mkdir -p bin
	gcc src/pixel_map.o src/bitmap.o src/main.o src/palette.o -o bin/bitmap_reader

clean:
	rm -f bin/bitmap_reader src/main.o src/bitmap.o src/palette.o src/pixel_map.o
