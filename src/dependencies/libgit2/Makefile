include $(VPX_ROOT_DIR)/tools/scripts/vars.mk
include $(VPX_ROOT_DIR)/tools/scripts/utils.mk

LIBGIT2_VER := v1.9.1
LIBGIT2_FILE_TYPE := tar.gz
LIBGIT2_URL := https://github.com/libgit2/libgit2/archive/refs/tags/$(LIBGIT2_VER).$(LIBGIT2_FILE_TYPE)

BUILD_TARGETS += libgit2
CLEAN_TARGETS += libgit2
CLEAN_DIRS += $(OBJ_PATH)/libgit2

.SILENT:
clean-libgit2:
	$(call RMDIR,$(OBJ_PATH)/libgit2)

download-libgit2:
	@echo "Downloading libgit2 v$(LIBGIT2_VER)...";
	$(call WGET,$(LIBGIT2_URL),libgit2.tar.gz)
	$(call UNTAR,/tmp/libgit2.tar.gz,$(DEPS_PATH)/libgit2)

build-libgit2:
	$(call MKDIR,$(DEPS_PATH)/libgit2/build)
	cd $(DEPS_PATH)/libgit2/build && cmake .. && cmake --build .; \
	if [ $$? -eq 0 ]; then \
		mv libgit2.so $(SHAREDLIBS_DIR); \
	fi

# TODO: Refactor
$(OBJ_PATH)/libgit2/%.o: $(DEPS_PATH)/libgit2/%.cpp
	mkdir -p $(@D)
	@echo "$(call TO_UPPER,$(subst .,,$(suffix $<))) [D]   $@";
	$(CXX) $(CXX_FLAGS) -c $< -o $@ $(foreach dir,$(LIBGIT2_INCLUDES),-I $(dir))