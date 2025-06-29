CC = g++
CFLAGS = -I/usr/include/SDL3 -I src -I lib -I resources -std=c++17 -Wall -Wextra
LDFLAGS = -L/usr/lib -lSDL3 -lGL -Werror -O3

COMMON_CFLAGS  = -I/usr/include/SDL3 -I src -I lib -I resources -std=c++17 -Wall -Wextra
COMMON_LDFLAGS = -L/usr/lib -lSDL3 -lGL -Werror

MODE ?= Release

ifeq ($(MODE), Debug)
    CFLAGS  = $(COMMON_CFLAGS) -Og -g1
    LDFLAGS = $(COMMON_LDFLAGS)
else ifeq ($(MODE), Release)
    CFLAGS  = $(COMMON_CFLAGS) -O3 -march=x86-64 -mtune=generic -fno-omit-frame-pointer
    LDFLAGS = $(COMMON_LDFLAGS)
else
    $(error INVALID MODE: use Debug or Release)
endif

SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
OUT_DIR = $(BUILD_DIR)/out

SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
TARGET = $(OUT_DIR)/nv2cpp

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(OUT_DIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
