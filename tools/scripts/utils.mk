SHELL := /bin/bash
UTILS_MAKEFILE_INCLUDE_DIRECTIVE := 1

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
	echo $(filter-out %$(1),$^);
	if [ -n "$(strip $(filter-out %$(1),$^))" ]; then \
		$(error "Some prerequisites don't match the extension $(1)!\
			$(filter-out %$(1),$^) \
		"); \
	fi;
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

# C/C++ helper functions
GET_CPP_FILES    = $(shell find $1 -name '*.cpp')
GET_HEADER_FILES = $(shell find $1 -name '*.hpp' -or -name '*.h')
GET_OBJ_FILES    = $(shell find $1 -name '*.o')
GET_OBJ_NAMES    = $(shell find $1 -name '*.cpp' | sed "s/\.cpp/\.o/g")
GET_MAKEFILES    = $(shell find $1 -name 'Makefile' -or -name 'makefile')

CXX_LINKALL = $(CXX) $(CXX_FLAGS) -o $1 $2 $3

define CXX_LINK
	$(CXX) $(CXX_FLAGS) -o $(CXX_LINK_OBJS) \
		$(foreach dir,$(CXX_LIB_SEARCH_PATH),-L$(dir) ) \
		$(foreach lib,$(CXX_LIBS),-l$(lib) );

	if [ $$? -eq 0 ]; then \
		echo "Linking complete: $1"; \
		echo "Output binary: $1"; \
		echo "----------------"; \
		size $1; \
		echo "----------------"; \
	else \
		echo "Linking failed!"; \
		exit 1; \
	fi
endef

# Compile C++ source files to object files.
# To compile, have a target of the form:
#
# $(OBJ_PATH)/%.o: %.cpp
#     $(call CXX_COMPILE)
#
# You may optionally pass the build type, this only affects the output message:
#	# $(call CXX_COMPILE,DEPENDENCY)
#
define CXX_COMPILE
    $(call MKDIR,$(@D))
	$(CXX) $(CXX_FLAGS) -c $< -o $@ \
			$(foreach dir,$(PP_INCLUDES),-I $(dir)) \
			$(foreach d,$(PP_DEFINES),-D$(d));
	if [[ "$(1)" == "DEPENDENCY" ]]; then \
		echo "$(call TO_UPPER,$(subst .,,$(suffix $<))) [D]   $@"; \
	else \
		echo "$(call TO_UPPER,$(subst .,,$(suffix $<)))       $@"; \
	fi;
endef


# String helper functions
TO_UPPER = $(shell echo $1 | tr a-z A-Z)

# TODO: Compile cross-toolchain:
# gcc-aarch64-linux-gnu binutils-aarch64-linux-gnu
