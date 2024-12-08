MAKEFLAGS += --no-print-directory
ROOT_DIR_RELATIVE := ../../..
VPX_HEADERS = $(sort $(dir $(shell find $(ROOT_DIR_RELATIVE)/src/vulpix/* -name '*.h' -or -name '*.hpp')))
OMIT_OBJ_FILES += ../../../src/build/obj/vulpix/main.o

setup-env:
	$(call MKDIR,$(OBJ_DIR))

.SILENT:
build-deps:
	echo "Building test dependencies...";
	if [ -n "$(DEPENDENCIES)" ]; then \
		$(foreach dep,build-$(DEPENDENCIES),$(MAKE) -C $(ROOT_DIR_RELATIVE)/ $(dep) DEBUG=1;) \
	fi
	$(MAKE) -C $(ROOT_DIR_RELATIVE)/ build-vulpix-objs DEBUG=1;

.PHONY:
test: setup-env build-deps $(OUTPUT_OBJ_FILES)
	echo "Linking $(TEST_BINARY)..."
	$(CXX) $(TEST_CXX_FLAGS) -o out/$(TEST_BINARY) $(filter-out $(OMIT_OBJ_FILES),$(call GET_OBJ_FILES,$(OBJ_DIR) $(OBJ_FILE_PATHS))) -lgtest -lgmock
	$(OBJ_DIR)/../$(TEST_BINARY)

.SILENT:
clean:
	echo "Cleaning $(TEST_BINARY)..."
	$(MAKE) -C $(ROOT_DIR_RELATIVE) clean > /dev/null
	rm -rf out

$(OBJ_DIR)/%.o: $(filter-out $(TEST_BINARY).cpp,./%.cpp)
	$(CXX) $(TEST_CXX_FLAGS) -o $@ -c $< $(foreach dir,$(INCLUDE_PATHS),-I $(dir))	;