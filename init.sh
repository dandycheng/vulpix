#!/bin/bash

init ()
{
    echo -e "\nRunning initialization pipeline...";

    for init_func in "${INIT_PIPELINE[@]}"; do
        local func=$(echo $init_func | sed -e s"/\[//g" -e s"/\].*//g");
        local args=$(echo $init_func | sed -e s"/^.*\](//g" -e s"/)$//g");

        if [ -n "$func" ]; then
            type $func &> /dev/null;

            if [ $? -eq 0 ]; then
                if [ -n "$args" ]; then
                    eval "$func $args";
                else
                    echo "Initialize: $func";
                    eval "$func";
                fi;
            else
                echo "$func is not defined, skipping.";
            fi;
        fi;
    done;
}
