# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -DNOMINMAX -D_WIN32_WINNT=0x0601

# Build configuration
BUILD_TYPE ?= Debug

# Vcpkg root
VCPKG_ROOT ?= C:/Users/Arnav/vcpkg

# Detect OS for cross-platform commands
ifeq ($(OS),Windows_NT)
	RM_CMD = rd /s /q build
	EXEC = ./build/$(BUILD_TYPE)/BasicServerWithCrow.exe
else
	RM_CMD = rm -rf build
	EXEC = ./build/$(BUILD_TYPE)/BasicServerWithCrow
endif

# Phony targets
.PHONY: all build run clean

# Default target
all: clean build run

# Build target
build:
	@if not exist build mkdir build
	@cd build && cmake -DCMAKE_TOOLCHAIN_FILE=$(VCPKG_ROOT)/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) .. && cmake --build . --config $(BUILD_TYPE)

# Run target
run: build
	@$(EXEC)

# Clean target
clean:
	@if exist build rd /s /q build
