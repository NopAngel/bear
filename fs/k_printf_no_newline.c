

unsigned int k_printf_no_newline(const char *message, unsigned int line, unsigned int color) {
    char *vidmem = (char *) 0xb8000;
    unsigned int i = (line * 80 * 2);

    while (*message != 0) {
        vidmem[i] = *message;      
        message++;
        i++;
        vidmem[i] = color;         
        i++;
    }

    return 1; 
}
