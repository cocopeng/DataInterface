################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../access/DataAccessInterface.cpp 

OBJS += \
./access/DataAccessInterface.o 

CPP_DEPS += \
./access/DataAccessInterface.d 


# Each subdirectory must supply rules for building sources it contributes
access/%.o: ../access/%.cpp
	@echo '正在构建文件： $<'
	@echo '正在调用： GNU C++ 编译器'
	g++ -I/usr/local/include -I/usr/local/include/boost -I/usr/local/include/thrift -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo '已结束构建： $<'
	@echo ' '


