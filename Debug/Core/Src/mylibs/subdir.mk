################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/mylibs/codeur.c \
../Core/Src/mylibs/pid_controller.c \
../Core/Src/mylibs/pwm.c \
../Core/Src/mylibs/shell.c 

OBJS += \
./Core/Src/mylibs/codeur.o \
./Core/Src/mylibs/pid_controller.o \
./Core/Src/mylibs/pwm.o \
./Core/Src/mylibs/shell.o 

C_DEPS += \
./Core/Src/mylibs/codeur.d \
./Core/Src/mylibs/pid_controller.d \
./Core/Src/mylibs/pwm.d \
./Core/Src/mylibs/shell.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/mylibs/%.o Core/Src/mylibs/%.su Core/Src/mylibs/%.cyclo: ../Core/Src/mylibs/%.c Core/Src/mylibs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-mylibs

clean-Core-2f-Src-2f-mylibs:
	-$(RM) ./Core/Src/mylibs/codeur.cyclo ./Core/Src/mylibs/codeur.d ./Core/Src/mylibs/codeur.o ./Core/Src/mylibs/codeur.su ./Core/Src/mylibs/pid_controller.cyclo ./Core/Src/mylibs/pid_controller.d ./Core/Src/mylibs/pid_controller.o ./Core/Src/mylibs/pid_controller.su ./Core/Src/mylibs/pwm.cyclo ./Core/Src/mylibs/pwm.d ./Core/Src/mylibs/pwm.o ./Core/Src/mylibs/pwm.su ./Core/Src/mylibs/shell.cyclo ./Core/Src/mylibs/shell.d ./Core/Src/mylibs/shell.o ./Core/Src/mylibs/shell.su

.PHONY: clean-Core-2f-Src-2f-mylibs

