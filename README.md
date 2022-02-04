# Erroneous Detection

## 1. Dependencies
The only dependency for build and run the code is g++ (the GNU C++ compiler) 

### Linux:

For Ubuntu, you need to run the following command:
``` 
sudo apt update && sudo apt install build-essentials
```
For Arch Linux, run:
```
sudo pacman -S base-devel
```
For Fedora, run:
```
dnf groupinstall 'Development Tools'
```
For other distributions, consult the official wiki of your distribution.

### Mac:
Using homebrew:
```
brew install gcc
```

### Windows:
For windows visit here: https://www3.cs.stonybrook.edu/~alee/g++/g++.html
    
## 2. Make
The following project is using a custom makefile and you can easily use the following command in terminal:
```
make
```
## 3. Clean
Make files will be created inside the build folder you can either remove the build folder manually or use the following command:
```
make clean
```