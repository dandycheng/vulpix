include ../../../utils.mk
include ../../test_common.mk
include ../ut_common.mk

TEST_BINARY := configTest
DEPENDENCIES := yaml-cpp

INCLUDE_PATHS := \
	$(VPX_HEADERS) \
	$(ROOT_DIR_RELATIVE)/src/dependencies/yaml-cpp/source/include \
	../../test-framework/mocks \
	../../test-framework/mocks/stdlib
	
OBJ_FILE_PATHS := \
	$(ROOT_DIR_RELATIVE)/src/build/obj/yaml-cpp/source \
	$(ROOT_DIR_RELATIVE)/src/build/obj/vulpix \
	../../test-framework/out/obj/mocks

OMIT_OBJ_FILES += $(ROOT_DIR_RELATIVE)/src/build/obj/vulpix/main.o