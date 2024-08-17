# Generic shell helper functions
MKDIR = mkdir -p $1;
WGET = wget $1 --quiet --directory-prefix /tmp -O /tmp/$2;
CP = cp -r $1 $2;
DIR = $(dir $1)
UNTAR = \
if [ -f "$1" ]; then \
	$(call MKDIR,$3) \
	if [ -n "$2" ]; then \
		echo "Extracting $2..."; \
	else \
		echo "Extracting $1..."; \
	fi; \
	tar -xf $1 --directory $3 $2 --strip-components=1; \
fi;

# C/C++ helper functions
GET_CPP_FILES = $(shell find $1 -name '*.cpp')
GET_HEADER_FILES = $(shell find $1 -name '*.hpp' -or -name '*.h')
GET_OBJ_FILES = $(shell find $1 -name '*.o')
GET_OBJ_NAMES = $(shell find $1 -name '*.cpp' | sed "s/\.cpp/\.o/g")
GET_MAKEFILES = $(shell find $1 -name 'Makefile')

# String helper functions
TO_UPPER = $(shell echo $1 | tr a-z A-Z)

# TODO: Compile cross-toolchain:
# gcc-aarch64-linux-gnu binutils-aarch64-linux-gnu