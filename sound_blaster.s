; Sound Blaster System  - BearOS
; Creator: NopAngel - kernel system


%macro OUTB 2
    mov dx, %1
    mov al, %2
    out dx, al
%endmacro

%macro INB 1
    mov dx, %1
    in al, dx
%endmacro


;SOUND BLASTER 16 driver in real mode

  ;reset sound blaster
  OUTB 0x226, 1 ;reset port
  mov ah, 86h
  mov cx, 0x0000
  mov dx, 0xFFFF
  int 15h ;wait
  OUTB 0x226, 0 ;reset port
 
  ;turn speaker on
  OUTB 0x22C, 0xD1

  ;DMA channel 1
  OUTB 0x0A, 5 ;disable channel 1 (number of channel + 0x04)
  OUTB 0x0C, 1 ;flip flop
  OUTB 0x0B, 0x49 ;transfer mode
  OUTB 0x83, 0x01 ;PAGE TRANSFER (EXAMPLE POSITION IN MEMORY 0x[01]0F04) - SET THIS VALUE FOR YOU
  OUTB 0x02, 0x04 ;POSITION LOW BIT (EXAMPLE POSITION IN MEMORY 0x010F[04]) - SET THIS VALUE FOR YOU
  OUTB 0x02, 0x0F ;POSITON HIGH BIT (EXAMPLE POSITION IN MEMORY 0x01[0F]04) - SET THIS VALUE FOR YOU
  OUTB 0x03, 0xFF ;COUNT LOW BIT (EXAMPLE 0x0FFF) - SET THIS VALUE FOR YOU
  OUTB 0x03, 0x0F ;COUNT HIGH BIT (EXAMPLE 0x0FFF) - SET THIS VALUE FOR YOU
  OUTB 0x0A, 1 ;enable channel 1

  ;program sound blaster 16
  OUTB 0x22C, 0x40 ;set time constant
  OUTB 0x22C, 165 ;10989 Hz
  OUTB 0x22C, 0xC0 ;8 bit sound
  OUTB 0x22C, 0x00 ;mono and unsigned sound data
  OUTB 0x22C, 0xFE ;COUNT LOW BIT - COUNT LENGTH-1 (EXAMPLE 0x0FFF SO 0x0FFE) - SET THIS VALUE FOR YOU
  OUTB 0x22C, 0x0F ;COUNT HIGH BIT - COUNT LENGTH-1 (EXAMPLE 0x0FFF SO 0x0FFE) - SET THIS VALUE FOR YOU

  ;now transfer start - don't forget to handle irq
