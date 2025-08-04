include $(VPX_TESTS)/common.mk
include $(VPX_ROOT_DIR)/tools/scripts/common.mk
include $(VPX_ROOT_DIR)/tools/scripts/utils.mk

UT_SRC_FILE              = $(TEST_BINARY).cpp
UT_OBJ_FILE              = $(addsuffix .o,$(sort $(basename $(UT_SRC_FILE))))
TEST_OBJ_FILES           = $(subst ./,$(TEST_OBJ_PATH)/,$(call GET_OBJ_NAMES,.))
OMIT_OBJ_FILES           = \
	$(SRC_PATH)/build/obj/vulpix/main.o \
	$(TEST_OBJ_PATH)/$(UT_OBJ_FILE)

GET_TEST_DEP_OBJ_FILES   = \
	$(filter-out $(OMIT_OBJ_FILES),$(call GET_OBJ_FILES,$(OBJ_FILE_PATHS))) \
	$(TEST_OBJ_FILES)

# TODO: Create debug and release tests (maybe consider stop using compiled object files and include headers instead?)
.SILENT:
build-deps:
	echo "Building test dependencies...";
	$(if $(DEPENDENCIES),$(foreach dep,$(DEPENDENCIES),$(MAKE) -C $(DEPS_PATH)/$(dep) debug=1 build-$(dep);),)
	$(MAKE) -C $(SRC_PATH) build-vulpix-objs DEBUG=1;

setup-env:
	$(call MKDIR,$(CURDIR)/$(TEST_OBJ_PATH))

# FIX: Non zero exit code doesn't stop test from running!
.PHONY:
test: setup-env build-deps $(TEST_OBJ_FILES)
	echo "Linking $(TEST_BINARY)..."
	$(call CXX_LINK,out/$(TEST_BINARY),$(call GET_TEST_DEP_OBJ_FILES),$(TEST_LDFLAGS),$(TEST_LIBS))

	if [ $$? -eq 0 ]; then \
		$(TEST_BINARY_PATH)/$(TEST_BINARY); \
	fi

cleanall: clean
	$(MAKE) -C $(VPX_ROOT_DIR) clean

clean:
	echo "Cleaning $(TEST_BINARY)..."
	rm -rf out

$(TEST_OBJ_PATH)/%.o: %.cpp
	 $(call CXX_COMPILE,$(foreach dir,$(INCLUDE_PATHS),-I $(dir)))
