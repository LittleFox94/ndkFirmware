/*
 * application.h
 *
 * Created: 22.01.2014 06:09:56
 *  Author: Moritz
 */ 


#ifndef APPLICATION_H_
#define APPLICATION_H_

#define BOOTLOADER_BUILD		0
#define FIRMWARE_VERSION		1

#define RESPONSE_INVALID		0x00
#define RESPONSE_UNKNOWN_CODE	0x01
#define RESPONSE_OK				0xFF

typedef struct {
	uint8_t RequestCode;
	uint8_t ResponseCode;
	uint8_t PayloadLength;
	uint8_t Reserved;
	uint8_t Payload[60];
} Package;

void PackInteger16(Package* package, uint16_t value);
void PackInteger32(Package* package, uint32_t value);

#endif /* APPLICATION_H_ */