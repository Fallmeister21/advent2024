#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>

std::vector<int> ParseReport(std::string _report);

int main()
{
	std::string report = "";
	//open input file
	std::ifstream day2File;
	std::vector<std::vector<int>> reportList;
	day2File.open("day2Input");

	if(day2File.is_open())
	{
		getline(day2File, report);
		reportList.push_back(ParseReport(report));
	}
	while(!day2File.eof())
	{
		getline(day2File, report);
		//get report input + push
		//convert to levels
		if(!day2File.eof())
		{
			reportList.push_back(ParseReport(report));
		}
	}
	day2File.close();

	//for all the reports
	int safeReports = 0;
	bool safeReport = true;
	for(unsigned int i = 0; i < reportList.size(); i++)
	{
		long base = 0;
		long adjacent = 0;
		//size of given report
		int reportLength = reportList[i].size();
		//check for each level
		for(unsigned int j = 0; j < reportLength; j++)
		{
			safeReport = true;
			std::cout << "=======================================" << std::endl;
			std::vector<int> dampenedReport(reportList[i].begin(), reportList[i].end());
			dampenedReport.erase(dampenedReport.begin() + j);
			if(std::is_sorted(dampenedReport.begin(), dampenedReport.end()) || std::is_sorted(dampenedReport.rbegin(), dampenedReport.rend()))
			{
				//check for good levels
				for(auto level = dampenedReport.begin(); level != dampenedReport.end(); level++)
				{
				
					int difference = 0;
					base = *level;
					if(level != dampenedReport.end() && (level + 1) != dampenedReport.end())
					{
						adjacent = *(level + 1);
						difference = std::abs(base - adjacent);
						std::cout << "Base: " << base << std::endl;
						std::cout << "Adjacent: " << adjacent << std::endl;
						std::cout << "Difference: " << difference << std::endl << std::endl;
					
						if((difference > 0 && difference <= 3) && difference != 0)
						{
							//safeReport = true;
							//do nothing :)
						}
						else
						{
							safeReport = false;
							break;
						}
					}
				}
			}
			else
				continue;

			if(safeReport)
			{
				std::cout << "Safe Report at: " << i << std::endl;
				safeReports++;
				break;
			}
		}
		
		
		std::cout << "----------------------------------------" << std::endl;
	}

	std::cout << "Safe Reports: " << safeReports << std::endl;

	return 0;
}

std::vector<int> ParseReport(std::string _report)
{
	std::vector<int> reportLevels;
	int level = 0;
	std::string subReport = "";

	//std::cout << "Report: " << _report << std::endl;
	for(std::string::iterator reportChar=_report.begin(); reportChar!=_report.end(); reportChar++)
	{
		if(reportChar != _report.end() && reportChar + 1 == _report.end())
			subReport += *reportChar;
		if((reportChar != _report.end() && reportChar + 1 == _report.end()) || *reportChar == ' ')
		{
			subReport.erase(std::find(subReport.begin(), subReport.end(), '\0'), subReport.end());
			level = std::stoi(subReport);
			subReport = "";
			//std::cout << "Level: " << level << std::endl;
			reportLevels.push_back(level);
		}
		else
			subReport += *reportChar;
	}
	return reportLevels;
}