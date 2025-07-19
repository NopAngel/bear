#define CMOS_ADDRESS 0x70
#define CMOS_DATA    0x71

// CMOS registros
#define REG_SECOND  0x00
#define REG_MINUTE  0x02
#define REG_HOUR    0x04
#define REG_DAY     0x07
#define REG_MONTH   0x08
#define REG_YEAR    0x09
#define REG_STATUSB 0x0B

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int  u32;

typedef struct {
    u8 second;
    u8 minute;
    u8 hour;
    u8 day;
    u8 month;
    u32 year;
} rtc_time_t;

static inline u8 inb(u16 port) {
    u8 r;
    __asm__ __volatile__("inb %1, %0" : "=a"(r) : "Nd"(port));
    return r;
}

static inline void outb(u16 port, u8 val) {
    __asm__ __volatile__("outb %0, %1" : : "a"(val), "Nd"(port));
}

// Espera a que RTC no esté actualizando
static int rtc_is_updating() {
    outb(CMOS_ADDRESS, 0x0A);
    return inb(CMOS_DATA) & 0x80;
}

static u8 rtc_read(u8 reg) {
    outb(CMOS_ADDRESS, reg);
    return inb(CMOS_DATA);
}

static u8 bcd_to_bin(u8 bcd) {
    return (bcd & 0x0F) + ((bcd >> 4) * 10);
}

rtc_time_t rtc_get_time() {
    while (rtc_is_updating());

    rtc_time_t t;
    t.second = rtc_read(REG_SECOND);
    t.minute = rtc_read(REG_MINUTE);
    t.hour   = rtc_read(REG_HOUR);
    t.day    = rtc_read(REG_DAY);
    t.month  = rtc_read(REG_MONTH);
    t.year   = rtc_read(REG_YEAR);

    // ¿Formato BCD?
    u8 status_b = rtc_read(REG_STATUSB);
    if (!(status_b & 0x04)) { // no binary
        t.second = bcd_to_bin(t.second);
        t.minute = bcd_to_bin(t.minute);
        t.hour   = bcd_to_bin(t.hour);
        t.day    = bcd_to_bin(t.day);
        t.month  = bcd_to_bin(t.month);
        t.year   = bcd_to_bin(t.year);
    }

    t.year += 2000; // Podés ajustar según siglo

    return t;
}

// Devuelve texto "HH:MM:SS" (necesitás buffer de al menos 9 bytes)
void rtc_format_time(char* buf, rtc_time_t* t) {
    buf[0] = '0' + (t->hour / 10);
    buf[1] = '0' + (t->hour % 10);
    buf[2] = ':';
    buf[3] = '0' + (t->minute / 10);
    buf[4] = '0' + (t->minute % 10);
    buf[5] = ':';
    buf[6] = '0' + (t->second / 10);
    buf[7] = '0' + (t->second % 10);
    buf[8] = '\0';
}

void rtc_init() {
   
    u8 prev = inb(CMOS_ADDRESS);
    outb(CMOS_ADDRESS, REG_STATUSB);
    u8 statusB = inb(CMOS_DATA);


    outb(CMOS_ADDRESS, REG_STATUSB);
    outb(CMOS_DATA, statusB | 0x40);


    outb(CMOS_ADDRESS, 0x0C);
    inb(CMOS_DATA);
    /// RTC INIT with MAIN CFG
}

