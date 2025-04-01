include $(VULPIX_TESTS)/ut_common.mk

TEST_BINARY := packageManagerTest
DEPENDENCIES := yaml-cpp

SRC_FILES := $(call GET_CPP_FILES,.)

INCLUDE_PATHS := \
	$(VPX_HEADERS) \
	$(TESTS_DIR)/test-framework/mocks \
	$(TESTS_DIR)/test-framework/mocks/stdlib
	
OBJ_FILE_PATHS := \
	$(VPX_ROOT_DIR)/src/build/obj/yaml-cpp/source \
	$(VPX_ROOT_DIR)/src/build/obj/vulpix \
	$(TESTS_DIR)/test-framework/out/obj/mocks

OMIT_OBJ_FILES += $(VPX_ROOT_DIR)/src/build/obj/vulpix/main.o