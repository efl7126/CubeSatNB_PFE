################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ax25.c \
../Src/cc112x_spi.c \
../Src/cc_tx_init.c \
../Src/comms_manager.c \
../Src/cw.c \
../Src/lfsr.c \
../Src/main.c \
../Src/pfe_fonctionsUtilisateur.c \
../Src/scrambler.c \
../Src/stats.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f4xx.c \
../Src/tx_manager.c \
../Src/usb_device.c \
../Src/usbd_cdc_if.c \
../Src/usbd_conf.c \
../Src/usbd_desc.c \
../Src/wod_handling.c 

OBJS += \
./Src/ax25.o \
./Src/cc112x_spi.o \
./Src/cc_tx_init.o \
./Src/comms_manager.o \
./Src/cw.o \
./Src/lfsr.o \
./Src/main.o \
./Src/pfe_fonctionsUtilisateur.o \
./Src/scrambler.o \
./Src/stats.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f4xx.o \
./Src/tx_manager.o \
./Src/usb_device.o \
./Src/usbd_cdc_if.o \
./Src/usbd_conf.o \
./Src/usbd_desc.o \
./Src/wod_handling.o 

C_DEPS += \
./Src/ax25.d \
./Src/cc112x_spi.d \
./Src/cc_tx_init.d \
./Src/comms_manager.d \
./Src/cw.d \
./Src/lfsr.d \
./Src/main.d \
./Src/pfe_fonctionsUtilisateur.d \
./Src/scrambler.d \
./Src/stats.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f4xx.d \
./Src/tx_manager.d \
./Src/usb_device.d \
./Src/usbd_cdc_if.d \
./Src/usbd_conf.d \
./Src/usbd_desc.d \
./Src/wod_handling.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Communications/Projet4_1_AX25/Inc" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Communications/Projet4_1_AX25/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Communications/Projet4_1_AX25/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Communications/Projet4_1_AX25/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Communications/Projet4_1_AX25/Drivers/CMSIS/Include" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Communications/Projet2_2_CWAjoutDeWOD/Middlewares/ST/STM32_USB_Device_Library" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Communications/Projet2_2_CWAjoutDeWOD/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Communications/Projet2_2_CWAjoutDeWOD/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Communications/Projet2_2_CWAjoutDeWOD/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Communications/Projet4_1_AX25/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Communications/Projet2_2_CWAjoutDeWOD_USB/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Communications/Projet2_2_CWAjoutDeWOD_USB/Drivers/STM32F4xx_HAL_Driver/Src" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Communications/Projet4_1_AX25/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Communications/Projet2_5_CWAjoutDeWOD_CWFonctionnel/ecss_services" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Communications/Projet3_3_WOD_UART/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Communications/Projet3_3_WOD_UART/Drivers/STM32F4xx_HAL_Driver/Src" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Communications/Projet4_1_AX25/ecss_services"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


