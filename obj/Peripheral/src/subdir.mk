################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_adc.c \
G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_awu.c \
G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_dbgmcu.c \
G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_dma.c \
G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_exti.c \
G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_flash.c \
G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_gpio.c \
G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_i2c.c \
G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_iwdg.c \
G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_misc.c \
G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_opa.c \
G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_pwr.c \
G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_rcc.c \
G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_spi.c \
G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_tim.c \
G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_usart.c \
G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_wwdg.c 

OBJS += \
./Peripheral/src/ch32x035_adc.o \
./Peripheral/src/ch32x035_awu.o \
./Peripheral/src/ch32x035_dbgmcu.o \
./Peripheral/src/ch32x035_dma.o \
./Peripheral/src/ch32x035_exti.o \
./Peripheral/src/ch32x035_flash.o \
./Peripheral/src/ch32x035_gpio.o \
./Peripheral/src/ch32x035_i2c.o \
./Peripheral/src/ch32x035_iwdg.o \
./Peripheral/src/ch32x035_misc.o \
./Peripheral/src/ch32x035_opa.o \
./Peripheral/src/ch32x035_pwr.o \
./Peripheral/src/ch32x035_rcc.o \
./Peripheral/src/ch32x035_spi.o \
./Peripheral/src/ch32x035_tim.o \
./Peripheral/src/ch32x035_usart.o \
./Peripheral/src/ch32x035_wwdg.o 

C_DEPS += \
./Peripheral/src/ch32x035_adc.d \
./Peripheral/src/ch32x035_awu.d \
./Peripheral/src/ch32x035_dbgmcu.d \
./Peripheral/src/ch32x035_dma.d \
./Peripheral/src/ch32x035_exti.d \
./Peripheral/src/ch32x035_flash.d \
./Peripheral/src/ch32x035_gpio.d \
./Peripheral/src/ch32x035_i2c.d \
./Peripheral/src/ch32x035_iwdg.d \
./Peripheral/src/ch32x035_misc.d \
./Peripheral/src/ch32x035_opa.d \
./Peripheral/src/ch32x035_pwr.d \
./Peripheral/src/ch32x035_rcc.d \
./Peripheral/src/ch32x035_spi.d \
./Peripheral/src/ch32x035_tim.d \
./Peripheral/src/ch32x035_usart.d \
./Peripheral/src/ch32x035_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
Peripheral/src/ch32x035_adc.o: G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_adc.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32x035_awu.o: G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_awu.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32x035_dbgmcu.o: G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_dbgmcu.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32x035_dma.o: G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_dma.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32x035_exti.o: G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_exti.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32x035_flash.o: G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_flash.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32x035_gpio.o: G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_gpio.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32x035_i2c.o: G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_i2c.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32x035_iwdg.o: G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_iwdg.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32x035_misc.o: G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_misc.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32x035_opa.o: G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_opa.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32x035_pwr.o: G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_pwr.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32x035_rcc.o: G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_rcc.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32x035_spi.o: G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32x035_tim.o: G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_tim.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32x035_usart.o: G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_usart.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32x035_wwdg.o: G:/My\ Drive/Code/RiscV/CH32X035/EVT/EXAM/SRC/Peripheral/src/ch32x035_wwdg.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Debug" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Core" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\USB\USBFS\DEVICE\MSC_U-Disk\User" -I"G:\My Drive\Code\RiscV\CH32X035\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

