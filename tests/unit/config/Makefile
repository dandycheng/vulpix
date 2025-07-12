include $(VPX_TESTS)/unit/ut_common.mk

TEST_BINARY := configTest
DEPENDENCIES := yaml-cpp

INCLUDE_PATHS := \
	$(VPX_HEADERS) \
	$(SRC_PATH)/dependencies/yaml-cpp/source/include \
	$(VPX_TESTS)/test-framework/mocks \
	$(VPX_TESTS)/test-framework/mocks/stdlib
	
OBJ_FILE_PATHS := \
	$(SRC_PATH)/build/obj/yaml-cpp/source \
	$(SRC_PATH)/build/obj/vulpix \
	$(VPX_TESTS)/test-framework/out/obj/mocks