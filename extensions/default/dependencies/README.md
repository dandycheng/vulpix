# Installing dependency packages

Currently Vulpix supports installation of packages with the Advanced Package Tool (APT). To enable Vulpix
to install dependencies, name your dependencies in a file name with the format `<filename>_apt_dependencies`,
and use a newline as a delimiter to separate dependency names. Vulpix will automatically find file names
ending with `apt_dependencies`, and install dependencies within it.
