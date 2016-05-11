################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../gen-cpp/DataInterfaceForward.cpp \
../gen-cpp/DataInterfaceForward_constants.cpp \
../gen-cpp/DataInterfaceForward_server.skeleton.cpp \
../gen-cpp/DataInterfaceForward_types.cpp \
../gen-cpp/PushMessage.cpp \
../gen-cpp/PushMessage_constants.cpp \
../gen-cpp/PushMessage_server.skeleton.cpp \
../gen-cpp/PushMessage_types.cpp 

OBJS += \
./gen-cpp/DataInterfaceForward.o \
./gen-cpp/DataInterfaceForward_constants.o \
./gen-cpp/DataInterfaceForward_server.skeleton.o \
./gen-cpp/DataInterfaceForward_types.o \
./gen-cpp/PushMessage.o \
./gen-cpp/PushMessage_constants.o \
./gen-cpp/PushMessage_server.skeleton.o \
./gen-cpp/PushMessage_types.o 

CPP_DEPS += \
./gen-cpp/DataInterfaceForward.d \
./gen-cpp/DataInterfaceForward_constants.d \
./gen-cpp/DataInterfaceForward_server.skeleton.d \
./gen-cpp/DataInterfaceForward_types.d \
./gen-cpp/PushMessage.d \
./gen-cpp/PushMessage_constants.d \
./gen-cpp/PushMessage_server.skeleton.d \
./gen-cpp/PushMessage_types.d 


# Each subdirectory must supply rules for building sources it contributes
gen-cpp/%.o: ../gen-cpp/%.cpp
	@echo '正在构建文件： $<'
	@echo '正在调用： GNU C++ 编译器'
	g++ -I/usr/local/include -I/usr/local/include/boost -I/usr/local/include/thrift -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo '已结束构建： $<'
	@echo ' '


