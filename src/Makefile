BINARY_NAME := vulpix
VPX_BUILD_SRC = $(shell find $(SRC_PATH)/vulpix/* -name '*.cpp')
VPX_HEADERS = $(sort $(dir $(shell find $(SRC_PATH)/vulpix/* -name '*.h' -or -name '*.hpp')))

VULPIX_BUILD_INCLUDES += \
	$(VPX_HEADERS) \
	$(DEPS_PATH)/yaml-cpp/source/include \
	$(DEPS_PATH)/yaml-cpp/source/src

ifeq ($(DEBUG),1)
	CXX_FLAGS += -D DEBUG
	CXX_FLAGS += -g
endif

build-vulpix-objs: $(subst $(SRC_PATH),$(OBJ_PATH),$(call GET_OBJ_NAMES,$(SRC_PATH)/vulpix))
build: $(BUILD_OUT_PATH)/$(BINARY_NAME)
get-build-config:
ifeq ($(DEBUG),1)
	echo "\nDEBUGGING IS ON.\n"
else
	echo "\nDEBUGGING IS OFF.\n"
endif

.SILENT:
$(BUILD_OUT_PATH)/$(BINARY_NAME): get-build-config build-deps build-vulpix-objs
	mkdir -p $(BUILD_OUT_PATH);
	echo "\nLinking binary $@...";
	$(CXX) $(CXX_FLAGS) -o $@ $(call GET_OBJ_FILES,$(OBJ_PATH));

	if [ $$? -eq 0 ]; then \
		echo "Build complete."; \
		echo "Output binary: $@"; \
	fi;

$(OBJ_PATH)/vulpix/%.o: $(SRC_PATH)/vulpix/%.cpp
	@mkdir -p $(@D);
	@echo "$(call TO_UPPER,$(subst .,,$(suffix $<)))       $@";
	$(CXX) $(CXX_FLAGS) -c $< -o $@ $(foreach dir,$(VULPIX_BUILD_INCLUDES),-I $(dir));