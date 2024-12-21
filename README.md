# vulpix

Vulpix is an extensible utility script that helps to ease your development process.

When running your development environment on different Linux machines or containers, the development process may differ. Vulpix alleviates the process of setting up your development environment by providing utilities such as:
- Installing dependencies based on your configuration file.
- Installing custom plugins like [git-prompt](https://github.com/git/git/blob/master/contrib/completion/git-prompt.sh) by providing a URL and installation instructions.
- Event listeners to invoke commands or functions after a command is invoked in the command line.

# Architecture

![Architecture](docs/Architecture.jpg)