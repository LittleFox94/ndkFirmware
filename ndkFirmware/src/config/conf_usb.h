/**
 * \file
 *
 * \brief USB configuration file
 *
 * Copyright (c) 2009 - 2013 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#ifndef _CONF_USB_H_
#define _CONF_USB_H_

#include "compiler.h"

/**
 * USB Device Configuration
 * @{
 */

//! Device definition (mandatory)
#define  USB_DEVICE_VENDOR_ID				0x1337
#define  USB_DEVICE_PRODUCT_ID				0x1F05
#define  USB_DEVICE_MAJOR_VERSION			1
#define  USB_DEVICE_MINOR_VERSION			0
#define  USB_DEVICE_POWER					100 // Consumption on Vbus line (mA)
#define  USB_DEVICE_ATTR					(USB_CONFIG_ATTR_BUS_POWERED | USB_CONFIG_ATTR_MUST_SET)

//! USB Device string definitions (Optional)
#define  USB_DEVICE_MANUFACTURE_NAME		"LittleFox"
#define  USB_DEVICE_PRODUCT_NAME			"non-destructable Keyboard"

#define  USB_DEVICE_SERIAL_NAME
#define	 USB_DEVICE_GET_SERIAL_NAME_LENGTH	8
#define  USB_DEVICE_GET_SERIAL_NAME_POINTER	_serialNumberUSB

extern uint8_t _serialNumberUSB[];

/**
 * Device speeds support
 * @{
 */
//! To define a Low speed device
//#define  USB_DEVICE_LOW_SPEED

//! To authorize the High speed
#if (UC3A3||UC3A4)
//#define  USB_DEVICE_HS_SUPPORT
#endif
//@}

/**
 * USB Device Callbacks definitions (Optional)
 * @{
 */
#define  UDC_VBUS_EVENT(b_vbus_high)      vbus_action(b_vbus_high)
extern void vbus_action(bool b_vbus_high);
#define  UDC_SOF_EVENT()                  sof_action()
extern void sof_action(void);
// #define  UDC_SUSPEND_EVENT()              user_callback_suspend_action()
// extern void user_callback_suspend_action(void);
// #define  UDC_RESUME_EVENT()               user_callback_resume_action()
// extern void user_callback_resume_action(void);
//! Mandatory when USB_DEVICE_ATTR authorizes remote wakeup feature
// #define  UDC_REMOTEWAKEUP_ENABLE()        user_callback_remotewakeup_enable()
// extern void user_callback_remotewakeup_enable(void);
// #define  UDC_REMOTEWAKEUP_DISABLE()       user_callback_remotewakeup_disable()
// extern void user_callback_remotewakeup_disable(void);
//! When a extra string descriptor must be supported
//! other than manufacturer, product and serial string
//#define  UDC_GET_EXTRA_STRING()
//@}

/**
 * USB Device low level configuration
 * When only one interface is used, these configurations are defined by the class module.
 * For composite device, these configuration must be defined here
 * @{
 */
//! Control endpoint size
#define  USB_DEVICE_EP_CTRL_SIZE       64

//! Number of interfaces for this device
#define  USB_DEVICE_NB_INTERFACE       8 // 1 or more

//! Total endpoint used by all interfaces
//! Note:
//! It is possible to define an IN and OUT endpoints with the same number on XMEGA product only
//! E.g. MSC class can be have IN endpoint 0x81 and OUT endpoint 0x01
#define  USB_DEVICE_MAX_EP             12 // 0 to max endpoint requested by interfaces
//@}

//@}


/**
 * USB Interface Configuration
 * @{
 */

/**
 * Configuration of CDC interface (if used)
 * @{
 */

//! Number of communication port used (1 to 3)
#define  UDI_CDC_PORT_NB 3

//! Interface callback definition
#define  UDI_CDC_ENABLE_EXT(port)             true
#define  UDI_CDC_DISABLE_EXT(port)
#define  UDI_CDC_RX_NOTIFY(port)
#define  UDI_CDC_TX_EMPTY_NOTIFY(port)
#define  UDI_CDC_SET_CODING_EXT(port,cfg)
#define  UDI_CDC_SET_DTR_EXT(port,set)
#define  UDI_CDC_SET_RTS_EXT(port,set)
/*
 * #define UDI_CDC_ENABLE_EXT(port) my_callback_cdc_enable()
 * extern bool my_callback_cdc_enable(void);
 * #define UDI_CDC_DISABLE_EXT(port) my_callback_cdc_disable()
 * extern void my_callback_cdc_disable(void);
 * #define  UDI_CDC_RX_NOTIFY(port) my_callback_rx_notify(port)
 * extern void my_callback_rx_notify(uint8_t port);
 * #define  UDI_CDC_TX_EMPTY_NOTIFY(port) my_callback_tx_empty_notify(port)
 * extern void my_callback_tx_empty_notify(uint8_t port);
 * #define  UDI_CDC_SET_CODING_EXT(port,cfg) my_callback_config(port,cfg)
 * extern void my_callback_config(uint8_t port, usb_cdc_line_coding_t * cfg); 
 * #define  UDI_CDC_SET_DTR_EXT(port,set) my_callback_cdc_set_dtr(port,set)
 * extern void my_callback_cdc_set_dtr(uint8_t port, bool b_enable);
 * #define  UDI_CDC_SET_RTS_EXT(port,set) my_callback_cdc_set_rts(port,set)
 * extern void my_callback_cdc_set_rts(uint8_t port, bool b_enable); 
 */

