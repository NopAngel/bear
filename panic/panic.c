/*
*
*   panic.c - a generic file for panic
*
*  (C) 2025 Angel Nieto/NopAngel <angelnieto1402@gmail.com>
*
*           This code is licenced under the APACHE 2.0
*/


// WARNING: I know this needs fixing, but I'm too lazy. I'll do it later. :)

void bear_panic(const char *msg) {
    
    for (int y = 0; y < 25; y++) {
        for (int x = 0; x < 80; x++)
            text_draw(x, y, ' ', 0x4C);  
    }
    const char *header = "PANIC ERROR :(";
    int x = (80 - 18) / 2;
    for (int i = 0; header[i]; i++)
        text_draw(x + i, 5, header[i], 0x47);  

    int y = 8;
    for (int i = 0; msg[i] && y < 24; i++) {
        text_draw((i % 60) + 10, y, msg[i], 0x47); 
        if (i % 60 == 59) y++;
    }

    
    while (1) {
        __asm__ volatile ("hlt");
    }
}
