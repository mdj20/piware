################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hm_agregate.c \
../key_value.c \
../kv_test.c \
../loc_agregate.c 

OBJS += \
./hm_agregate.o \
./key_value.o \
./kv_test.o \
./loc_agregate.o 

C_DEPS += \
./hm_agregate.d \
./key_value.d \
./kv_test.d \
./loc_agregate.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


