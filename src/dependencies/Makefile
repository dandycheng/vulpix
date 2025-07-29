include $(VPX_ROOT_DIR)/tools/scripts/vars.mk
include $(VPX_ROOT_DIR)/tools/scripts/utils.mk

DEPENDENCY_MAKEFILES = $(shell find $(DEPS_PATH) -mindepth 2 -maxdepth 2 -iname 'makefile')
DEPENDENCIES = $(subst /,,$(subst $(DEPS_PATH),,$(shell ls -d $(DEPS_PATH)/*/)))

include $(DEPENDENCY_MAKEFILES)

download-deps: $(addprefix download-,$(DEPENDENCIES))
build-deps: $(addprefix build-,$(BUILD_TARGETS))

# TODO: Use a separate target to allow cleanup $(MAKE) -C <dep_path> cleanup
# FIX: Second run throws error
clean-deps: $(addprefix clean-,$(DEPENDENCIES))
