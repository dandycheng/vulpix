#!/bin/bash

init_dependencies ()
{
    install_apt_deps;
}

install_apt_deps ()
{
    local dep_files=$(ls | grep -Po ".*_apt_dependencies");

    echo "Installing dependency packages...";

    for dep_file in ${dep_files[@]}; do
        echo "Probing $dep_file...";

        local deps=$(cat $dep_file | sed "s/\r|\n/ /g");

        if [ -n "$deps" ]; then
            sudo apt install $deps;
            
            if [ $? -ne 0 ]; then
                echo "An error has occured when installing dependencies in $dep_file. Please check whether the dependency names are correct.";
            fi;
        fi;
    done;
}
