unsigned int k_printf_xy(char *message, unsigned int x, unsigned int y, unsigned int color)
{
    char *vidmem = (char *) 0xb8000;
    unsigned int i = (y * 80 + x) * 2; 

    while (*message != 0)
    {
        if (*message == '\n') // new line
        {
            y++;
            i = (y * 80 + x) * 2; 
            message++;
        }
        else
        {
            vidmem[i] = *message;
            message++;
            i++;
            vidmem[i] = color;
            i++;
        }
    }

    return 1;
}

