COMMON_MAKEFILE_INCLUDE_DIRECTIVE := 1

CXX         := g++
CXX_FLAGS   := -std=c++14
BUILD_DEPS  := cmake g++
TEST_DEPS   := libgtest-dev libgmock-dev
VPX_HEADERS = $(sort $(dir $(call GET_HEADER_FILES,$(SRC_PATH)/vulpix/*)))