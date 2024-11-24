include ../../../utils.mk
include ../../test_common.mk
include ../ut_common.mk

TEST_BINARY := configTest
DEPENDENCIES := yaml-cpp

INCLUDE_PATHS := \
	$(VPX_HEADERS) \
	../../../src/dependencies/yaml-cpp/source/include \
	../../test-framework/mocks \
	../../test-framework/mocks/stdlib
	
OBJ_FILE_PATHS := \
	../../../src/build/obj/yaml-cpp/source \
	../../../src/build/obj/vulpix \
	../../test-framework/out/obj/mocks

OMIT_OBJ_FILES += ../../../src/build/obj/vulpix/main.o