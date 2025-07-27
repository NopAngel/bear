#ifndef _ATA_DRIVER_H
#define _ATA_DRIVER_H

#define ATA_PRIMARY_BASE 0x1F0
#define ATA_CMD_READ 0x20

void ata_read_sector(unsigned int lba, unsigned char *buffer);

#endif