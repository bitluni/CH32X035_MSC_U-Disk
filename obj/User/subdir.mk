################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/Internal_Flash.c \
../User/SPI_FLASH.c \
../User/SW_UDISK.c \
../User/ch32x035_it.c \
../User/ch32x035_usbfs_device.c \
../User/main.c \
../User/system_ch32x035.c \
../User/usb_desc.c 

OBJS += \
./User/Internal_Flash.o \
./User/SPI_FLASH.o \
./User/SW_UDISK.o \
./User/ch32x035_it.o \
./User/ch32x035_usbfs_device.o \
./User/main.o \
./User/system_ch32x035.o \
./User/usb_desc.o 

C_DEPS += \
./User/Internal_Flash.d \
./User/SPI_FLASH.d \
./User/SW_UDISK.d \
./User/ch32x035_it.d \
./User/ch32x035_usbfs_device.d \
./User/main.d \
./User/system_ch32x035.d \
./User/usb_desc.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

