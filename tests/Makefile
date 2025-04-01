UT_PATHS = $(dir $(shell find unit -name 'Makefile'))
MAKEFLAGS := --no-print-directory

help:
	@echo
	@echo "Targets"
	@echo "--------------------------------"
	@echo "ut-all   - Builds all unit tests."
	@echo "ut-clean - Cleans all unit tests."
	@echo

.SILENT:
ut-all:
	for path in $(UT_PATHS); do \
		$(MAKE) -C $$path test; \
	done;

ut-clean:
	for path in $(UT_PATHS); do \
		$(MAKE) -C $$path clean; \
	done;