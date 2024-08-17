#!/bin/bash

# The init pipeline allows you Vulpix to initialize the
# your shell environment by calling the functions in the
# INIT_PIPELINE array. To add arguments, add the function
# call in the following format:
#
#    "[my_init_function](arg1 arg2)"
#
# If the format is not followed, Vulpix will assume this
# is a function.
declare -A INIT_PIPELINE=(
    [0]="[init_vimrc](a b)"
    [1]="init_apt_dependencies"
    [2]="init_env"
)
