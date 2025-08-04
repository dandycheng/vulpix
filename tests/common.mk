include $(VPX_ROOT_DIR)/tools/scripts/vars.mk

MAKEFLAGS += --no-print-directory
TEST_LIBS        := gmock gtest
CXX_FLAGS        := -g -Wall
TEST_OBJ_PATH    := out/obj
TEST_BINARY_PATH := out

create-dirs:
	$(call MKDIR,$(dir $(OBJ_FILES)))