LIBRARY := wilcot

# Path to directories
SOURCE_DIRECTORY := source
INCLUDE_DIRECTORY := include
LIBRARY_DIRECTORY := library
TESTS_DIRECTORY := tests
BUILD_DIRECTORY := .build

# Compiler settings
COMPILER := g++
COMPILE_FLAGS := \
	-I$(INCLUDE_DIRECTORY) --std=c++03 -pedantic -pedantic-errors -Wall \
	-Wextra -Werror -Wconversion -Weffc++ -Wduplicated-cond -Wduplicated-branches \
	-Wlogical-op -Wnull-dereference -Wold-style-cast -Wuseless-cast -Wshadow

# Recursive find by pattern
find = $(foreach file, $(wildcard $1/*), $(filter $2, $(file)) $(call find, $(file), $2))

# Source and object files
SOURCE_FILES := $(call find, $(SOURCE_DIRECTORY), %.cpp)
OBJECT_FILES := $(patsubst $(SOURCE_DIRECTORY)/%.cpp, $(BUILD_DIRECTORY)/%.o, $(SOURCE_FILES))

LIBRARY_FILE := $(LIBRARY_DIRECTORY)/lib$(LIBRARY).a

SOURCE_TESTS := $(call find, $(TESTS_DIRECTORY), %.cpp)
BINARY_TESTS := $(patsubst $(TESTS_DIRECTORY)/%.cpp, $(BUILD_DIRECTORY)/%, $(SOURCE_TESTS))

# All targets

all: build tests

build: $(LIBRARY_FILE)

tests: $(BINARY_TESTS)

clean:
	@echo "[RM] '$(BUILD_DIRECTORY)', '$(LIBRARY_FILE)'"
	@rm -rf "$(BUILD_DIRECTORY)" "$(LIBRARY_FILE)"

$(LIBRARY_FILE): $(OBJECT_FILES)
	@echo "[AR] '$@'"
	@mkdir -p "$(LIBRARY_DIRECTORY)"
	@ar rcs "$@" $^

$(BUILD_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cpp
	@echo "[CC] '$<'"
	@mkdir -p "$(dir $@)"
	@$(COMPILER) $(COMPILE_FLAGS) -o "$@" -c "$<"

$(BUILD_DIRECTORY)/%: $(TESTS_DIRECTORY)/%.cpp
	@mkdir -p "$(dir $@)"
	@$(COMPILER) $(COMPILE_FLAGS) -L$(LIBRARY_DIRECTORY) -o "$@" "$<" -l$(LIBRARY)
	@echo "[TS] '$<'"
	@./$@
	@rm -f "$@"
