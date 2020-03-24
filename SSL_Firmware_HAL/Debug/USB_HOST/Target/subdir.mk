################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB_HOST/Target/usbh_conf.c 

OBJS += \
./USB_HOST/Target/usbh_conf.o 

C_DEPS += \
./USB_HOST/Target/usbh_conf.d 


# Each subdirectory must supply rules for building sources it contributes
USB_HOST/Target/usbh_conf.o: ../USB_HOST/Target/usbh_conf.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../USB_HOST/App -IC:/Users/Gabriel/STM32Cube/Repository/STM32Cube_FW_F4_V1.24.2/Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -IC:/Users/Gabriel/STM32Cube/Repository/STM32Cube_FW_F4_V1.24.2/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/Gabriel/STM32Cube/Repository/STM32Cube_FW_F4_V1.24.2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/Gabriel/STM32Cube/Repository/STM32Cube_FW_F4_V1.24.2/Drivers/CMSIS/Include -I../USB_HOST/Target -IC:/Users/Gabriel/STM32Cube/Repository/STM32Cube_FW_F4_V1.24.2/Middlewares/ST/STM32_USB_Host_Library/Core/Inc -IC:/Users/Gabriel/STM32Cube/Repository/STM32Cube_FW_F4_V1.24.2/Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"USB_HOST/Target/usbh_conf.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

