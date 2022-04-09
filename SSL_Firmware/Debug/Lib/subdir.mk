################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/Feedback.pb.c \
../Lib/grSim_Commands.pb.c \
../Lib/pb_common.c \
../Lib/pb_decode.c \
../Lib/pb_encode.c 

C_DEPS += \
./Lib/Feedback.pb.d \
./Lib/grSim_Commands.pb.d \
./Lib/pb_common.d \
./Lib/pb_decode.d \
./Lib/pb_encode.d 

OBJS += \
./Lib/Feedback.pb.o \
./Lib/grSim_Commands.pb.o \
./Lib/pb_common.o \
./Lib/pb_decode.o \
./Lib/pb_encode.o 


# Each subdirectory must supply rules for building sources it contributes
Lib/%.o Lib/%.su: ../Lib/%.c Lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Lib -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Lib

clean-Lib:
	-$(RM) ./Lib/Feedback.pb.d ./Lib/Feedback.pb.o ./Lib/Feedback.pb.su ./Lib/grSim_Commands.pb.d ./Lib/grSim_Commands.pb.o ./Lib/grSim_Commands.pb.su ./Lib/pb_common.d ./Lib/pb_common.o ./Lib/pb_common.su ./Lib/pb_decode.d ./Lib/pb_decode.o ./Lib/pb_decode.su ./Lib/pb_encode.d ./Lib/pb_encode.o ./Lib/pb_encode.su

.PHONY: clean-Lib

