LIBRARY := wilcot

# Path to directories
SOURCE_DIRECTORY := source
INCLUDE_DIRECTORY := include
LIBRARY_DIRECTORY := library
TESTS_DIRECTORY := tests

# Compiler settings
COMPILER := g++
COMPILE_FLAGS := -I$(INCLUDE_DIRECTORY) --std=c++03 -Wall -pedantic

# Recursive find by pattern
find = $(foreach file, $(wildcard $1/*), $(filter $2, $(file)) $(call find, $(file), $2))

# Source and object files
SOURCE_FILES := $(call find, $(SOURCE_DIRECTORY), %.cpp)
OBJECT_FILES := $(patsubst %.cpp, %.o, $(SOURCE_FILES))

LIBRARY_FILE := $(LIBRARY_DIRECTORY)/lib$(LIBRARY).a

SOURCE_TESTS := $(call find, $(TESTS_DIRECTORY), %.cpp)
BINARY_TESTS := $(patsubst %.cpp, %, $(SOURCE_TESTS))

# All targets

all: build tests

build: $(LIBRARY_FILE)

tests: $(BINARY_TESTS)

clean:
	@echo Remove all object and library files
	@rm -f $(OBJECT_FILES) $(LIBRARY_FILE)

$(LIBRARY_FILE): $(OBJECT_FILES)
	@echo Create library "$@"
	@mkdir -p $(LIBRARY_DIRECTORY)
	@ar rcs $@ $^

$(SOURCE_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cpp
	@echo Compile file "$<"
	@$(COMPILER) $(COMPILE_FLAGS) -c $< -o $@

$(TESTS_DIRECTORY)/%: $(TESTS_DIRECTORY)/%.cpp
	@echo Compile test "$<"
	@$(COMPILER) $(COMPILE_FLAGS) -L$(LIBRARY_DIRECTORY) -o $@ $< -l$(LIBRARY)
	@echo Run test "$<"
	@./$@ >/dev/null 2>&1
	@echo Test completed!
	@rm -f $@
