#!/bin/bash

init_plugins ()
{

}

install_plugin ()
{
	local optstr="g:l:";
	local is_git_repo=1;
	local url="";

	while getopts $optstr opt; do
		case $opt in
			g)
				is_git_repo=0;
			    ;;
			l)
				url=$optstr;
			    ;;
			*)
				echo "Invalid argument $opt.";
				echo "Usage:";
				echo -e "\n-g - Install a plugin from a git repository. If this is not provided, Vulpix will assume that";
				echo "	   this is a custom plugin that is to be downloaded as a raw file.";
				echo -e "\n-l - URL of the plugin.";
			    ;;
		esac;
	done;
}

install_default_plugins ()
{

}
