include $(VPX_ROOT_DIR)/tools/scripts/utils.mk

UT_PATHS = $(dir $(call GET_MAKEFILES,$(VPX_TESTS)/unit))
MAKEFLAGS := --no-print-directory

.SILENT:
help:
	@echo
	@echo "TARGETS:"
	@echo "ut-all      - Builds all unit tests."
	@echo "ut-clean    - Cleans all unit tests."
	@echo "ut-cleanall - Cleans all unit tests and its dependencies."
	@echo

# TODO: Fix
ut-all:
	for path in $(UT_PATHS); do \
		$(MAKE) -C $$path test; \
	done;

ut-clean:
	for path in $(UT_PATHS); do \
		$(MAKE) -C $$path clean; \
	done;

ut-cleanall: ut-clean
	$(MAKE) -C $(VPX_ROOT_DIR) clean