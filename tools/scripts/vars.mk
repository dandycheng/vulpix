VARS_MAKEFILE_INCLUDE_DIRECTIVE := 1

################################################################
# This file stores all common variables that'll be used by the #
# build.                                                       #
################################################################

SRC_PATH       = $(VPX_ROOT_DIR)/src
DEPS_PATH      = $(SRC_PATH)/dependencies
OBJ_PATH       = $(SRC_PATH)/build/obj
SHAREDLIBS_DIR = $(SRC_PATH)/build/sharedlibs
STATICLIBS_DIR = $(SRC_PATH)/build/staticlibs
BUILD_OUT_DIR  = $(VPX_ROOT_DIR)/artifacts

# Build related variables
MAKEFLAGS += --no-print-directory
PKG_MANAGER = $(shell which apt || which zypper || which yum)

export SRC_PATH
export DEPS_PATH
export OBJ_PATH
export BUILD_OUT_DIR
