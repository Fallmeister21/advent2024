#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <regex>

int main()
{
	//regex stuff
	std::smatch foundMuls;
	std::smatch foundDoDont;
	std::regex stateMatch("mul\\(\\d+,\\d+\\)|do\\(\\)|don't\\(\\)");
	//open input file
	std::ifstream day3File;
	//mul line holder
	std::string checkMul = "";
	day3File.open("day3Input");


	bool doState = true;
	std::vector<int> products;
	if(day3File.is_open())
	{
		getline(day3File, checkMul);
	}
	std::string tempMul = "";
	while(!day3File.eof())
	{
		tempMul = "";
		getline(day3File, tempMul);
		if(!day3File.eof())
		{
			checkMul += tempMul;
		}
	}

	std::string gotDoDont = "";
	while(std::regex_search(checkMul, foundMuls, stateMatch))
	{
		std::string workMul = foundMuls.str(0);

		

		if(workMul == "do()")
			doState = true;
		else if(workMul == "don't()")
			doState = false;
		else
		{
			//guaranteed to be here
			std::string::size_type pos1 = workMul.find('(');
			std::string::size_type pos2 = workMul.find(',');
			std::string::size_type pos3 = workMul.find(')');

			int num1 = std::stoi(workMul.substr(pos1 + 1, pos2 - 1));
			int num2 = std::stoi(workMul.substr(pos2 + 1, pos3 - 1));
			
			workMul = foundMuls.str(0);
			int product = num1 * num2;
			std::cout << "Workmul " << workMul  << std::endl;

			if(doState)
			{
				products.push_back(product);
				std::cout << "Num1: " << num1 << " Num2: " << num2 << std::endl;
			}
		}

		checkMul = foundMuls.suffix().str();
	}

	int totalOfProducts = 0;
	for(auto& product : products)
		totalOfProducts += product;

	std::cout << "Total of all products: " << totalOfProducts << std::endl;

	day3File.close();

	return 0;
}