MAKEFLAGS += --no-print-directory
VPX_HEADERS = $(sort $(dir $(shell find ../../../src/vulpix/* -name '*.h' -or -name '*.hpp')))
OMIT_OBJ_FILES += ../../../src/build/obj/vulpix/main.o

setup-env:
	$(call MKDIR,$(OBJ_DIR))

.SILENT:
build-deps:
	echo "Building test dependencies...";
	$(foreach dep,build-$(DEPENDENCIES),$(MAKE) -C ../../../ $(dep) DEBUG=1;)
	$(MAKE) -C ../../../ build-vulpix-objs DEBUG=1;

.PHONY:
test: setup-env build-deps $(OUTPUT_OBJ_FILES)
	$(CXX) $(TEST_CXX_FLAGS) -o out/$(TEST_BINARY) $(filter-out $(OMIT_OBJ_FILES),$(call GET_OBJ_FILES,$(OBJ_DIR) $(OBJ_FILE_PATHS))) -lgtest -lgmock
	$(OBJ_DIR)/../$(TEST_BINARY)

# Clean with the main Makefile to clean dependencies
clean:
	$(MAKE) -C ../../.. clean
	rm -rf out

$(OBJ_DIR)/%.o: $(filter-out $(TEST_BINARY).cpp,./%.cpp)
	$(CXX) $(TEST_CXX_FLAGS) -o $@ -c $< $(foreach dir,$(INCLUDE_PATHS),-I $(dir));