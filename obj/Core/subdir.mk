################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Core/core_riscv.c 

OBJS += \
./Core/core_riscv.o 

C_DEPS += \
./Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
Core/core_riscv.o: G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Core/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

