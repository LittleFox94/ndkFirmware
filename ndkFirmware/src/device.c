/*
 * device.c
 *
 * Created: 23.01.2014 20:18:41
 *  Author: Moritz
 */ 

#include <avr/io.h>
#include "asf.h"

#include "device.h"

uint32_t GetSerialnumber()
{
	uint8_t usersig[4];
	usersig[0] = nvm_read_user_signature_row(0);
	usersig[1] = nvm_read_user_signature_row(1);
	usersig[2] = nvm_read_user_signature_row(2);
	usersig[3] = nvm_read_user_signature_row(3);
	
	uint32_t serial = (uint32_t)usersig[0];
	serial |= (uint32_t)usersig[1] << 8;
	serial |= (uint32_t)usersig[2] << 16;
	serial |= (uint32_t)usersig[3] << 24;
	
	return serial;
}

uint16_t GetHardwareRevision()
{
	uint8_t usersig[2];
	usersig[0] = nvm_read_user_signature_row(4);
	usersig[1] = nvm_read_user_signature_row(5);
	
	uint16_t hwrev = usersig[0];
	hwrev |= usersig[1] << 8;
	
	return hwrev;
}

uint16_t GetFlashCounter()
{
	uint8_t eeprom[2];
	nvm_eeprom_read_buffer(0, eeprom, 2);
	
	uint16_t flashcount = eeprom[0];
	flashcount |= eeprom[1] << 8;
	
	return flashcount;
}