//! Define it when the transfer CDC Device to Host is a low rate (<512000 bauds)
//! to reduce CDC buffers size
#define  UDI_CDC_LOW_RATE

//! Default configuration of communication port
#define  UDI_CDC_DEFAULT_RATE             115200
#define  UDI_CDC_DEFAULT_STOPBITS         CDC_STOP_BITS_1
#define  UDI_CDC_DEFAULT_PARITY           CDC_PAR_NONE
#define  UDI_CDC_DEFAULT_DATABITS         8

/**
 * USB CDC low level configuration
 * In standalone these configurations are defined by the CDC module.
 * For composite device, these configuration must be defined here
 * @{
 */
//! Endpoints' numbers used by single or first CDC port
#define  UDI_CDC_DATA_EP_IN_0          (2 | USB_EP_DIR_IN)  // TX
#define  UDI_CDC_DATA_EP_OUT_0         (3 | USB_EP_DIR_OUT) // RX
#define  UDI_CDC_COMM_EP_0             (4 | USB_EP_DIR_IN)  // Notify endpoint
//! Endpoints' numbers used by second CDC port (Optional)
#define  UDI_CDC_DATA_EP_IN_1          (5 | USB_EP_DIR_IN)  // TX
#define  UDI_CDC_DATA_EP_OUT_1         (6 | USB_EP_DIR_OUT) // RX
#define  UDI_CDC_COMM_EP_1             (7 | USB_EP_DIR_IN)  // Notify endpoint
//! Endpoints' numbers used by third CDC port (Optional)
#define  UDI_CDC_DATA_EP_IN_2          (8 | USB_EP_DIR_IN)  // TX
#define  UDI_CDC_DATA_EP_OUT_2         (9 | USB_EP_DIR_OUT) // RX
#define  UDI_CDC_COMM_EP_2             (10 | USB_EP_DIR_IN)  // Notify endpoint

//! Interface numbers used by single or first CDC port
#define  UDI_CDC_COMM_IFACE_NUMBER_0   1
#define  UDI_CDC_DATA_IFACE_NUMBER_0   2
//! Interface numbers used by second CDC port (Optional)
#define  UDI_CDC_COMM_IFACE_NUMBER_1   3
#define  UDI_CDC_DATA_IFACE_NUMBER_1   4
//! Interface numbers used by third CDC port (Optional)
#define  UDI_CDC_COMM_IFACE_NUMBER_2   5
#define  UDI_CDC_DATA_IFACE_NUMBER_2   6
//@}
//@}


/**
 * Configuration of HID Keyboard interface (if used)
 * @{
 */
//! Interface callback definition
#define  UDI_HID_KBD_ENABLE_EXT()       true
#define  UDI_HID_KBD_DISABLE_EXT()
//#define UDI_HID_KBD_ENABLE_EXT() keyboard_enable()
//extern bool keyboard_enable(void);
// #define UDI_HID_KBD_DISABLE_EXT() my_callback_keyboard_disable()
// extern void my_callback_keyboard_disable(void);
#define  UDI_HID_KBD_CHANGE_LED(value)
// #define  UDI_HID_KBD_CHANGE_LED(value) my_callback_keyboard_led(value)
// extern void my_callback_keyboard_led(uint8_t value)

/**
 * USB HID Keyboard low level configuration
 * In standalone these configurations are defined by the HID Keyboard module.
 * For composite device, these configuration must be defined here
 * @{
 */
//! Endpoint numbers definition
#define  UDI_HID_KBD_EP_IN           (11 | USB_EP_DIR_IN)

//! Interface number
#define  UDI_HID_KBD_IFACE_NUMBER    7
//@}
//@}


/**
 * Configuration of Class Vendor interface (if used)
 * @{
 */

//! Interface callback definition
#define UDI_VENDOR_ENABLE_EXT() vendor_enable()
extern bool vendor_enable(void);
#define UDI_VENDOR_DISABLE_EXT() vendor_disable()
extern void vendor_disable(void);

#define  UDI_VENDOR_SETUP_OUT_RECEIVED()  vendor_setup_out_received()
extern bool vendor_setup_out_received(void);
#define  UDI_VENDOR_SETUP_IN_RECEIVED()   vendor_setup_in_received()
extern bool vendor_setup_in_received(void);

#define UDI_VENDOR_BULK_

//! endpoints size for full speed
#define  UDI_VENDOR_EPS_SIZE_INT_FS		0
#define  UDI_VENDOR_EPS_SIZE_BULK_FS	64
#define  UDI_VENDOR_EPS_SIZE_ISO_FS		0

