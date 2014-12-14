.PHONY: clean

all: bitmap_reader

bitmap_reader: src/bitmap.o src/main.o
	mkdir -p bin
	gcc src/bitmap.o src/main.o -o bin/bitmap_reader
clean:
	rm -f bin/bitmap_reader src/main.o src/bitmap.o
