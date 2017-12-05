################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GFX.c \
../LCD_ILI9341.c \
../TouchScreen.c \
../main.c \
../uart.c 

OBJS += \
./GFX.o \
./LCD_ILI9341.o \
./TouchScreen.o \
./main.o \
./uart.o 

C_DEPS += \
./GFX.d \
./LCD_ILI9341.d \
./TouchScreen.d \
./main.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


