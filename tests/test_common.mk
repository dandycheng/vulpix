TEST_LIBS := \
	-lgmock \
	-lgtests
TEST_CXX_FLAGS := -g
OBJ_DIR := out/obj

OUTPUT_OBJ_FILES = $(subst ./,$(OBJ_DIR)/,$(filter-out ./$(TEST_BINARY).o,$(call GET_OBJ_NAMES,.)))