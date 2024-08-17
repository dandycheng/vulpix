#!/bin/bash

CONFIG_FILE="config";
AVAIL_CONFIGS=(
    "STARTUP_DIRECTORY"
    "STARTUP_DIRECTORY1"
);

init_env ()
{
    for conf in "${AVAIL_CONFIGS[@]}"; do
        local config_val=$(__config_get_val $conf);

        if [ -n "$config_val" ]; then
            case $conf in
                STARTUP_DIRECTORY)
                    VPX_STARTUP_DIRECTORY="$config_val";
                    ;;
            esac;
        fi;
    done;

    echo "Environment initialized.";
    goto_start_dir;
}

goto_start_dir ()
{
    __validate_config_option

    # FIX: No directory found
    if [ $? -eq 0 ] && [ ! -d $VPX_STARTUP_DIRECTORY ]; then
        echo "Startup directory $VPX_STARTUP_DIRECTORY does not exist, stopping.";
        return 1;
    fi;

    cd $VPX_STARTUP_DIRECTORY;
}

__validate_config_option ()
{
    if [ -n "$1" ]; then
        echo "$1 config option not set.";
        return 1;
    fi;

    return 0;
}

__config_get_val ()
{
    if [ -n "$(grep $1 config)" ]; then
        grep -Po "(?<=$1=).*" $CONFIG_FILE;
    fi;
}