//! endpoints size for high speed
#define  UDI_VENDOR_EPS_SIZE_INT_HS		0
#define  UDI_VENDOR_EPS_SIZE_BULK_HS	64
#define  UDI_VENDOR_EPS_SIZE_ISO_HS		0

/**
 * USB Class Vendor low level configuration
 * In standalone these configurations are defined by the Class Vendor module.
 * For composite device, these configuration must be defined here
 * @{
 */
//! Endpoint numbers definition
//#define  UDI_VENDOR_EP_INTERRUPT_IN  (11 | USB_EP_DIR_IN)
//#define  UDI_VENDOR_EP_INTERRUPT_OUT (11 | USB_EP_DIR_OUT)
#define  UDI_VENDOR_EP_BULK_IN       (1 | USB_EP_DIR_IN)
#define  UDI_VENDOR_EP_BULK_OUT      (1 | USB_EP_DIR_OUT)
//#define  UDI_VENDOR_EP_ISO_IN        (15 | USB_EP_DIR_IN)
//#define  UDI_VENDOR_EP_ISO_OUT       (16 | USB_EP_DIR_OUT)

//! Interface number
#define UDI_VENDOR_IFACE_NUMBER		0
//@}
//@}

//@}


/**
 * Description of Composite Device
 * @{
 */
//! USB Interfaces descriptor structure
#define UDI_COMPOSITE_DESC_T \
	udi_vendor_desc_t udi_vendor; \
	\
	usb_iad_desc_t udi_cdc_iad0; \
	udi_cdc_comm_desc_t udi_cdc_comm0; \
	udi_cdc_data_desc_t udi_cdc_data0; \
	\
	usb_iad_desc_t udi_cdc_iad1; \
	udi_cdc_comm_desc_t udi_cdc_comm1; \
	udi_cdc_data_desc_t udi_cdc_data1; \
	\
	usb_iad_desc_t udi_cdc_iad2; \
	udi_cdc_comm_desc_t udi_cdc_comm2; \
	udi_cdc_data_desc_t udi_cdc_data2; \
	\
	udi_hid_kbd_desc_t udi_hid_keyboard;

//! USB Interfaces descriptor value for Full Speed
#define UDI_COMPOSITE_DESC_FS \
	.udi_vendor			= UDI_VENDOR_DESC_FS, \
	\
	.udi_cdc_iad0		= UDI_CDC_IAD_DESC_0, \
	.udi_cdc_comm0		= UDI_CDC_COMM_DESC_0, \
	.udi_cdc_data0		= UDI_CDC_DATA_DESC_0_FS, \
	\
	.udi_cdc_iad1		= UDI_CDC_IAD_DESC_1, \
	.udi_cdc_comm1		= UDI_CDC_COMM_DESC_1, \
	.udi_cdc_data1		= UDI_CDC_DATA_DESC_1_FS, \
	\
	.udi_cdc_iad2		= UDI_CDC_IAD_DESC_2, \
	.udi_cdc_comm2		= UDI_CDC_COMM_DESC_2, \
	.udi_cdc_data2		= UDI_CDC_DATA_DESC_2_FS, \
	\
	.udi_hid_keyboard	= UDI_HID_KBD_DESC, \
	

//! USB Interfaces descriptor value for High Speed
#define UDI_COMPOSITE_DESC_HS \
	.udi_vendor			= UDI_VENDOR_DESC_HS, \
	\
	.udi_cdc_iad0		= UDI_CDC_IAD_DESC_0, \
	.udi_cdc_comm0		= UDI_CDC_COMM_DESC_0, \
	.udi_cdc_data0		= UDI_CDC_DATA_DESC_0_HS, \
	\
	.udi_cdc_iad1		= UDI_CDC_IAD_DESC_1, \
	.udi_cdc_comm1		= UDI_CDC_COMM_DESC_1, \
	.udi_cdc_data1		= UDI_CDC_DATA_DESC_1_HS, \
	\
	.udi_cdc_iad2		= UDI_CDC_IAD_DESC_2, \
	.udi_cdc_comm2		= UDI_CDC_COMM_DESC_2, \
	.udi_cdc_data2		= UDI_CDC_DATA_DESC_2_HS, \
	\
	.udi_hid_keyboard	= UDI_HID_KBD_DESC, \

//! USB Interface APIs
#define UDI_COMPOSITE_API \
	&udi_api_vendor, \
	&udi_api_cdc_comm, \
	&udi_api_cdc_data, \
	&udi_api_cdc_comm, \
	&udi_api_cdc_data, \
	&udi_api_cdc_comm, \
	&udi_api_cdc_data, \
	&udi_api_hid_kbd

//@}


//! The includes of classes and other headers must be done at the end of this file to avoid compile error

/* Example of include for interface */
#include "udi_hid_kbd.h"
#include "udi_cdc.h"
#include "udi_vendor.h"

/* Declaration of callbacks used by USB
#include "callback_def.h"
*/

#endif // _CONF_USB_H_
