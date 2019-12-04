################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
..\Headers\Buttons.cpp \
..\Headers\Interpol.cpp \
..\Headers\Serial.cpp \
..\Headers\Telas.cpp 

LINK_OBJ += \
.\Headers\Buttons.cpp.o \
.\Headers\Interpol.cpp.o \
.\Headers\Serial.cpp.o \
.\Headers\Telas.cpp.o 

CPP_DEPS += \
.\Headers\Buttons.cpp.d \
.\Headers\Interpol.cpp.d \
.\Headers\Serial.cpp.d \
.\Headers\Telas.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
Headers\Buttons.cpp.o: ..\Headers\Buttons.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Sloeber\sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Sloeber\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.23\cores\arduino" -I"C:\Sloeber\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.23\variants\mega" -I"C:\Sloeber\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.7\src" -I"C:\Sloeber\sloeber\arduinoPlugin\libraries\Bounce2\2.52.0\src" -I"C:\Sloeber\sloeber\arduinoPlugin\libraries\Stepper\1.1.3\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Headers\Interpol.cpp.o: ..\Headers\Interpol.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Sloeber\sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Sloeber\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.23\cores\arduino" -I"C:\Sloeber\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.23\variants\mega" -I"C:\Sloeber\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.7\src" -I"C:\Sloeber\sloeber\arduinoPlugin\libraries\Bounce2\2.52.0\src" -I"C:\Sloeber\sloeber\arduinoPlugin\libraries\Stepper\1.1.3\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Headers\Serial.cpp.o: ..\Headers\Serial.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Sloeber\sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Sloeber\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.23\cores\arduino" -I"C:\Sloeber\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.23\variants\mega" -I"C:\Sloeber\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.7\src" -I"C:\Sloeber\sloeber\arduinoPlugin\libraries\Bounce2\2.52.0\src" -I"C:\Sloeber\sloeber\arduinoPlugin\libraries\Stepper\1.1.3\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Headers\Telas.cpp.o: ..\Headers\Telas.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Sloeber\sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Sloeber\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.23\cores\arduino" -I"C:\Sloeber\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.23\variants\mega" -I"C:\Sloeber\sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.7\src" -I"C:\Sloeber\sloeber\arduinoPlugin\libraries\Bounce2\2.52.0\src" -I"C:\Sloeber\sloeber\arduinoPlugin\libraries\Stepper\1.1.3\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


