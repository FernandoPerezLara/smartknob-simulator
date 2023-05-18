# Output colors
GREEN = \033[0;32m
BLUE = \033[0;34m
RESET = \033[0m
INFO = $(BLUE)[$(GREEN)INFO$(BLUE)]$(RESET)

# Compiler
CXX = g++

# Path
SRC_PATH = src
BUILD_PATH = build
BIN_PATH = $(BUILD_PATH)/bin
BIN_NAME = runner

# Extensions
SRC_EXT = cpp

# List of source files, compilation objects and dependecies
SOURCES = $(shell find $(SRC_PATH) -name "*.$(SRC_EXT)" | sort -k 1nr | cut -f2-)
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
DEPS = $(OBJECTS:.o=.d)

# Compiler configuration
PKGCONFIG = $(shell which pkg-config)
COMPILE_FLAGS = -std=c++11 -Wall -Wextra -g
INCLUDES = -I include/ -I /usr/local/include $(shell $(PKGCONFIG) --cflags gtk4)
LIBS = $(shell $(PKGCONFIG) --libs gtk4)

# Create directories
directories:
	@echo -e "$(INFO) Creating directories"
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)

# Clean build files and directories
clean:
	@echo -e "$(INFO) Deleting $(BIN_NAME) symlink"
	@$(RM) $(BIN_NAME)
	@echo -e "$(INFO) Deleting directories"
	@$(RM) -r $(BUILD_PATH)
	@$(RM) -r $(BIN_PATH)

# Create directories on build
build: directories
	@$(MAKE) symlink

# Create symlink on build
symlink: $(BIN_PATH)/$(BIN_NAME)
	@echo -e "$(INFO) Making symlink: $(BIN_NAME) -> $<"
	@$(RM) $(BIN_NAME)
	@ln -s $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)

# Run project
run: $(BIN_PATH)/$(BIN_NAME)
	@echo -e "$(INFO) Running project"
	@$(BIN_PATH)/$(BIN_NAME)

# Compile
$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo -e "$(INFO) Linking: $@"
	$(CXX) $(OBJECTS) -o $@ ${LIBS}

# Add dependency files
-include $(DEPS)

# Compile
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo -e "$(INFO) Compiling: $< -> $@"
	$(CXX) $(COMPILE_FLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
