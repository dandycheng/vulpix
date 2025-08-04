SHELL := /bin/bash

############################################################
#                  Shell helper functions                  #
############################################################

MKDIR = mkdir -p $1;
RMRF  = if [ -d "$1" ] || [ -f "$1" ]; then rm -rf "$1"; fi;
WGET  = wget $1 --quiet --directory-prefix /tmp -O /tmp/$2;
CP    = cp -r $1 $2;


# Extracts an archive using tar.
# Usage:
#
# $1 - Path to the archive
# $2 - Directory within the archive to extract
# $2 - Target directory to extract $2 to
define UNTAR
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
endef


define GET_FILE_SIZE
	du $1 --block-size=$(if $2,$2,K) | awk '{print $$1}';
endef

##########################################################
#        C/C++ build pipeline specific functions         #
##########################################################

# TODO: Compile cross-toolchain:
# gcc-aarch64-linux-gnu binutils-aarch64-linux-gnu

GET_CPP_FILES    = $(shell find $1 -name '*.cpp')
GET_HEADER_FILES = $(shell find $1 -name '*.hpp' -or -name '*.h')
GET_OBJ_FILES    = $(shell find $1 -name '*.o')
GET_OBJ_NAMES    = $(shell find $1 -name '*.cpp' | sed "s/\.cpp/\.o/g")
GET_MAKEFILES    = $(shell find $1 -iname 'makefile')


# Creates static library. Non-relocated object files
# will be omitted.
# To create one, have a target of the form:
#
# libyamlcpp.a: $(MY_OBJ_FILES)
#     $(call MK_STATIC_LIB)
define MK_STATIC_LIB
	echo "Creating static library $@...";

	if [ ! -d "$(STATICLIBS_DIR)" ]; then \
		$(call MKDIR,$(STATICLIBS_DIR)) \
	fi;

	if [ -f "$(STATICLIBS_DIR)/$@" ]; then \
		echo "Static library $@ was already created."; \
	else \
		ar crs $(STATICLIBS_DIR)/$@ $(filter %.o,$^); \
		if [ $$? -eq 0 ]; then \
			echo "Static library created: $@."; \
		else \
			echo "Failed to create static library: $@!"; \
		fi; \
	fi;
endef


# Compile C++ source files to relocatable object files.
# To compile, have a target of the form:
#
# $(OBJ_PATH)/%.o: %.cpp
#     $(call CXX_COMPILE, ...)
#
# $1 - Preprocessor includes, g++ -I flag
# $2 - Preprocessor defines, g++ -D flag
# $3 - Optional - Defines the type of build
#
# You may optionally pass the build type, this only affects the output message:
#     $(call CXX_COMPILE,DEPENDENCY)
define CXX_COMPILE
	$(call MKDIR,$(@D))
	$(CXX) $(CXX_FLAGS) -c $< -o $@ \
			$(foreach dir,$1,-I$(dir)) \
			$(foreach d,$2,-D$(d));

	if [[ "$3" == "DEPENDENCY" ]]; then \
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
# $1 - The output binary
# $2 - Relocatable object files to link
# $3 - Library search path, g++ -L flag
# $4 - Libraries, g++ -l flag
define CXX_LINK
	$(call MKDIR,$(dir $1))
	$(CXX) $(CXX_FLAGS) -o $1 $2 \
		$(foreach dir,$3,-L$(dir) ) \
		$(foreach lib,$4,-l$(lib) );

	if [ $$? -eq 0 ]; then \
		if [ -n "$(PRINT_BIN_INFO)" ] && [ $(PRINT_BIN_INFO) -eq 1 ]; then \
			echo -e "Linking complete: $1\n"; \
			echo "Output binary: $1"; \
			echo -n "Binary size: "; \
			$(call GET_FILE_SIZE,$1) \
			echo -e "\nSections:"; \
			echo "━━━━━━━━━━━"; \
			size $1; \
		fi; \
	else \
		echo "Linking failed!"; \
		exit 1; \
	fi
endef

##########################################################
#                String helper functions                 #
##########################################################

TO_UPPER = $(shell echo $1 | tr a-z A-Z)