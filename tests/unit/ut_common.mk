UT_COMMON_MAKEFILE_INCLUDE_DIRECTIVE := 1

include $(VPX_TESTS)/common.mk
include $(VPX_ROOT_DIR)/tools/scripts/common.mk
include $(VPX_ROOT_DIR)/tools/scripts/utils.mk

TEST_OBJ_FILES          = $(subst ./,$(OBJ_PATH)/,$(call GET_OBJ_NAMES,.))
GET_TEST_DEP_OBJ_FILES  = $(filter-out $(OMIT_OBJ_FILES),$(call GET_OBJ_FILES,$(OBJ_FILE_PATHS)))
OMIT_OBJ_FILES          := $(SRC_PATH)/build/obj/vulpix/main.o

# TODO: Create debug and release tests (maybe consider stop using compiled object files and include headers instead?)
.SILENT:
build-deps:
	echo "Building test dependencies...";
	$(if $(DEPENDENCIES),$(foreach dep,build-$(DEPENDENCIES),$(MAKE) -C $(VPX_ROOT_DIR) $(dep) DEBUG=1;),)
	$(MAKE) -C $(VPX_ROOT_DIR)/ build-vulpix-objs DEBUG=1;

setup-env:
	$(call MKDIR,$(CURDIR)/$(OBJ_PATH))

.PHONY:
test: setup-env build-deps $(TEST_OBJ_FILES)
	echo "Linking $(TEST_BINARY)..."
	$(call CXX_LINKALL,out/$(TEST_BINARY),$(call GET_TEST_DEP_OBJ_FILES) $(TEST_OBJ_FILES),$(TEST_LIBS))
	$(TEST_BINARY_PATH)/$(TEST_BINARY)

cleanall: clean
	$(MAKE) -C $(VPX_ROOT_DIR) clean

clean:
	echo "Cleaning $(TEST_BINARY)..."
	rm -rf out

$(OBJ_PATH)/%.o: %.cpp
	 $(call CXX_COMPILE,$<,$@,$(foreach dir,$(INCLUDE_PATHS),-I $(dir)))