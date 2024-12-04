#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>

int main()
{
	std::vector<int> firstList, secondList, distanceList;
	
	int distance = 0;
	int firstNum = 0;
	int secondNum = 0;
	//open input file
	std::ifstream day1File;
	day1File.open("day1Input");

	if(day1File.is_open())
	{
		day1File >> firstNum;
		day1File >> secondNum;
		firstList.push_back(firstNum);
		secondList.push_back(secondNum);
	}
	while(!day1File.eof())
	{
		//get first input + push
		day1File >> firstNum;
		//get second input + push
		day1File >> secondNum;
		if(!day1File.eof())
		{
			firstList.push_back(firstNum);
			secondList.push_back(secondNum);
		}
	}
	day1File.close();

	//sort smallest to biggest
	std::sort(firstList.begin(), firstList.end(), [&] (int lhs, int rhs) {return lhs < rhs; });
	for(auto& num1 : firstList)
		std::cout << "Num1: " << num1 << std:: endl;
	std::sort(secondList.begin(), secondList.end(), [&] (int lhs, int rhs) {return lhs < rhs; });
	for(auto& num2 : secondList)
		std::cout << "Num2: " << num2 << std:: endl;

	//same size list
	for(unsigned int i = 0; i < firstList.size(); i++)
	{
		distance = 0;
		if(firstList[i] > secondList[i])
			distance = firstList[i] - secondList[i];
		else
			distance = secondList[i] - firstList[i];
		std::cout << "Distance: " << distance << std::endl;
		distanceList.push_back(distance);
	}
	int totalDistance = 0;
	for(auto& distanceNum : distanceList)
		totalDistance += distanceNum;

	std::cout << "TOTAL DISTANCE: " << totalDistance << std::endl;

	//get the similarity score
	std::vector<int> similarityList;
	int similarityScore = 0;
	for(auto& num : firstList)
	{
		similarityScore = num * (std::count(secondList.begin(), secondList.end(), num));
		similarityList.push_back(similarityScore);
	}
	int totalSimilarity = 0;
	for(auto& similarityNum : similarityList)
		totalSimilarity += similarityNum;

	std::cout << "TOTAL SIMILARITY: " << totalSimilarity << std::endl;

	return 0;
}