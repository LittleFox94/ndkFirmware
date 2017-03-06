#!/bin/bash

TOOLCHAIN_PATH=/opt/avr8-gnu-toolchain-linux_x86_64/bin
PART=atxmega32a4u
CCFLAGS="-DBOARD=USER_BOARD -O3"
ASFLAGS=""

CCFILES="main.c
device.c
ASF/xmega/drivers/nvm/nvm.c
ASF/common/services/usb/class/hid/device/udi_hid.c
ASF/common/services/usb/class/hid/device/kbd/udi_hid_kbd.c
ASF/common/boards/user_board/init.c
ASF/xmega/drivers/usb/usb_device.c
ASF/common/drivers/nvm/xmega/xmega_nvm.c
ASF/common/services/clock/xmega/sysclk.c
ASF/common/services/sleepmgr/xmega/sleepmgr.c
ASF/common/services/usb/class/cdc/device/udi_cdc.c
ASF/common/services/usb/class/composite/device/udi_composite_desc.c
ASF/common/services/usb/class/vendor/device/udi_vendor.c
ASF/common/services/usb/udc/udc.c
"
ASFILES="ASF/xmega/drivers/cpu/ccp.S
ASF/xmega/drivers/nvm/nvm_asm.S
"

CC="$TOOLCHAIN_PATH/avr-gcc -Wl,--section-start=.BOOT=0x8000 -mmcu=$PART $CCFLAGS"
OBJCOPY="$TOOLCHAIN_PATH/avr-objcopy"

INCLUDE_PATHS="-I. -IASF/xmega/drivers/cpu/ -IASF/xmega/utils/ -IASF/common/utils/ -IASF/xmega/drivers/usb/ -Iconfig/ -IASF/common/drivers/nvm/ -IASF/xmega/utils/preprocessor/ -IASF/common/boards/user_board/ -IASF/xmega/utils/assembler/ -IASF/xmega/utils/bit_handling/ -IASF/xmega/drivers/nvm/ -IASF/common/boards/ -IASF/xmega/drivers/sleep/ -IASF/common/services/sleepmgr/ -IASF/common/services/clock/ -IASF/common/services/usb/udc/ -IASF/common/services/usb/class/hid/device/kbd/ -IASF/common/services/usb/ -IASF/common/services/usb/class/hid/ -IASF/common/services/usb/class/cdc/ -IASF/common/services/usb/class/cdc/device -IASF/common/services/usb/class/vendor/ -IASF/common/services/usb/class/vendor/device/ -IASF/common/services/usb/class/hid/device/"

compilefiles=$(echo "$CCFILES $ASFILES" | sed ':a;N;$!ba;s/\n/ /g')
$CC $INCLUDE_PATHS $CCFLAGS $compilefiles -o test.elf
$OBJCOPY -O ihex test.elf test.hex
