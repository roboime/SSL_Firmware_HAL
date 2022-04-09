################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Components/motor_c.c 

CPP_SRCS += \
../Core/Src/Components/BTS7960B.cpp \
../Core/Src/Components/CommunicationUSB.cpp \
../Core/Src/Components/Dribble.cpp \
../Core/Src/Components/Encoder.cpp \
../Core/Src/Components/Kick.cpp \
../Core/Src/Components/Motor.cpp \
../Core/Src/Components/Robo.cpp \
../Core/Src/Components/RoboIME_RF24.cpp \
../Core/Src/Components/SerialDebug.cpp \
../Core/Src/Components/Start.cpp 

C_DEPS += \
./Core/Src/Components/motor_c.d 

OBJS += \
./Core/Src/Components/BTS7960B.o \
./Core/Src/Components/CommunicationUSB.o \
./Core/Src/Components/Dribble.o \
./Core/Src/Components/Encoder.o \
./Core/Src/Components/Kick.o \
./Core/Src/Components/Motor.o \
./Core/Src/Components/Robo.o \
./Core/Src/Components/RoboIME_RF24.o \
./Core/Src/Components/SerialDebug.o \
./Core/Src/Components/Start.o \
./Core/Src/Components/motor_c.o 

CPP_DEPS += \
./Core/Src/Components/BTS7960B.d \
./Core/Src/Components/CommunicationUSB.d \
./Core/Src/Components/Dribble.d \
./Core/Src/Components/Encoder.d \
./Core/Src/Components/Kick.d \
./Core/Src/Components/Motor.d \
./Core/Src/Components/Robo.d \
./Core/Src/Components/RoboIME_RF24.d \
./Core/Src/Components/SerialDebug.d \
./Core/Src/Components/Start.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Components/%.o Core/Src/Components/%.su: ../Core/Src/Components/%.cpp Core/Src/Components/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Lib -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/Components/%.o Core/Src/Components/%.su: ../Core/Src/Components/%.c Core/Src/Components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Lib -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Components

clean-Core-2f-Src-2f-Components:
	-$(RM) ./Core/Src/Components/BTS7960B.d ./Core/Src/Components/BTS7960B.o ./Core/Src/Components/BTS7960B.su ./Core/Src/Components/CommunicationUSB.d ./Core/Src/Components/CommunicationUSB.o ./Core/Src/Components/CommunicationUSB.su ./Core/Src/Components/Dribble.d ./Core/Src/Components/Dribble.o ./Core/Src/Components/Dribble.su ./Core/Src/Components/Encoder.d ./Core/Src/Components/Encoder.o ./Core/Src/Components/Encoder.su ./Core/Src/Components/Kick.d ./Core/Src/Components/Kick.o ./Core/Src/Components/Kick.su ./Core/Src/Components/Motor.d ./Core/Src/Components/Motor.o ./Core/Src/Components/Motor.su ./Core/Src/Components/Robo.d ./Core/Src/Components/Robo.o ./Core/Src/Components/Robo.su ./Core/Src/Components/RoboIME_RF24.d ./Core/Src/Components/RoboIME_RF24.o ./Core/Src/Components/RoboIME_RF24.su ./Core/Src/Components/SerialDebug.d ./Core/Src/Components/SerialDebug.o ./Core/Src/Components/SerialDebug.su ./Core/Src/Components/Start.d ./Core/Src/Components/Start.o ./Core/Src/Components/Start.su ./Core/Src/Components/motor_c.d ./Core/Src/Components/motor_c.o ./Core/Src/Components/motor_c.su

.PHONY: clean-Core-2f-Src-2f-Components

