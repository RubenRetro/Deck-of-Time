# ==============================================================================
# PROJECT SETTINGS
# ==============================================================================
SRC_DIR = src
OUT_DIR = out
ENV ?= mingw
BUILD_MODE ?= debug

# ==============================================================================
# TOOLCHAIN CONFIGURATION (ADJUST PATHS HERE!)
# ==============================================================================

ifeq ($(ENV), djgpp)
    # DJGPP Environment (DOS)
    CC = C:/dev-allegro/djgpp/bin/i586-pc-msdosdjgpp-gcc.exe -DDOS -DALLEGRO_HAVE_STDINT_H
    TARGET_NAME = dos
    TARGET_EXT = .exe
    CLEAN_RM = del 2> /dev/null
    
    # Custom Paths for DJGPP
    IFLAGS  = -IC:/dev-allegro/allegro4-dos/include -I./include
    LDPATHS = -LC:/dev-allegro/allegro4-dos/lib
    
    # Combined Flags 
    LDFLAGS = $(LDPATHS) -ljgmod -lalleg -lemu
else
    # MinGW Environment (Windows) - This is the default
    CC = C:/dev-allegro/mingw32/bin/gcc.exe
    TARGET_NAME = win
    TARGET_EXT = .exe
    CLEAN_RM = del 2> /dev/null

    # Custom Paths for MinGW
    IFLAGS  = -IC:/dev-allegro/allegro4-win/include -I./include
    LDPATHS = -LC:/dev-allegro/allegro4-win/lib

    # Combined Flags
    LDFLAGS = $(LDPATHS) -ljgmod -lalleg -lgdi32 -luser32 -lwinmm -lkernel32 -ldsound
endif

# ==============================================================================
# BUILD MODE AND FLAGS (STD ADDED HERE)
# ==============================================================================
# Base flags for std, Warnings, and Debug/Optimization
BASE_FLAGS = -Wall -std=gnu99 -fgnu89-inline

ifeq ($(BUILD_MODE), debug)
    # Add IFLAGS (custom includes) and Debug flags
    CFLAGS = -g -O0 $(BASE_FLAGS) $(IFLAGS) 
    TARGET = $(TARGET_NAME)_dbg$(TARGET_EXT)
else
    # Add IFLAGS (custom includes) and Release flags
    CFLAGS = -O3 -DNDEBUG $(BASE_FLAGS) $(IFLAGS)
    TARGET = $(TARGET_NAME)_rel$(TARGET_EXT)
endif

# ==============================================================================
# FILE DISCOVERY AND TRANSFORMATION (Windows 'cmd.exe' Only)
# ==============================================================================
# Define the absolute path to the project root, converted to forward slashes.
ABS_ROOT_FORWARD_SLASH := $(subst \,/,$(realpath $(CURDIR)))

# 1. Execute 'dir' command ONCE to get the list of files with full, Windows-style paths.
WIN_SOURCES := $(shell dir $(SRC_DIR)\*.c /s /b)

# 2. Normalize and Strip:
#    a) Convert backslashes to forward slashes.
NORM_SOURCES := $(subst \,/,$(WIN_SOURCES))

#    b) Remove the absolute root path, leaving only the relative path (e.g., src/main.c).
SOURCES := $(subst $(ABS_ROOT_FORWARD_SLASH)/,,$(NORM_SOURCES))

# 3. Transform source paths to object paths
TEMP_OBJECTS := $(patsubst $(SRC_DIR)/%.c,%.o,$(SOURCES))
OBJECTS := $(addprefix $(OUT_DIR)/, $(TEMP_OBJECTS))

# Define dependency files (*.d)
DEPS := $(OBJECTS:.o=.d)

# Use VPATH to tell make where to look for source files
VPATH = $(SRC_DIR)
#$(info SOURCES is: $(SOURCES))
#$(info OBJECTS is: $(OBJECTS))

# ==============================================================================
# RULES
# ==============================================================================

.PHONY: all
all: $(OUT_DIR) $(TARGET)
	@echo "Build complete: $(ENV) $(BUILD_MODE) mode."

$(OUT_DIR):
	@mkdir $(OUT_DIR)

# DEPS used here: Include auto-generated dependency files
-include $(DEPS)

# 1. Linking Rule
$(TARGET): $(OBJECTS)
	@echo "Linking C objects for $(ENV) $(BUILD_MODE) build..."
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@

# 2. Compilation Pattern Rule
$(OUT_DIR)/%.o: %.c
	@echo "Compiling $< to $@"
	@mkdir $(subst /,\,$(dir $@)) 2>NUL || @echo ""
	$(CC) $(CFLAGS) -MMD -c $< -o $@

# 3. Clean Rule
.PHONY: clean
clean:
	@echo "Cleaning up..."
	@rmdir /s /q $(OUT_DIR) 2> /dev/null
	@$(CLEAN_RM) $(TARGET_NAME)_dbg$(TARGET_EXT) $(TARGET_NAME)_rel$(TARGET_EXT)

# 4. Convenience Targets
.PHONY: debug release
debug:
	@$(MAKE) V=1 BUILD_MODE=debug all

release:
	@$(MAKE) V=1 BUILD_MODE=release all
