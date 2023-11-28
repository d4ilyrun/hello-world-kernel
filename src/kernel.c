#include <stdint.h>

enum vga_color {
    VGA_COLOR_BLACK = 0,
    // Some colors we will not use ...
    VGA_COLOR_WHITE = 15,
};

struct vga_character {
    uint8_t character;
    enum vga_color fg : 4;
    enum vga_color bg : 4;
} __attribute__((__packed__));

#include <stddef.h> // For size_t

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static uint8_t terminal_row = 0;
static uint8_t terminal_column = 0;

void terminal_putchar(char c, enum vga_color fg, enum vga_color bg)
{
    static struct vga_character *terminal_buffer =
        (struct vga_character *)(0xB8000);

    struct vga_character character = {.character = c, .fg = fg, .bg = bg};
    terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] = character;

    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
            terminal_row = 0;
    }
}

void terminal_reset(void)
{
    terminal_row = 0;
    terminal_column = 0;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            terminal_putchar(' ', VGA_COLOR_BLACK, VGA_COLOR_BLACK);
        }
    }
}

void terminal_write(const char *s, size_t len)
{
    // We write each character in white over black
    for (size_t i = 0; i < len; ++i)
        terminal_putchar(s[i], VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

int kernel_main(void)
{
    const char string[] = "Hello, GISTRE!";
    terminal_reset();
    terminal_write(string, sizeof(string));
    return 0;
}
