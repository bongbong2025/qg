#ifndef __EEPROM_H__
#define __EEPROM_H__

void eeprom_write_onebyte(unsigned char addr, unsigned char dat);
unsigned char eeprom_read_onebyte(unsigned char addr);

#endif