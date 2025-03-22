/*
 *
 * kernel.c - version 0.0.1
 * 
 */


#define WHITE_TXT 0x07 /* light gray on black text */

void k_clear_screen();
unsigned int k_printf(char *message, unsigned int line);

// Simula datos de la batería
static BatteryStatus battery_status = {
    .state = BATTERY_STATE_UNKNOWN,
    .charge = 0,
    .voltage = 0,
    .capacity = 0
};

// Inicializa el controlador de batería
void battery_init() {
    battery_status.state = BATTERY_STATE_CHARGING; // Simulación de batería cargando
    battery_status.charge = 75;                    // 75% de carga
    battery_status.voltage = 11400;                // 11.4V (en mV)
    battery_status.capacity = 5000;                // 5000mAh
    k_printf("Controlador de batería inicializado.\n", 10, 0x0A); // Línea 10, verde
}

// Obtiene el estado actual de la batería
void battery_get_status(BatteryStatus* status) {
    if (status) {
        status->state = battery_status.state;
        status->charge = battery_status.charge;
        status->voltage = battery_status.voltage;
        status->capacity = battery_status.capacity;
        k_printf("Batería: %d%%, Voltaje: %dmV, Capacidad: %dmAh\n", 11, 0x07); // Línea 11
    } else {
        k_printf("Error: No se pudo obtener el estado de la batería.\n", 12, 0x04); // Línea 12, rojo
    }
}







/* simple kernel written in C */
void k_main() 
{
	k_clear_screen();
	k_printf("Hello, world! Welcome to my kernel.", 0);
	battery_init();
};



/* k_clear_screen : to clear the entire text screen */
void k_clear_screen()
{

	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (80*25*2))
	{
		vidmem[i]=' ';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	};
};

/* k_printf : the message and the line # */
unsigned int k_printf(char *message, unsigned int line)
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;

	i=(line*80*2);

	while(*message!=0)
	{
		if(*message=='\n') // check for a new line
		{
			line++;
			i=(line*80*2);
			*message++;
		} else {
			vidmem[i]=*message;
			*message++;
			i++;
			vidmem[i]=WHITE_TXT;
			i++;
		};
	};

	return(1);
}
