# FilePartitioner
A simple C++ program to perform line-based partitioning of files. Nothing fancy, but does the job just fine and supports several options detailed below! The header file *FilePartitioner.hpp* contains all the partitioning functions, the source file *main.cpp* is just a small wrapper to parse command line input. The program was tested on Linux with GCC 5.4 and Windows with MinGW 5.3.

You can compile the program with a command similar to the following:
```
g++ -std=c++11 -O3 -o FilePartitioner src/main.cpp src/FilePartitioner.hpp
```

### Program parameters
Once compiled, the input of the program must have the following form: 
```
file-location destination-folder partitioning-mode number-of-partitions
```

* *file-location*: location of the file to partition. Any line-based text file will work (.txt files, .csv files, etc.).
* *destination-folder*: must point to an existing folder in your file system; the output files will have the same name as the input one, with an additional suffix corresponding to the partition number.
* *partitioning-mode*
  * *rr* for round-robin partitioning, each partition receives a line from the input file in turn.
  * *ln* for linear partitioning, each partition receives one chunk of the input file.
   * *rd* for random partitioning, each partition receives randomly selected lines from the input file (will most likely not give equally sized partitions).
* *number-of-partitions*: number of partitions to create from the input file.

For instance, on Linux:
```
./FilePartitioner data/myFile.csv data/ rr 8
```

Have fun partitioning your files!
