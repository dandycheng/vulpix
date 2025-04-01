include $(VULPIX_TESTS)/common.mk

VPX_HEADERS         = $(sort $(dir $(shell find $(VPX_ROOT_DIR)/src/vulpix/* -name '*.h' -or -name '*.hpp')))
OMIT_OBJ_FILES      += $(VPX_ROOT_DIR)/src/build/obj/vulpix/main.o
GET_TEST_OBJ_FILES  = $(filter-out $(OMIT_OBJ_FILES),$(call GET_OBJ_FILES,$(OBJ_PATH) $(OBJ_FILE_PATHS)))

.SILENT:
build-deps:
	echo "Building test dependencies...";
	$(if $(DEPENDENCIES),$(foreach dep,build-$(DEPENDENCIES),$(MAKE) -C $(VPX_ROOT_DIR)/ $(dep) DEBUG=1;),)
	$(MAKE) -C $(VPX_ROOT_DIR)/ build-vulpix-objs DEBUG=1;

.PHONY:
test: create-dirs build-deps $(OUTPUT_OBJ_FILES)
	echo "Linking $(TEST_BINARY)..."
	$(call CXX_LINKALL,out/$(TEST_BINARY),$(call GET_TEST_OBJ_FILES),$(TEST_LIBS))
	$(OBJ_PATH)/../$(TEST_BINARY)

cleanall: clean
	echo "Cleaning vulpix..."
	$(MAKE) -C $(VPX_ROOT_DIR) clean

clean:
	echo "Cleaning $(TEST_BINARY)..."
	rm -rf out

$(OBJ_PATH)/%.o: $(filter-out $(TEST_BINARY).cpp,./%.cpp)
	$(call CXX_COMPILE,$<,$@,$(foreach dir,$(INCLUDE_PATHS),-I $(dir)))