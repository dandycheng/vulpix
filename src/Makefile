include $(VPX_ROOT_DIR)/tools/scripts/utils.mk
include $(VPX_ROOT_DIR)/tools/scripts/common.mk

BINARY_NAME := $(call GET_BUILD_NAME)

BUILD_INCLUDES += \
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

build-vulpix-objs: $(subst $(SRC_PATH),$(OBJ_PATH),$(call GET_OBJ_NAMES,$(SRC_PATH)/vulpix))

$(BUILD_OUT_DIR)/$(BINARY_NAME): build-deps build-vulpix-objs
	mkdir -p $(BUILD_OUT_DIR);
	echo "\nLinking binary $@...";	
	$(call CXX_LINKALL,$@,$(call GET_OBJ_FILES,$(OBJ_PATH)))

	if [ $$? -eq 0 ]; then \
		echo "Build complete."; \
		echo "Output binary: $@"; \
	fi;

$(OBJ_PATH)/vulpix/%.o: $(SRC_PATH)/vulpix/%.cpp
	@mkdir -p $(@D);
	@echo "$(call TO_UPPER,$(subst .,,$(suffix $<)))       $@";
	$(call CXX_COMPILE,$<,$@,$(foreach dir,$(BUILD_INCLUDES),-I $(dir)))