# === Basic config ===
CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused-parameter -O2 -Iinclude
SRC_DIR = src
BUILD_DIR = build
RELEASE_DIR = release
INCLUDE_DIR = include
LIB_NAME = reestruct

# === Directory structure ===
RELEASE_INCLUDE = $(RELEASE_DIR)/include
RELEASE_LIB = $(RELEASE_DIR)/lib

# === Source files ===
SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
HEADERS := $(wildcard $(INCLUDE_DIR)/*.h)

# === Targets ===
.PHONY: all static shared clean release

all: static shared release

# === Build static library (.a) ===
static: $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	ar rcs $(BUILD_DIR)/lib$(LIB_NAME).a $(OBJECTS)
	@echo "✅ Static library built: lib$(LIB_NAME).a"

# === Build shared library (.dll / .so) ===
shared: $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
ifeq ($(OS),Windows_NT)
	$(CC) -shared -o $(BUILD_DIR)/$(LIB_NAME).dll $(OBJECTS)
	@echo "✅ Shared library built: $(LIB_NAME).dll"
else
	$(CC) -shared -fPIC -o $(BUILD_DIR)/lib$(LIB_NAME).so $(OBJECTS)
	@echo "✅ Shared library built: lib$(LIB_NAME).so"
endif

# === Compile .o from .c ===
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# === Create release package ===
release: static shared
	@mkdir -p $(RELEASE_INCLUDE)
	@mkdir -p $(RELEASE_LIB)
	@cp $(INCLUDE_DIR)/*.h $(RELEASE_INCLUDE)/
ifeq ($(OS),Windows_NT)
	@cp $(BUILD_DIR)/$(LIB_NAME).dll $(RELEASE_LIB)/
	@cp $(BUILD_DIR)/lib$(LIB_NAME).a $(RELEASE_LIB)/
else
	@cp $(BUILD_DIR)/lib$(LIB_NAME).so $(RELEASE_LIB)/
	@cp $(BUILD_DIR)/lib$(LIB_NAME).a $(RELEASE_LIB)/
endif
	@cp LICENSE README.md CHANGELOG.md $(RELEASE_DIR)/
	@echo "📦 Release package created in $(RELEASE_DIR)"

# === Clean ===
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(RELEASE_DIR)
	@echo "🧹 Cleaned build and release files"