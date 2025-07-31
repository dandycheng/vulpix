include $(VPX_ROOT_DIR)/tools/scripts/vars.mk
include $(VPX_ROOT_DIR)/tools/scripts/utils.mk

LIBGIT2_VER := 1.9.1
LIBGIT2_FILE_TYPE := tar.gz
LIBGIT2_URL := https://github.com/libgit2/libgit2/archive/refs/tags/v$(LIBGIT2_VER).$(LIBGIT2_FILE_TYPE)
LIBGIT2_SRC := $(DEPS_PATH)/libgit2/source

# BUILD_TARGETS += libgit2
CLEAN_TARGETS += libgit2
CLEAN_DIRS += $(OBJ_PATH)/libgit2
PP_DEFINES += LIBGIT2_SO=libgit2.so

.SILENT:
clean-libgit2:
	$(call RMDIR,$(OBJ_PATH)/libgit2)

download-libgit2:
	@echo "Downloading libgit2 v$(LIBGIT2_VER)...";
	$(call MKDIR,$(LIBGIT2_SRC))
	$(call WGET,$(LIBGIT2_URL),libgit2.tar.gz)
	$(call UNTAR,/tmp/libgit2.tar.gz,$(LIBGIT2_SRC))

build-libgit2:
	$(call MKDIR,$(LIBGIT2_SRC)/build)
	cd $(LIBGIT2_SRC)/build && cmake .. && cmake --build .; \
	if [ $$? -eq 0 ]; then \
		cp $(LIBGIT2_SRC)/build/libgit2.so $(SHAREDLIBS_DIR); \
	fi
