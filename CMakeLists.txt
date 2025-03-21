cmake_minimum_required(VERSION 3.10)
project(Blink C ASM)

# Toolchain
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# Flags
set(MCU "cortex-m7")
set(FPU "-mfpu=fpv5-sp-d16 -mfloat-abi=hard")
set(ARCH "-mthumb -mcpu=${MCU} ${FPU}")

set(CMAKE_C_FLAGS "${ARCH} -Os -g -std=gnu11 -Wall -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSTM32F7 -DSTM32F746xx")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp")

# Libopencm3
set(LIBOPENCM3_PATH ./libopencm3)
include_directories(${LIBOPENCM3_PATH}/include)
link_directories(${LIBOPENCM3_PATH}/lib)

# Linker
set(LD_SCRIPT ../proj.ld)
set(CMAKE_EXE_LINKER_FLAGS "${ARCH} -Wl,--gc-sections -T${LD_SCRIPT}")

# Sources
add_executable(${PROJECT_NAME}.elf main.c)

# Link
target_link_libraries(${PROJECT_NAME}.elf opencm3_stm32f7)

# Post-build
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
  COMMAND arm-none-eabi-objcopy -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.bin
)