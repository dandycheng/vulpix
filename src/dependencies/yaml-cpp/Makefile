YAML_CPP_VER := 0.8.0
YAML_CPP_FILE_TYPE := tar.gz
YAML_CPP_URL := https://github.com/jbeder/yaml-cpp/archive/refs/tags/$(YAML_CPP_VER).$(YAML_CPP_FILE_TYPE)
YAML_CPP_INCLUDES = \
	$(DEPS_PATH)/yaml-cpp/source/src \
	$(DEPS_PATH)/yaml-cpp/source/include \
	$(DEPS_PATH)/yaml-cpp/source/include/yaml-cpp \
	$(DEPS_PATH)/yaml-cpp/source/include/node \
	$(DEPS_PATH)/yaml-cpp/source/include/node/detail \
	$(DEPS_PATH)/yaml-cpp/source/include/contrib

BUILD_TARGETS += yaml-cpp
CLEAN_TARGETS += yaml-cpp
CLEAN_DIRS += $(OBJ_PATH)/yaml-cpp
CLEAN_SRCS += $(DEPS_PATH)/yaml-cpp/source

download-yaml-cpp:
	@echo "Downloading yaml-cpp v$(YAML_CPP_VER)...";
	$(call WGET,$(YAML_CPP_URL),yaml-cpp.tar.gz)
	$(call UNTAR,/tmp/yaml-cpp.tar.gz,yaml-cpp-$(YAML_CPP_VER)/src/,$(DEPS_PATH)/yaml-cpp/source)
	$(call UNTAR,/tmp/yaml-cpp.tar.gz,yaml-cpp-$(YAML_CPP_VER)/include,$(DEPS_PATH)/yaml-cpp/source)

clean-yaml-cpp:
	if [ -d "$(OBJ_PATH)/yaml-cpp" ]; then \
		echo "Cleaning yaml-cpp..."; \
	fi

build-yaml-cpp: $(subst $(DEPS_PATH),$(OBJ_PATH),$(call GET_OBJ_NAMES,$(DEPS_PATH)/yaml-cpp))

$(OBJ_PATH)/yaml-cpp/%.o: $(DEPS_PATH)/yaml-cpp/%.cpp
	mkdir -p $(@D)
	@echo "$(call TO_UPPER,$(subst .,,$(suffix $<))) [D]   $@";
	$(CXX) $(CXX_FLAGS) -c $< -o $@ $(foreach dir,$(YAML_CPP_INCLUDES),-I $(dir))