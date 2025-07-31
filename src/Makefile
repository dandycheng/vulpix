include $(VPX_ROOT_DIR)/tools/scripts/utils.mk
include $(VPX_ROOT_DIR)/tools/scripts/common.mk

ifeq ($(RELEASE),1)
BINARY_NAME := vulpix-f$(VULPIX_VER)
BUILD_TYPE := RELEASE
else
BINARY_NAME := vulpix-d$(VULPIX_VER)
BUILD_TYPE := DEVELOPMENT
PP_DEFINES := DEBUG_LOG_ENABLE
endif

PP_INCLUDES := \
	$(VPX_HEADERS) \
	$(DEPS_PATH)/yaml-cpp/source/include \
	$(DEPS_PATH)/yaml-cpp/source/src

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

$(BUILD_OUT_DIR)/$(BINARY_NAME): build-deps build-vulpix-objs
	mkdir -p $(BUILD_OUT_DIR);
	echo "\nLinking binary $@...";
	$(call CXX_LINKALL,$@,$(call GET_OBJ_FILES,$(OBJ_PATH)))

	if [ $$? -eq 0 ]; then \
		echo "$(BUILD_TYPE) build complete."; \
		echo "Output binary: $@"; \
	fi;

build-vulpix-objs: $(subst $(SRC_PATH),$(OBJ_PATH),$(call GET_OBJ_NAMES,$(SRC_PATH)/vulpix))

$(OBJ_PATH)/vulpix/%.o: $(SRC_PATH)/vulpix/%.cpp
	$(call CXX_COMPILE)