################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ON_OFF_GPIO.c \
../src/UART.c \
../src/_write.c \
../src/adc.c \
../src/interrupt_gpio.c \
../src/main.c \
../src/timer.c 

OBJS += \
./src/ON_OFF_GPIO.o \
./src/UART.o \
./src/_write.o \
./src/adc.o \
./src/interrupt_gpio.o \
./src/main.o \
./src/timer.o 

C_DEPS += \
./src/ON_OFF_GPIO.d \
./src/UART.d \
./src/_write.d \
./src/adc.d \
./src/interrupt_gpio.d \
./src/main.d \
./src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


