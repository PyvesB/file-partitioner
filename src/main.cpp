//--------------------------------------------------------------------
//
// main.cpp
//
// Created on: 4 Jun 2016
// Author: Pyves
//
//--------------------------------------------------------------------

#include <iostream>

#include "FilePartitioner.hpp"

int main(int argc, char *argv[])
{

	/* Pattern for input: file-location destination-folder partitioning-mode number-of-partitions */
	if (argc != 5)
	{
		std::cerr
				<< "Incorrect input. Please specify the file location, destination folder, partitioner mode and number of partitions."
				<< std::endl;
		return EXIT_FAILURE;
	}

	/* Parse the input. */
	char* filePath = argv[1];
	std::string filePathString(filePath);

	char* destFolder = argv[2];
	std::string destFolderString(destFolder);

	char* mode = argv[3];
	std::string modeString(mode);

	char* numOfPartitionsChars = argv[4];
	uint32_t numOfPartitions;
	try
	{
		numOfPartitions = std::stoi(numOfPartitionsChars);
	} catch (std::exception const & e)
	{
		std::cerr
				<< "Incorrect input. Please specify the file location, destination folder, partitioner mode and number of partitions."
				<< std::endl;
		return EXIT_FAILURE;
	}

	if (modeString == "rr")
	{
		std::cout << "FilePartitioner: starting round-robin partitioning..."
				<< std::endl;
		RoundRobinPartition(filePathString, destFolderString, numOfPartitions);
	}
	else if (modeString == "ln")
	{
		std::cout << "FilePartitioner: starting linear partitioning..."
				<< std::endl;
		LinearPartition(filePathString, destFolderString, numOfPartitions);
	}
	else if (modeString == "rd")
	{
		std::cout << "FilePartitioner: starting random partitioning..."
				<< std::endl;
		RandomPartition(filePathString, destFolderString, numOfPartitions);
	}
	else
	{
		std::cerr
				<< "Incorrect mode. Please use rr for round-robin partitioning, ln for linear partitioning or rd for random partitioning."
				<< std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
