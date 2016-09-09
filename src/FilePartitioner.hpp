//--------------------------------------------------------------------
//
// FilePartitioner.hpp
//
// Created on: 4 Jun 2016
// Author: Pyves
//
//--------------------------------------------------------------------

#ifndef FILEPARTITIONER_HPP_
#define FILEPARTITIONER_HPP_

#include <ctime>
#include <fstream>
#include <random>
#include <vector>

/**
 * Partition files in a round-robin manner: each partition receives a line from the input file in turn.
 */
void RoundRobinPartition(const std::string& filePath,
		const std::string& destFolder, const uint32_t numOfPartitions)
{
	/* Get index of start of name of the file to process. */
	size_t nameDelimiterIndex = filePath.find_last_of("/");
	/* Extract name of file to process. */
	std::string nameOfFile = filePath.substr(nameDelimiterIndex + 1);

	/* Vector containing the partition output files. */
	std::vector<std::ofstream> outputFiles(numOfPartitions);
	/* Initialise the output files. */
	for (uint32_t partition = 0; partition < numOfPartitions; ++partition)
	{
		outputFiles[partition].open(
				destFolder + "/" + nameOfFile + "."
						+ std::to_string(partition));
	}

	/* Variable keeping track of which partition to output to. */
	uint32_t partition = 0;
	/* File to process. */
	std::ifstream input(filePath);
	std::string line;
	/* Parse the file to process line by line and output the line in the correct partition. */
	while (std::getline(input, line))
	{
		/* Output line. */
		outputFiles[partition] << line << std::endl;
		/* Move on to next partition in a round-robin way. */
		partition = (partition + 1) % numOfPartitions;
	}
}

/**
 * Partition files in a linear manner: each partition receives one chunk of the input file.
 * The last partition may receive more lines if the number of lines in the input file is not divisible by the number of partitions.
 */
void LinearPartition(const std::string& filePath, const std::string& destFolder,
		const uint32_t numOfPartitions)
{
	/* Get index of start of name of the file to process. */
	size_t nameDelimiterIndex = filePath.find_last_of("/");
	/* Extract name of file to process. */
	std::string nameOfFile = filePath.substr(nameDelimiterIndex + 1);

	/* Vector containing the partition output files. */
	std::vector<std::ofstream> outputFiles(numOfPartitions);
	/* Initialise the output files. */
	for (uint32_t partition = 0; partition < numOfPartitions; ++partition)
	{
		outputFiles[partition].open(
				destFolder + "/" + nameOfFile + "."
						+ std::to_string(partition));
	}

	/* Variable keeping track of which partition to output to. */
	uint32_t partition = 0;
	/* File to process. */
	std::ifstream input(filePath);

	/* Count the total number of lines in the file. */
	uint32_t numOfLines = 0;
	std::string line;
	while (std::getline(input, line))
		++numOfLines;

	/* Reset input file at the beginning. */
	input.clear();
	input.seekg(0, std::ios::beg);

	/* Number of lines per partition: rounded to integer value. */
	int32_t numOfLinesPerPartition = numOfLines / numOfPartitions;

	/* Represents the current line number. */
	uint32_t currentLine = 0;

	/* Parse the file to process line by line and output the line in the correct partition. */
	while (std::getline(input, line))
	{
		/* Output line. */
		outputFiles[partition] << line << std::endl;

		++currentLine;
		/* Move on to next partition if we have filled in all the lines required in the current partition. */
		/* The remaining lines due to integer approximation are output in the last partition. */
		if (currentLine >= (partition + 1) * numOfLinesPerPartition
				&& partition < numOfPartitions - 1)
		{
			++partition;
		}
	}
}

/**
 * Partition files in a random manner: each partition receives randomly selected lines from the input file.
 * The different partitions are likely to not end up with the same number of lines.
 */
void RandomPartition(const std::string& filePath, const std::string& destFolder,
		const uint32_t numOfPartitions)
{
	/* Get index of start of name of the file to process. */
	size_t nameDelimiterIndex = filePath.find_last_of("/");
	/* Extract name of file to process. */
	std::string nameOfFile = filePath.substr(nameDelimiterIndex + 1);

	/* Vector containing the partition output files. */
	std::vector<std::ofstream> outputFiles(numOfPartitions);
	/* Initialise the output files. */
	for (uint32_t partition = 0; partition < numOfPartitions; ++partition)
	{
		outputFiles[partition].open(
				destFolder + "/" + nameOfFile + "."
						+ std::to_string(partition));
	}

	/* Initialise number distribution. */
	std::uniform_int_distribution<uint32_t> dist(0, numOfPartitions - 1);
	/* Initialise random number generator with time based seed. */
	std::mt19937 rng(time(NULL));

	/* File to process. */
	std::ifstream input(filePath);
	std::string line;
	/* Parse the file to process line by line and output the line in a random partition. */
	while (std::getline(input, line))
	{
		/* Output line. */
		outputFiles[dist(rng)] << line << std::endl;
	}
}

#endif /* FILEPARTITIONER_HPP_ */
