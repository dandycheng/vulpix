include $(VPX_ROOT_DIR)/tools/scripts/vars.mk
include $(VPX_ROOT_DIR)/tools/scripts/utils.mk

MAKEFLAGS += --no-print-directory
TEST_LIBS := -lgmock -lgtest
CXX_FLAGS := -g -Wall
OBJ_PATH  := out/obj

OUTPUT_OBJ_FILES = $(subst ./,$(OBJ_PATH)/,$(filter-out ./$(TEST_BINARY).o,$(call GET_OBJ_NAMES,.)))

create-dirs:
	$(call MKDIR,$(dir $(OUTPUT_OBJ_FILES)))