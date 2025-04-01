include $(VPX_ROOT_DIR)/tools/scripts/utils.mk
include $(VULPIX_TESTS)/unit/ut_common.mk

TEST_BINARY := configTest
DEPENDENCIES := yaml-cpp

INCLUDE_PATHS := \
	$(VPX_HEADERS) \
	$(VPX_ROOT_DIR)/src/dependencies/yaml-cpp/source/include \
	../../test-framework/mocks \
	../../test-framework/mocks/stdlib
	
OBJ_FILE_PATHS := \
	$(VPX_ROOT_DIR)/src/build/obj/yaml-cpp/source \
	$(VPX_ROOT_DIR)/src/build/obj/vulpix \
	../../test-framework/out/obj/mocks