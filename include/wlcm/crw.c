#define GREEN_TXT 0x02
#define ORANGE_TXT 0x06
#define WHITE_TXT 0x07


void CR_W() {
	k_clear_screen();
	k_printf("[BEAR] Bear packs loading",0, GREEN_TXT);
    delay(10);
    k_printf("[BEAR] Bear packs loaded.",0, GREEN_TXT);

	k_printf("[BEAR] Init scripts",1, GREEN_TXT);


	k_printf("[BEAR] APM Manager inited",2, GREEN_TXT);


	k_printf("[BEAR] Terminal preparing",3, GREEN_TXT);
    delay(10);
    k_printf("[BEAR] Terminal prepared.",3, GREEN_TXT);


	k_printf("[BEAR] Keyboard port inited",4, GREEN_TXT);
    delay(10);

	k_printf("[BEAR] Sound inited port",5, GREEN_TXT);


	k_printf("[BEAR] VGA Resolution PREPARED",6, GREEN_TXT);
    delay(10);
    k_printf("[BEAR] VGA Resolution PREPARED",6, GREEN_TXT);


	k_printf("[BEAR] Keyboard Scanned loading",7, GREEN_TXT);
    delay(10);
    k_printf("[BEAR] Keyboard Scanned loaded.",7, GREEN_TXT);


	k_printf("[BEAR] Commands PREPARING",8, GREEN_TXT);
    delay(10);
    k_printf("[BEAR] Commands PREPARED..",8, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Drivers PREPARING..",9, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Drivers PREPARED..",10, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Disk method PREPARING",11, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Disk method PREPARED..",12, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] PCI Devices PREPARING",13, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] PCI Devices PREPARED..",14, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Colors loading",15, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Colors loaded..",16, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Optimization PREPARING",17, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Optimization PREPARED..",18, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Itoa PREPARING",19, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Itoa PREPARED..",20, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] SOUND DRVIER PREPARED",21, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] SOUND DRIVER PREPARING..",22, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] INFORMATION PREPARING",23, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] INFORMATION PREPARED..",24, GREEN_TXT);
    delay(10);


	k_printf("-----------------------------------",25, WHITE_TXT);
    k_clear_screen();
	delay(10);
	k_clear_screen();
    k_printf_center("BearOS starting - Author: NopAngel", 12, ORANGE_TXT);
}
