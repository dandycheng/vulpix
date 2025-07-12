#!/bin/bash

MKDIRS=(
    src/build/obj
    src/build/sharedlibs
)

set_env_vars ()
{
    export VPX_ROOT_DIR="$(git rev-parse --show-toplevel | sed 's/ /\\ /g')"
    export VPX_TESTS="$VPX_ROOT_DIR/tests"
}

create_dirs ()
{
    for d in "${MKDIRS[@]}"; do
        mkdir -p "$d"
    done
}

run_setup ()
{
    echo -e "Setting up build environment..."
    set_env_vars
    create_dirs
    echo -e "Environment setup complete."
}

run_setup