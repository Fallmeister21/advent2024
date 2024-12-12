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
#include <map>

int main()
{
	//regex stuff
	std::smatch foundRules;
	std::regex ruleMatch("(\\d+)\\|(\\d+)");
	//open input file
	std::ifstream day5File;
	std::string inRule = "";
	int leftRule = 0;
	int rightRule = 0;
	bool doneWithSection1 = false;
	bool swapped = false;

	//rules and pages
	std::multimap<int, int> ruleList;
	std::vector<std::vector<int>> pagesList;
	bool goodPageList = true;
	std::vector<std::vector<int>> orderedPagesList;
	std::vector<std::vector<int>> swappedPagesList;
	day5File.open("day5Input");

	if(day5File.is_open())
	{
		getline(day5File, inRule);
		std::regex_search(inRule, foundRules, ruleMatch);
		leftRule = std::stoi(foundRules.str(1));
		rightRule = std::stoi(foundRules.str(2));
		ruleList.insert({ leftRule, rightRule });
	}

	while(!day5File.eof())
	{
		getline(day5File, inRule);
		std::regex_search(inRule, foundRules, ruleMatch);
		//section1
		if(foundRules.str(0) != "")
		{
			leftRule = std::stoi(foundRules.str(1));
			rightRule = std::stoi(foundRules.str(2));
			ruleList.insert({ leftRule, rightRule });
		}
		//section2
		else if (foundRules.str(0) == "")
			doneWithSection1 = true;
		if(doneWithSection1 && inRule != "")
		{
			std::string workingPages = inRule;
			int page = 0;
			std::vector<int> tempPages;
			size_t commaPos = 0;
			while((commaPos = workingPages.find(",")) != std::string::npos)
			{
				page = std::stoi(workingPages.substr(0, commaPos));
				tempPages.push_back(page);
				workingPages.erase(0, commaPos + 1);
			}
			tempPages.push_back(std::stoi(workingPages));
			pagesList.push_back(tempPages);
		}
	}

	//loop through all pages
	for(unsigned int i = 0; i < pagesList.size(); i++)
	{
		swapped = false;
		//for each page in the list of pageLists
		for(unsigned int page = 0; page < pagesList[i].size(); page++)
		{
			//page from page list
			//double check multimap
			auto ruleIterator = ruleList.begin();
			while(ruleIterator != ruleList.end())
			{
				if(!goodPageList)
					goodPageList = true;
				if(ruleIterator->first == pagesList[i][page])
				{
					auto xSidePageIterator = find(pagesList[i].begin(), pagesList[i].end(), pagesList[i][page]);
					auto ySidePageIterator = find(pagesList[i].begin(), pagesList[i].end(), ruleIterator->second);
					//std::cout << "Got rule " << *xSidePageIterator << " and " << *ySidePageIterator << std::endl;
					if(xSidePageIterator > ySidePageIterator)
					{
						goodPageList = false;
						swapped = true;
						int tempX = 0;
						int tempY = 0;
						//std::cout << "Swapping " << *xSidePageIterator << " and " << *ySidePageIterator << std::endl;
						tempX = *xSidePageIterator;
						tempY = *ySidePageIterator;
						*ySidePageIterator = tempX;
						*xSidePageIterator = tempY;
						//std::cout << "After swapping " << *xSidePageIterator << " and " << *ySidePageIterator << std::endl;
						//try again!
						ruleIterator = ruleList.begin();
						page = 0;
					}
					//swap values from xSideIterator and ySideIterator and reset iterator and check entire list again
				}
				ruleIterator++;
				
			}
		}
		if(goodPageList && !swapped)
		{
			orderedPagesList.push_back(pagesList[i]);
			std::cout << "Good pages list at i: " << i << std::endl;
			for(unsigned int j = 0; j < pagesList[i].size(); j++)
				std::cout << pagesList[i][j] << " ";
			std::cout << std::endl << std::endl;
		}
		if(goodPageList && swapped)
		{
			swappedPagesList.push_back(pagesList[i]);
			std::cout << "Swapped pages list at i: " << i << std::endl;
			for(unsigned int j = 0; j < pagesList[i].size(); j++)
				std::cout << pagesList[i][j] << " ";
			std::cout << std::endl << std::endl;
		}
	}

	int totalPageListMiddle = 0;
	int swappedPageListMiddle = 0;
	for(auto& orderedList : orderedPagesList)
	{
		// std::cout << "Ordered Pages: ";
		// for(auto& ordPages : orderedList)
		// 	std::cout << ordPages << " ";
		// std::cout << std::endl;
		auto midPgNum = orderedList.begin() + orderedList.size() / 2;
		totalPageListMiddle += *midPgNum;
	}
	for(auto& swappedList : swappedPagesList)
	{
		auto midSwapNum = swappedList.begin() + swappedList.size() / 2;
		swappedPageListMiddle += *midSwapNum;
	}

	std::cout << "Total of middle value of ordered pages: " << totalPageListMiddle << std::endl;
	std::cout << "Total of middle value of swapped pages: " << swappedPageListMiddle << std::endl;
	return 0;
}
