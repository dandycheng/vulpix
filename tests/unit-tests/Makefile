UNIT_TEST_LIBRARIES := \
	gtest \
	gmock

UNIT_TEST_CXX_FLAGS := \
	-g \
	$(foreach lib,$(UNIT_TEST_LIBRARIES),-l$(lib))

INCLUDE_TESTS := \
	config

UNIT_TEST_COMMON_INCLUDES := \
	../../include/vulpix

UNIT_TEST_OBJ := obj
UNIT_TEST_OUT := out

setup-test-env:
	$(call MKDIR,$(UNIT_TEST_OBJ))
	$(call MKDIR,$(UNIT_TEST_OUT))

all: $(UNIT_TEST_OUT)/config_test

testall: run-$(INCLUDE_TESTS)-test