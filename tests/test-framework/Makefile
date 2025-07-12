include $(VPX_ROOT_DIR)/tools/scripts/utils.mk

INCLUDE_PATHS := \
	mocks \
	mocks/stdlib \
	$(DEPS_PATH)/yaml-cpp/source/include

mocks: $(addprefix out/obj/,$(call GET_OBJ_NAMES,mocks))

$(addprefix out/obj/,$(call GET_OBJ_NAMES,mocks)): $(call GET_CPP_FILES,mocks)
	$(call MKDIR,$(dir $@))
	$(CXX) $(CXX_FLAGS) -o $@ -c $< $(foreach dir,$(INCLUDE_PATHS),-I $(dir));

.PHONY:
clean:
	rm -rf out;