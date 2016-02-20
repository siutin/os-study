#include "color.h"

uint8_t make_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}
