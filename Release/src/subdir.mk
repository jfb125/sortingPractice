################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BinaryHeap.cpp \
../src/QuickSortWith3Waypartitioning.cpp \
../src/insertionSort.cpp \
../src/insertionSort_test.cpp \
../src/mergeSort.cpp \
../src/quickSort.cpp \
../src/selectionSort.cpp \
../src/selectionSort_test.cpp \
../src/sorting.cpp \
../src/sortingAlgorithms.cpp \
../src/sorting_test.cpp 

OBJS += \
./src/BinaryHeap.o \
./src/QuickSortWith3Waypartitioning.o \
./src/insertionSort.o \
./src/insertionSort_test.o \
./src/mergeSort.o \
./src/quickSort.o \
./src/selectionSort.o \
./src/selectionSort_test.o \
./src/sorting.o \
./src/sortingAlgorithms.o \
./src/sorting_test.o 

CPP_DEPS += \
./src/BinaryHeap.d \
./src/QuickSortWith3Waypartitioning.d \
./src/insertionSort.d \
./src/insertionSort_test.d \
./src/mergeSort.d \
./src/quickSort.d \
./src/selectionSort.d \
./src/selectionSort_test.d \
./src/sorting.d \
./src/sortingAlgorithms.d \
./src/sorting_test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


