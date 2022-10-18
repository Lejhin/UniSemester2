################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../gtest_main.cpp \
../main.cpp \
../test_tausche.cpp 

CPP_DEPS += \
./gtest_main.d \
./main.d \
./test_tausche.d 

OBJS += \
./gtest_main.o \
./main.o \
./test_tausche.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./gtest_main.d ./gtest_main.o ./main.d ./main.o ./test_tausche.d ./test_tausche.o

.PHONY: clean--2e-

