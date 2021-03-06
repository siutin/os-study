#include "string.h"
#include "term.h"

uint16_t make_vgaentry(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize() {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_scroll(){
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			terminal_buffer[y * VGA_WIDTH + x] = terminal_buffer[(y+1) * VGA_WIDTH + x];
		}
	}
}

void terminal_newline(){
	terminal_column = 0;
	if ((terminal_row + 1) != VGA_HEIGHT) {
			terminal_row++;
	}
}

void terminal_putchar(char c) {
	if (c == '\n'){
		if ( (terminal_row + 1) == VGA_HEIGHT) {
			terminal_scroll();
			terminal_column = 0;						
		}
		else{
			terminal_newline();
		}
	}else{
		if (++terminal_column == VGA_WIDTH) {
			terminal_newline();
			if ( (terminal_row + 1) == VGA_HEIGHT) {
					terminal_scroll();
			}
		}
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	}
}

void terminal_writestring(const char* data) {
	size_t datalen = strlen(data);
	for (size_t i = 0; i < datalen; i++){
		terminal_putchar(data[i]);
	}
}
