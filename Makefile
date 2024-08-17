#################################
#   Vulpix specific variables   #
#################################

SRC_PATH := src
DEPS_PATH := $(SRC_PATH)/dependencies
INCLUDE_PATH := include
TEST_PATH := tests
UNIT_TEST_PATH := $(TEST_PATH)/unit-tests
OBJ_PATH := $(SRC_PATH)/build/obj
BUILD_OUT_PATH := $(SRC_PATH)/build/out

CXX := g++
MAKEFLAGS += --no-print-directory
CXX_FLAGS := \
	-std=c++14
CXX_LIBS =

include ./utils.mk
include $(DEPS_PATH)/Makefile
include $(SRC_PATH)/Makefile

VPX_CLEAN_SOURCES := \
	$(SRC_PATH)/build \
	$(OBJ_PATH)/vulpix

BUILD_DEPENDENCIES := \
	cmake \
	g++ \

TEST_DEPENDENCIES := \
	libgtest-dev \
	libgmock-dev \

PKG_MANAGER = $(shell which apt || which zypper || which yum)

setup-env:
	@echo "\nSetting up build environment..."
	$(call MKDIR,$(SRC_PATH))
	$(call MKDIR,$(INCLUDE_PATH))
	$(call MKDIR,$(DEPS_PATH))
	$(call MKDIR,$(OBJ_PATH))
	$(call MKDIR,$(BUILD_OUT_PATH))

install-build-deps:
	sudo $(PKG_MANAGER) update
	sudo $(PKG_MANAGER) install -y $(BUILD_DEPENDENCIES)

install-test-deps:
	sudo $(PKG_MANAGER) update
	sudo $(PKG_MANAGER) install -y $(TEST_DEPENDENCIES)

remove-build-deps:
	sudo $(PKG_MANAGER) remove -y $(BUILD_DEPENDENCIES)

.PHONY:
clean: clean-deps
	rm -rf $(VPX_CLEAN_SOURCES)

# TODO: Update this to remove dependency folders in src
cleanall: clean
	rm -rf $(CLEAN_SRCS)