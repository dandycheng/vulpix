include $(VPX_TESTS)/unit/ut_common.mk

TEST_BINARY := packageManagerTest
DEPENDENCIES := yaml-cpp
TEST_LDFLAGS := $(STATICLIBS_DIR)
TEST_LIBS += yamlcpp

INCLUDE_PATHS := \
	$(VPX_HEADERS) \
	$(DEPS_PATH)/yaml-cpp/source/include \
	$(VPX_TESTS)/test-framework/mocks \
	$(VPX_TESTS)/test-framework/mocks/stdlib
	
OBJ_FILE_PATHS := \
	$(OBJ_PATH)/vulpix