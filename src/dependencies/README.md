# Compiling dependencies

Dependencies needed by Vulpix has to follow these 3 rules:
1. It must be able to obtain the source files (`download-deps` target)
2. It must be able to move the relevant source/header files into it's subdirectory `source`, which must be created by the Makefile.
3. It must have a way to clean it's source/object files.
4. All required targets (`download-<dependency>`, `build-<dependency>`, `clean-<dependency>`) must have `dependency` as the exact same name as its folder name. For example: `download-yaml-cpp` must have its folder named `yaml-cpp`.

The rules above is used to accommodate upgrading dependencies easily, as well as provide custom build rules. In the future where the repository gets too large due to dependencies, we can just dynamically download the dependencies and build on our machine.

## Dependency variables

The following are variables that can be used to alter the behavior of the dependencies' build/clean process:

| Variable | Description | Notes |
|-|-|-|
| `CLEAN_DIRS` | Directories to remove when `make clean` is executed. The parent Makefile will call the relevant `clean-<dependency>` target based on the `CLEAN_TARGETS` list. | This is a list that should appended, not overwritten. 
| `BUILD_TARGETS` | This list declares which dependency should be built. Makefile will call the relevant `build-<dependency>` target. | This is a list that should appended, not overwritten. |