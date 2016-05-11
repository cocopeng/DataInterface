################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../util/CProperty.cpp \
../util/IPGet.cpp \
../util/MapSerializer.cpp \
../util/SQLList.cpp 

OBJS += \
./util/CProperty.o \
./util/IPGet.o \
./util/MapSerializer.o \
./util/SQLList.o 

CPP_DEPS += \
./util/CProperty.d \
./util/IPGet.d \
./util/MapSerializer.d \
./util/SQLList.d 


# Each subdirectory must supply rules for building sources it contributes
util/%.o: ../util/%.cpp
	@echo '正在构建文件： $<'
	@echo '正在调用： GNU C++ 编译器'
	g++ -I/usr/local/include -I/usr/local/include/boost -I/usr/local/include/thrift -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo '已结束构建： $<'
	@echo ' '


