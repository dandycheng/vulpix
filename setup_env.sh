#!/bin/bash

set_env_vars ()
{
    export VPX_ROOT_DIR="$(pwd | sed 's/ /\\ /g')"
    export VULPIX_TESTS="$VPX_ROOT_DIR/tests"
}

create_dirs ()
{
    mkdir -p \
        src/build/obj \
        src/build/out
    
    return $?
}

run_setup ()
{
    echo -e "Setting up build environment..."
    set_env_vars
    create_dirs
    echo -e "Environment setup complete."
}

run_setup