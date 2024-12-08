UT_PATHS = $(dir $(shell find unit -name 'Makefile'))
MAKEFLAGS := --no-print-directory

.SILENT:
ut-all:
	for path in $(UT_PATHS); do \
		$(MAKE) -C $$path test; \
	done;

ut-clean:
	for path in $(UT_PATHS); do \
		$(MAKE) -C $$path clean; \
	done;