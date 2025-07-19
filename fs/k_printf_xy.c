unsigned int k_printf_xy(char *message, unsigned int x, unsigned int y, unsigned int color)
{
    char *vidmem = (char *) 0xb8000;
    unsigned int i = (y * 80 + x) * 2; // Calcula posición correcta

    while (*message != 0)
    {
        if (*message == '\n') // Nueva línea
        {
            y++;
            i = (y * 80) * 2; // Reinicia a la posición inicial de la línea
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
        x++; // Asegurar que cada letra se coloque en la siguiente columna
    }

    return 1;
}

