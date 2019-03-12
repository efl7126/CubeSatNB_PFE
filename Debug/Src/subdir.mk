################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/cc112x_spi.c \
../Src/cc_tx_init.c \
../Src/comms_manager.c \
../Src/cw.c \
../Src/main.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c \
../Src/tx_manager.c 

OBJS += \
./Src/cc112x_spi.o \
./Src/cc_tx_init.o \
./Src/comms_manager.o \
./Src/cw.o \
./Src/main.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o \
./Src/tx_manager.o 

C_DEPS += \
./Src/cc112x_spi.d \
./Src/cc_tx_init.d \
./Src/comms_manager.d \
./Src/cw.d \
./Src/main.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d \
./Src/tx_manager.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Tests/Test3_CC1120_Simple/Inc" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Tests/Test3_CC1120_Simple/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Tests/Test3_CC1120_Simple/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Tests/Test3_CC1120_Simple/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/franc/Documents/_Hiver2019/PFE/Codes/Tests/Test3_CC1120_Simple/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


