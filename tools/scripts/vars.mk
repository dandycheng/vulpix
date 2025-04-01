################################################################
# This file stores all common variables that'll be used by the #
# build.                                                       #
################################################################

SRC_PATH       := $(VPX_ROOT_DIR)/src
DEPS_PATH      := $(SRC_PATH)/dependencies
OBJ_PATH       := $(SRC_PATH)/build/obj
BUILD_OUT_DIR  := $(SRC_PATH)/build/artifacts

# Build related variables
MAKEFLAGS += --no-print-directory
PKG_MANAGER = $(shell which apt || which zypper || which yum)