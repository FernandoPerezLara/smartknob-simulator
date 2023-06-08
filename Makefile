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
RESOURCE_XML = $(SRC_PATH)/gresource.xml
RESOURCE_SRC = $(BUILD_PATH)/MainWindow/resources.c
RESOURCE_OBJ = $(BUILD_PATH)/MainWindow/resources.o

# Extensions
SRC_EXT = cpp

# List of source files, compilation objects and dependecies
SOURCES = $(shell find $(SRC_PATH) -name "*.$(SRC_EXT)" | sort -k 1nr | cut -f2-)
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o) $(RESOURCE_OBJ)
DEPS = $(OBJECTS:.o=.d)

# Compiler configuration
PKGCONFIG = $(shell which pkg-config)
COMPILE_FLAGS = -std=c++17 -Wall -Wextra -g
INCLUDES = -I include/ -I /usr/local/include $(shell $(PKGCONFIG) --cflags gtkmm-4.0)
LIBS = $(shell $(PKGCONFIG) --libs gtkmm-4.0)

# Create directories
directories:
	@printf "$(INFO) Creating directories\n"
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)

# Clean build files and directories
clean:
	@printf "$(INFO) Deleting $(BIN_NAME) symlink\n"
	@$(RM) $(BIN_NAME)
	@printf "$(INFO) Deleting directories\n"
	@$(RM) -r $(BUILD_PATH)
	@$(RM) -r $(BIN_PATH)

# Create directories on build
build: directories compile_resources
	@$(MAKE) symlink

compile_resources:
	@printf "$(INFO) Compiling resources\n"
	@glib-compile-resources $(RESOURCE_XML) --target=$(RESOURCE_SRC) --sourcedir=$(SRC_PATH) --generate-source

# Create symlink on build
symlink: $(BIN_PATH)/$(BIN_NAME)
	@printf "$(INFO) Making symlink: $(BIN_NAME) -> $<\n"
	@$(RM) $(BIN_NAME)
	@ln -s $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)

# Run project
run: $(BIN_PATH)/$(BIN_NAME)
	@printf "$(INFO) Running project\n"
	@$(BIN_PATH)/$(BIN_NAME)

# Compile
$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@printf "$(INFO) Linking: $@\n"
	$(CXX) $(OBJECTS) -o $@ ${LIBS}

# Add dependency files
-include $(DEPS)

# Compile
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@printf "$(INFO) Compiling: $< -> $@\n"
	$(CXX) $(COMPILE_FLAGS) $(INCLUDES) -MP -MMD -c $< -o $@

# Compile resources
$(RESOURCE_OBJ): $(RESOURCE_SRC)
	@printf "$(INFO) Compiling: $< -> $@\n"
	$(CXX) $(COMPILE_FLAGS) $(INCLUDES) -c $< -o $@
