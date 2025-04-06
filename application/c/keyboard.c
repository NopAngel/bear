#define VIDEO_MEMORY 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define KEYBOARD_PORT 0x60

unsigned int cursor_x = 0;
unsigned int cursor_y = 0;


void write_char(char c, unsigned char color) {
    unsigned short *video_memory = (unsigned short *)VIDEO_MEMORY;
    unsigned int position = (cursor_y * SCREEN_WIDTH) + cursor_x;

    video_memory[position] = (color << 8) | c;

    cursor_x++;
    if (cursor_x >= SCREEN_WIDTH) {
        cursor_x = 0;
        cursor_y++;
        if (cursor_y >= SCREEN_HEIGHT) {
            cursor_y = 0;
        }
    }
}

void write_string(const char *string, unsigned char color) {
    while (*string != 0) {
        write_char(*string, color);
        string++;
    }
}


void set_cursor(unsigned int x, unsigned int y) {
    cursor_x = x;
    cursor_y = y;
}

char read_key() {
    char key;
    while (1) {
        if (inportb(KEYBOARD_PORT) != 0) {
            key = inportb(KEYBOARD_PORT);
            return key;
        }
    }
}

void keyboard_handler(unsigned char color) {
    char key;
    while (1) {
        key = read_key();
        if (key > 0) {
            write_char(key, color); 
        }
    }
}
