################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
touch_screen_demo.lss \

FLASH_IMAGE += \
touch_screen_demo.hex \

EEPROM_IMAGE += \
touch_screen_demo.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: touch_screen_demo.elf secondary-outputs

# Tool invocations
touch_screen_demo.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,touch_screen_demo.map -mmcu=atmega328p -o "touch_screen_demo.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

touch_screen_demo.lss: touch_screen_demo.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S touch_screen_demo.elf  >"touch_screen_demo.lss"
	@echo 'Finished building: $@'
	@echo ' '

touch_screen_demo.hex: touch_screen_demo.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex touch_screen_demo.elf  "touch_screen_demo.hex"
	@echo 'Finished building: $@'
	@echo ' '

touch_screen_demo.eep: touch_screen_demo.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex touch_screen_demo.elf  "touch_screen_demo.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: touch_screen_demo.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p touch_screen_demo.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) touch_screen_demo.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
