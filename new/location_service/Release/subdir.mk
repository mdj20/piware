################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../key_value.c \
../kv_test.c \
../loc_agregate.c \
../loc_service.c \
../location_test.c \
../ls_threads.c \
../mt_buffer.c \
../udp_adapter.c \
../udp_socketbuilder.c 

OBJS += \
./key_value.o \
./kv_test.o \
./loc_agregate.o \
./loc_service.o \
./location_test.o \
./ls_threads.o \
./mt_buffer.o \
./udp_adapter.o \
./udp_socketbuilder.o 

C_DEPS += \
./key_value.d \
./kv_test.d \
./loc_agregate.d \
./loc_service.d \
./location_test.d \
./ls_threads.d \
./mt_buffer.d \
./udp_adapter.d \
./udp_socketbuilder.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


