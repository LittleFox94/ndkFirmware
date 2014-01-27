#include <asf.h>
#include <string.h>
#include <util/delay.h>

#include "application.h"
#include "device.h"

uint8_t _vendorClassBuffer[UDI_VENDOR_EPS_SIZE_BULK_FS];
uint8_t _serialNumberUSB[USB_DEVICE_GET_SERIAL_NAME_LENGTH + 1];

bool sendPending = false;

void main_vendor_bulk_in_received(udd_ep_status_t status, iram_size_t nb_transfered, udd_ep_id_t ep);
void main_vendor_bulk_out_received(udd_ep_status_t status, iram_size_t nb_transfered, udd_ep_id_t ep);

int main (void)
{	
	sysclk_init();
	irq_initialize_vectors();
	cpu_irq_enable();
	board_init();
	
	nvm_init(INT_EEPROM);
	nvm_init(INT_USERPAGE);
	
	uint32_t serial = GetSerialnumber();
	
	int i = USB_DEVICE_GET_SERIAL_NAME_LENGTH - 1;
	_serialNumberUSB[USB_DEVICE_GET_SERIAL_NAME_LENGTH] = 0;
	while(i >= 0)
	{
		_serialNumberUSB[i] = (serial % 10) + 0x30;
		serial /= 10;
		i--;
	}
	
	udc_start();
	
	if(!udc_include_vbus_monitoring())
	{
		vbus_action(true);
	}

	PORTD.DIR = 7;

	while(true)
	{		
	}
}

void vbus_action(bool b_vbus_high)
{
	if(b_vbus_high)
	{
		udc_attach();
	}
	else
	{
		udc_detach();
	}
}

bool vendor_enable()
{
	main_vendor_bulk_in_received(UDD_EP_TRANSFER_OK, 0, 0);
	return true;
}

void vendor_disable()
{
}

bool vendor_setup_out_received()
{
	udd_g_ctrlreq.payload = _vendorClassBuffer;
	udd_g_ctrlreq.payload_size = min(udd_g_ctrlreq.req.wLength, UDI_VENDOR_EPS_SIZE_BULK_FS);
	return true;
}

bool vendor_setup_in_received()
{
	udd_g_ctrlreq.payload = _vendorClassBuffer;
	udd_g_ctrlreq.payload_size = min(udd_g_ctrlreq.req.wLength, UDI_VENDOR_EPS_SIZE_BULK_FS);
	return true;
}

void main_vendor_bulk_in_received(udd_ep_status_t status, iram_size_t nb_transfered, udd_ep_id_t ep)
{
	if (UDD_EP_TRANSFER_OK != status) {
		return; // Transfer aborted, then stop loopback
	}
	
	udi_vendor_bulk_out_run(_vendorClassBuffer, UDI_VENDOR_EPS_SIZE_BULK_FS, main_vendor_bulk_out_received);
}

void main_vendor_bulk_out_received(udd_ep_status_t status, iram_size_t nb_transfered, udd_ep_id_t ep)
{
	if (UDD_EP_TRANSFER_OK != status) {
		return; // Transfer aborted, then stop loopback
	}
	
	Package* package = (Package*)_vendorClassBuffer;
	
	switch(package->RequestCode)
	{
		case 0x00:
		{
			// get serial number
			PackInteger32(package, GetSerialnumber());
			package->ResponseCode = RESPONSE_OK;
			break;
		}
		case 0x01:
		{
			// get hardware revision
			PackInteger16(package, GetHardwareRevision());
			package->ResponseCode = RESPONSE_OK;
			break;
		}
		case 0x02:
		{
			// get software revision
			PackInteger16(package, FIRMWARE_VERSION);
			package->ResponseCode = RESPONSE_OK;
			break;
		}
		case 0xF0:
		{
			package->Payload[0] = BOOTLOADER_BUILD;
			package->PayloadLength = 1;
			package->ResponseCode = RESPONSE_OK;
		}
	#if BOOTLOADER_BUILD == 1
		case 0xF1:
		{
			
		}
	#endif
		default:
		{
			package->ResponseCode = RESPONSE_UNKNOWN_CODE;
			break;
		}
	}
	
	udi_vendor_bulk_in_run(_vendorClassBuffer, UDI_VENDOR_EPS_SIZE_BULK_FS, main_vendor_bulk_in_received);
}

void PackInteger16(Package* package, uint16_t value)
{
	package->Payload[0] = value & 0xFF;
	package->Payload[1] = (value >> 8) & 0xFF;
	package->PayloadLength = 2;
}

void PackInteger32(Package* package, uint32_t value)
{
	package->Payload[0] = value & 0xFF;
	package->Payload[1] = (value >> 8) & 0xFF;
	package->Payload[2] = (value >> 16) & 0xFF;
	package->Payload[3] = (value >> 24) & 0xFF;
	package->PayloadLength = 4;
}
