#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA 0xCFC



int uptime_seconds = 0;

void timer_tick() {
    static int ticks = 0;
    ticks++;
    if (ticks >= 100) {  
        ticks = 0;
        uptime_seconds++;
    }
}

void cmd_uptime() {
    char msg[32];
    int sec = uptime_seconds;
    int min = sec / 60;
    sec %= 60;

    int i = 0;
    msg[i++] = 'U'; msg[i++] = 'p'; msg[i++] = 't'; msg[i++] = 'i'; msg[i++] = 'm'; msg[i++] = 'e';
    msg[i++] = ':'; msg[i++] = ' ';
    msg[i++] = '0' + min / 10;
    msg[i++] = '0' + min % 10;
    msg[i++] = 'm';
    msg[i++] = ' ';
    msg[i++] = '0' + sec / 10;
    msg[i++] = '0' + sec % 10;
    msg[i++] = 's';
    msg[i] = '\0';

    for (int j = 0; msg[j]; j++){
        text_draw(j, 20, msg[j], 0x0B); 
}
}
