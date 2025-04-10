unsigned int k_printf_r(char *message, unsigned int line, unsigned int color)
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;

	i=(line*80*2);

	while(*message!=0)
	{
		if(*message=='\n') // chec1k for a new line (upgrated)
		{
			line++;
			i=(line*80*2);
			*message++;
		} else {
			vidmem[i]=*message;
			*message++;
			i++;
			vidmem[i]=color;
			i++;
		};
	};

	return(1);
}

// WARNING: I know this needs fixing, but I'm too lazy. I'll do it later. :)




void kernelPanic(char * reasons) {
	asm volatile("cli");
	k_printf_r(reasons, 0x04, 0);
}

