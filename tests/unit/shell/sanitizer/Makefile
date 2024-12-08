include ../../../../utils.mk
include ../../../test_common.mk
include ../../ut_common.mk

TEST_BINARY := sanitizerTest
DEPENDENCIES := yaml-cpp
ROOT_DIR_RELATIVE := ../../../..

INCLUDE_PATHS := \
	$(VPX_HEADERS) \
	$(ROOT_DIR_RELATIVE)/tests/test-framework/mocks \
	$(ROOT_DIR_RELATIVE)/tests/test-framework/mocks/stdlib
	
OBJ_FILE_PATHS := \
	$(ROOT_DIR_RELATIVE)/src/build/obj/yaml-cpp/source \
	$(ROOT_DIR_RELATIVE)/src/build/obj/vulpix \
	$(ROOT_DIR_RELATIVE)/tests/test-framework/out/obj/mocks

OMIT_OBJ_FILES += $(ROOT_DIR_RELATIVE)/src/build/obj/vulpix/main.o