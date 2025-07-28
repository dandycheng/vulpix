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
MK_STATIC_LIB = \
	"Creating static library $1..."; \
	if [ ! -d "$(STATIC_LIBS_DIR)" ]; then \
		$(call MKDIR,$(STATIC_LIBS_DIR)) \
	fi; \
	ar crs $1 $(shell find $2 -name '*.o');

# C/C++ helper functions
GET_CPP_FILES    = $(shell find $1 -name '*.cpp')
GET_HEADER_FILES = $(shell find $1 -name '*.hpp' -or -name '*.h')
GET_OBJ_FILES    = $(shell find $1 -name '*.o')
GET_OBJ_NAMES    = $(shell find $1 -name '*.cpp' | sed "s/\.cpp/\.o/g")
GET_MAKEFILES    = $(shell find $1 -name 'Makefile' -or -name 'makefile')

CXX_LINKALL = $(CXX) $(CXX_FLAGS) -o $1 $2 $3
CXX_COMPILE = $(shell set -e; $(CXX) $(CXX_FLAGS) -c $1 -o $2 $3 $(foreach d,$(PP_DEFINES),-D$(d)))

# String helper functions
TO_UPPER = $(shell echo $1 | tr a-z A-Z)

# TODO: Compile cross-toolchain:
# gcc-aarch64-linux-gnu binutils-aarch64-linux-gnu
