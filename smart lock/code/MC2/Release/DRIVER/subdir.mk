################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DRIVER/I2C.c \
../DRIVER/TIMER.c \
../DRIVER/UART.c 

OBJS += \
./DRIVER/I2C.o \
./DRIVER/TIMER.o \
./DRIVER/UART.o 

C_DEPS += \
./DRIVER/I2C.d \
./DRIVER/TIMER.d \
./DRIVER/UART.d 


# Each subdirectory must supply rules for building sources it contributes
DRIVER/%.o: ../DRIVER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


