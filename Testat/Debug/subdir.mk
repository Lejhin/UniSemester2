################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Studi.cpp \
../gtest_main.cpp \
../simplemath.cpp \
../test_simplemath.cpp \
../test_studi.cpp 

OBJS += \
./Studi.o \
./gtest_main.o \
./simplemath.o \
./test_simplemath.o \
./test_studi.o 

CPP_DEPS += \
./Studi.d \
./gtest_main.d \
./simplemath.d \
./test_simplemath.d \
./test_studi.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


