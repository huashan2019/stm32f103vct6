################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/Sch/sch_common.c \
../Source/Sch/sch_message.c \
../Source/Sch/sch_printf.c \
../Source/Sch/sch_queue.c 

OBJS += \
./Source/Sch/sch_common.o \
./Source/Sch/sch_message.o \
./Source/Sch/sch_printf.o \
./Source/Sch/sch_queue.o 

C_DEPS += \
./Source/Sch/sch_common.d \
./Source/Sch/sch_message.d \
./Source/Sch/sch_printf.d \
./Source/Sch/sch_queue.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Sch/sch_common.o: ../Source/Sch/sch_common.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I"E:/project/DSP/16 chl DSP/SW/STM32CubeIDE/workspace_1.3.0/stm32f103vct6/Source/Sch" -I"E:/project/DSP/16 chl DSP/SW/STM32CubeIDE/workspace_1.3.0/stm32f103vct6/Source/common" -I"E:/project/DSP/16 chl DSP/SW/STM32CubeIDE/workspace_1.3.0/stm32f103vct6/Source/App" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../USB_DEVICE/App -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I"E:/project/DSP/16 chl DSP/SW/STM32CubeIDE/workspace_1.3.0/stm32f103vct6/Source/SigmaStudio_Dsp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/Sch/sch_common.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Source/Sch/sch_message.o: ../Source/Sch/sch_message.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I"E:/project/DSP/16 chl DSP/SW/STM32CubeIDE/workspace_1.3.0/stm32f103vct6/Source/Sch" -I"E:/project/DSP/16 chl DSP/SW/STM32CubeIDE/workspace_1.3.0/stm32f103vct6/Source/common" -I"E:/project/DSP/16 chl DSP/SW/STM32CubeIDE/workspace_1.3.0/stm32f103vct6/Source/App" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../USB_DEVICE/App -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I"E:/project/DSP/16 chl DSP/SW/STM32CubeIDE/workspace_1.3.0/stm32f103vct6/Source/SigmaStudio_Dsp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/Sch/sch_message.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Source/Sch/sch_printf.o: ../Source/Sch/sch_printf.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I"E:/project/DSP/16 chl DSP/SW/STM32CubeIDE/workspace_1.3.0/stm32f103vct6/Source/Sch" -I"E:/project/DSP/16 chl DSP/SW/STM32CubeIDE/workspace_1.3.0/stm32f103vct6/Source/common" -I"E:/project/DSP/16 chl DSP/SW/STM32CubeIDE/workspace_1.3.0/stm32f103vct6/Source/App" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../USB_DEVICE/App -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I"E:/project/DSP/16 chl DSP/SW/STM32CubeIDE/workspace_1.3.0/stm32f103vct6/Source/SigmaStudio_Dsp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/Sch/sch_printf.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Source/Sch/sch_queue.o: ../Source/Sch/sch_queue.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I"E:/project/DSP/16 chl DSP/SW/STM32CubeIDE/workspace_1.3.0/stm32f103vct6/Source/Sch" -I"E:/project/DSP/16 chl DSP/SW/STM32CubeIDE/workspace_1.3.0/stm32f103vct6/Source/common" -I"E:/project/DSP/16 chl DSP/SW/STM32CubeIDE/workspace_1.3.0/stm32f103vct6/Source/App" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../USB_DEVICE/App -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I"E:/project/DSP/16 chl DSP/SW/STM32CubeIDE/workspace_1.3.0/stm32f103vct6/Source/SigmaStudio_Dsp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/Sch/sch_queue.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

