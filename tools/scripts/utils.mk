SHELL := /bin/bash

# Generic shell helper functions
MKDIR = mkdir -p $1;
RMDIR = if [ -d "$1" ]; then rm -rf "$1"; fi;
WGET  = wget $1 --quiet --directory-prefix /tmp -O /tmp/$2;
CP    = cp -r $1 $2;
UNTAR = \
if [ -f "$1" ]; then \
	if [ -n "$3" ]; then \
		mkdir -p $3; \
	fi; \
	if [ -n "$2" ]; then \
		echo "Extracting $2..."; \
	else \
		echo "Extracting $1..."; \
	fi; \
	tar -xf $1 --directory $3 $2 --strip-components=1; \
fi;

define ALL_PREQS_MATCH
	$(if $(filter-out %$(1),$^),
		$(error Some prerequisites don't match the extension $(1)! $(filter-out %$(1),$^)),
	)
endef


define MK_STATIC_LIB
	echo "Creating static library $@...";

	if [ ! -d "$(STATICLIBS_DIR)" ]; then \
		$(call MKDIR,$(STATICLIBS_DIR)) \
	fi;

	ar crs $(STATICLIBS_DIR)/$@ $^;
	$(call ALL_PREQS_MATCH,.o)

	if [ $$? -eq 0 ]; then \
		echo "Static library created: $(STATICLIBS_DIR)/$@"; \
	else \
		echo "Failed to create static library $(STATICLIBS_DIR)/$@!"; \
	fi;
endef


# Compile C++ source files to object files.
# To compile, have a target of the form:
#
# $(OBJ_PATH)/%.o: %.cpp
#     $(call CXX_COMPILE, ...)
#
# $(1) - Preprocessor includes, g++ -I flag
# $(2) - Preprocessor defines, g++ -D flag
# $(3) - Library search path, g++ -L flag
# $(4) - Libraries, g++ -l flag
# $(5) - Optional - Defines the type of build
# You may optionally pass the build type, this only affects the output message:
#	# $(call CXX_COMPILE,DEPENDENCY)
define CXX_COMPILE
    $(call MKDIR,$(@D))
	$(CXX) $(CXX_FLAGS) -c $< -o $@ \
			$(foreach dir,$(1),-I$(dir)) \
			$(foreach d,$(2),-D$(d)) \
			$(foreach ld,$(3),-L$(ld)) \
			$(foreach lib,$(4),-l$(lib));

	if [[ "$(5)" == "DEPENDENCY" ]]; then \
		echo "$(call TO_UPPER,$(subst .,,$(suffix $<))) [D]   $@"; \
	else \
		echo "$(call TO_UPPER,$(subst .,,$(suffix $<)))       $@"; \
	fi;
endef


# Links all C++ relocatable object files and library
# files into a single binary.
# To compile, have a target of the form:
#
# $(OBJ_PATH)/%.o: %.cpp
#     $(call LINK, ...)
#
# $(1) - The output binary
# $(2) - Relocatable object files to link
# $(3) - Library search path, g++ -L flag
# $(4) - Libraries, g++ -l flag
define CXX_LINK
	$(call MKDIR,$(dir $1))
	$(CXX) $(CXX_FLAGS) -o $(1) $(2) \
		$(foreach dir,$(3),-L$(dir) ) \
		$(foreach lib,$(4),-l$(lib) );

	if [ $$? -eq 0 ]; then \
		echo -e "Linking complete: $(1)\n"; \
		echo "Output binary: $(1)"; \
		echo -n "Binary size: "; \
		$(call GET_FILE_SIZE,$(1)) \
		echo -e "\nSections:"; \
		echo "━━━━━━━━━━━"; \
		size $(1); \
	else \
		echo "Linking failed!"; \
		exit 1; \
	fi
endef


GET_CPP_FILES    = $(shell find $1 -name '*.cpp')
GET_HEADER_FILES = $(shell find $1 -name '*.hpp' -or -name '*.h')
GET_OBJ_FILES    = $(shell find $1 -name '*.o')
GET_OBJ_NAMES    = $(shell find $1 -name '*.cpp' | sed "s/\.cpp/\.o/g")
GET_MAKEFILES    = $(shell find $1 -name 'Makefile' -or -name 'makefile')

CXX_LINKALL = $(CXX) $(CXX_FLAGS) -o $1 $2 $3

define GET_FILE_SIZE
	du $(1) --block-size=$(if $(2),$(2),K) | awk '{print $$1}';
endef

# String helper functions
TO_UPPER = $(shell echo $1 | tr a-z A-Z)

# TODO: Compile cross-toolchain:
# gcc-aarch64-linux-gnu binutils-aarch64-linux-gnu
