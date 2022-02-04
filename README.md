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

## 4. Usage
In the main directory a binary will be made if you make the code. It is called "Connecterra". You should call it from terminal with command below:
```
./Connecterra csvFileLocation/csvFile.csv
```
Address to csv file can be local or global.

After running the code result will be stored in a csv file in the root folder of the project with the name of Result.csv, and the result will be shown on the console as well.

## 5. Test
For test the application a pythn script has been developed and it can be found in the test folder. This script generates a controlled random data with custom number of nodes and samples. Then it will generate a csv file ("testData.csv") acording to the given data. That csv file can be used in order to test the main application.

The only dependency for the test generator script is python >=3.5.

The test generator script can be run with the following command:
```
cd Test
python generateTestCsv.py
```

The are two other files in the Test folder, "given.csv" and "testData.csv". "given.csv" is the data given with the assignment and the "testData.csv" is a test data generated with the script for 5 nodes and 100 samples per node.
