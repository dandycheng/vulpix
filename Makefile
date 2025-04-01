VULPIX_VER := 0.0.1-rc1

$(if $(VPX_ROOT_DIR),,$(error Build environment is not setup, run setup_env.sh first))

include tools/scripts/vars.mk
include tools/scripts/utils.mk
include $(SRC_PATH)/Makefile
include $(DEPS_PATH)/Makefile

CLEAN_DIRS := \
	$(SRC_PATH)/build \
	$(OBJ_PATH)/vulpix

install-build-deps:
	sudo $(PKG_MANAGER) update; \
	for dep in $(BUILD_DEPS); do \
		if [ -n "`dpkg -l | grep $$dep | awk '{print $2}'`" ]; then \
			echo "$$dep is already installed."; \
		else \
			sudo $(PKG_MANAGER) install -y $(BUILD_DEPS); \
		fi \
	done

install-test-deps:
	sudo $(PKG_MANAGER) update
	sudo $(PKG_MANAGER) install -y $(TEST_DEPS)

remove-build-deps:
	sudo $(PKG_MANAGER) remove -y $(BUILD_DEPS)

.PHONY:
clean: clean-deps
	rm -rf $(CLEAN_DIRS)

cleanall: clean
	rm -rf $(CLEAN_SRCS)