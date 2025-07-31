include $(VPX_ROOT_DIR)/tools/scripts/utils.mk
include $(VPX_ROOT_DIR)/tools/scripts/common.mk

ifeq ($(RELEASE),1)
BINARY_NAME := vulpix-f$(VULPIX_VER)
BUILD_TYPE := RELEASE
else
BINARY_NAME := vulpix-d$(VULPIX_VER)
BUILD_TYPE := DEVELOPMENT
VPX_PP_DEFINES := DEBUG_LOG_ENABLE
endif

VPX_PP_INCLUDES := \
	$(VPX_HEADERS) \
	$(DEPS_PATH)/yaml-cpp/source/include \
	$(DEPS_PATH)/yaml-cpp/source/src

LDFLAGS := $(STATICLIBS_DIR)
VPX_CXX_OBJS := $(subst $(SRC_PATH),$(OBJ_PATH),$(call GET_OBJ_NAMES,$(SRC_PATH)/vulpix))

# PWD   := $(shell pwd)
# KDIR  := /lib/modules/$(shell uname -r)/build/
# obj-m += helloworld_lkm.o

# all:
#         make -C $(KDIR) M=$(PWD) modules
# install:
#         make -C $(KDIR) M=$(PWD) modules_install
# clean:
#         make -C $(KDIR) M=$(PWD) clean

# TODO: Clean up to follow Linux Kernel module build format
# TODO: Find a way to enable individual binary builds for some utils.
.SILENT:
build: $(BUILD_OUT_DIR)/$(BINARY_NAME)

help:
	@echo
	@echo "TARGETS:"
	@echo "build             - Builds the dependencies, then the vulpix binary."
	@echo "build-vulpix-objs - Builds Vulpix object files only."
	@echo "build-deps        - Builds dependencies only."
	@echo "clean-deps        - Cleans dependencies."
	@echo "download-deps     - Downloads all dependencies if they have specified"
	@echo "                    a target to download its source."
	@echo

build-vulpix-objs: $(VPX_CXX_OBJS)

$(BUILD_OUT_DIR)/$(BINARY_NAME): build-deps build-vulpix-objs
	$(call CXX_LINK,$@,$(VPX_CXX_OBJS),$(LDFLAGS),$(LIBS))

$(OBJ_PATH)/vulpix/%.o: $(SRC_PATH)/vulpix/%.cpp
	$(call CXX_COMPILE,$(VPX_PP_INCLUDES),$(VPX_PP_DEFINES))