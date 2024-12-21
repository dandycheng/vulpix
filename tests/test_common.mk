TEST_LIBS := \
	-lgmock \
	-lgtests
TEST_CXX_FLAGS := -g -Wall
OBJ_PATH := out/obj

OUTPUT_OBJ_FILES = $(subst ./,$(OBJ_PATH)/,$(filter-out ./$(TEST_BINARY).o,$(call GET_OBJ_NAMES,.)))