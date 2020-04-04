################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DRIVER/LCD.c \
../DRIVER/UART.c \
../DRIVER/keypad.c 

OBJS += \
./DRIVER/LCD.o \
./DRIVER/UART.o \
./DRIVER/keypad.o 

C_DEPS += \
./DRIVER/LCD.d \
./DRIVER/UART.d \
./DRIVER/keypad.d 


# Each subdirectory must supply rules for building sources it contributes
DRIVER/%.o: ../DRIVER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


