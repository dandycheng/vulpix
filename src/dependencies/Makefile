DEPENDENCY_MAKEFILES = $(call GET_MAKEFILES,$(DEPS_PATH)/*/*)
DEPENDENCIES = $(subst /,,$(subst $(DEPS_PATH),,$(shell ls -d $(DEPS_PATH)/*/)))

include $(DEPENDENCY_MAKEFILES)

download-deps: $(addprefix download-,$(DEPENDENCIES))
build-deps: $(addprefix build-,$(BUILD_TARGETS))
clean-deps: $(addprefix clean-,$(CLEAN_TARGETS))
	for target in $(CLEAN_DIRS); do \
		if [ -d "$$target" ]; then \
			echo "Cleaning up $$target..."; \
			rm -rf $$target; \
		fi \
	done