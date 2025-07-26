#ifndef WMSG_H
#define WMSG_H

#include "../../fs/k_printf.h"


#define WHITE_TXT 0x07
#define GRAY_TXT 0x08
#define AQUA_TXT 0x03
#define RED_TXT 0x04
#define BLUE_TXT 0x09
#define PURPLE_TXT 0x07
#define ORANGE_TXT 0x06
#define BLACK_TXT 0x00
#define PINK_TXT 0x05
#define GREEN_TXT 0x02
#define DARKBLUE_TXT 0x01
#define YELLOW_TXT 0x0E

#define RED_TXT_BG 0x44
#define AQUA_TXT_BG 0x33
#define WHITE_TXT_BG 0x77
#define BLUE_TXT_BG 0x99
#define GREEN_TXT_BG 0x22
#define PURPLE_TXT_BG 0x77
#define PINK_TXT_BG 0x55

#define WHITE_BG 0x70											//#define BLUECRYSTAL_TXT 0x90
#define GRAY_BG 0x80
#define AQUA_BG 0x30
#define RED_BG 0x40
#define BLUE_BG 0x90
#define PURPLE_BG 0x70
#define ORANGE_BG 0x60
#define BLACK_BG 0x00
#define PINK_BG 0x50
#define GREEN_BG 0x20
#define DARKBLUE_BG 0x10


void W_MSG();

#endif