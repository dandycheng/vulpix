include ../Makefile
include ../../../utils.mk

DEBUG := 1
MAKEFLAGS += --no-print-directory
TEST_BINARY := config_test

INCLUDE_PATHS := \
	../../../include/vulpix \
	../../../include/vulpix/debug \
	../../../include/vulpix/shell \
	../../../include/vulpix/stdio \
	../../../include/vulpix/utils \
	../../../src/dependencies/yaml-cpp/source/include
	
OBJ_FILE_PATHS := \
	../../../src/build/obj/yaml-cpp/source \
	../../../src/build/obj/vulpix

OMIT_OBJ_FILES := \
	../../../src/build/obj/vulpix/main.o

DEPENDENCIES := \
	yaml-cpp

LIBS := \
	gtest \
	gmock

test: out/$(TEST_BINARY)


# TODO: test coverage
.SILENT:
out/$(TEST_BINARY): build-deps
	echo "Building test suite $(TEST_BINARY)...";
	$(call MKDIR,out/obj)
	echo "Linking...";
	$(CXX) -g -o out/obj/config_test.o -c config_test.cpp $(foreach dir,$(INCLUDE_PATHS),-I $(dir));
	$(CXX) -g -o $@ out/obj/config_test.o $(filter-out $(OMIT_OBJ_FILES),$(call GET_OBJ_FILES,$(OBJ_FILE_PATHS))) -lgtest -lgmock
	./$@;

.SILENT:
build-deps:
	echo "Building test dependencies...";
	$(foreach dep,build-$(DEPENDENCIES),$(MAKE) -C ../../../ $(dep) DEBUG=1;)
	$(MAKE) -C ../../../ build-vulpix-objs DEBUG=0;

.PHONY:
clean:
	$(MAKE) -C ../../../ clean
	rm -rf out