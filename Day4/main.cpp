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

bool MasCheckerUpDown(std::string _mas, int currI, int upDown, int currJ, const std::vector<std::string> & xmasList);
bool XMasCheckerDiagonalUpDown(std::string _mas, int currI, int upDown, int currJ, int leftRight, const std::vector<std::string> & xmasList);
bool MasCheckerDiagonalUpDown(std::string _mas, int currI, int upDown, int currJ, int leftRight, const std::vector<std::string> & xmasList);

int main()
{
	//regex stuff
	std::smatch foundFirstMass;
	std::smatch foundSecondMass;
	std::regex masMatch("(M[A-Z]S)|(M[A-Z]M)|(S[A-Z]M)|(S[A-Z]S)");
	std::string xmas = "";
	//open input file
	std::ifstream day4File;
	std::vector<std::string> xmasList;
	day4File.open("day4Input");

	if(day4File.is_open())
	{
		getline(day4File, xmas);
		xmasList.push_back(xmas);
	}

	std::cout << xmas << std::endl;

	while(!day4File.eof())
	{
		getline(day4File, xmas);
		std::cout << xmas << std::endl;
		if(!day4File.eof())
			xmasList.push_back(xmas);
	}

	int xmasCount = 0;
	int x_masCount = 0;

	//returned from regex
	//used when checking for top and bottom bounds of an x-mas
	int topPos = 0;
	int bottomPos = 0;
	std::string firstMatch = "";
	std::string secondMatch = "";

	for(signed int i = 0; i != xmasList.size(); i++)
	{
		std::cout << "checking XMAS's here: " << xmasList[i] << " " << i << std::endl;
		size_t xmasPos = xmasList[i].find("XMAS", 0);
		size_t samxPos = xmasList[i].find("SAMX", 0);
		//cases 1 and 2: xmas or samx
		while(xmasPos != std::string::npos)
		{
			std::cout << "Found XMAS at: " << xmasList[i].find("XMAS") << std::endl;
			xmasPos = xmasList[i].find("XMAS", xmasPos + 1);
			xmasCount++;
		}
		while(samxPos != std::string::npos)
		{
			std::cout << "Found SAMX at: " << xmasList[i].find("SAMX") << std::endl;
			samxPos = xmasList[i].find("SAMX", samxPos + 1);
			xmasCount++;
		}
		for(signed int j = 0; j < xmasList[i].size(); j++)
		{
			// beginning of xmas
			// dont look for S because it will double finds
			if(xmasList[i][j] == 'X')
			{
				//std::cout << "Found an X at spot: " << j << std::endl;
				// case 3: xmas down
				if(i + 3 < xmasList.size())
				{
					if(MasCheckerUpDown("MAS", i, 1, j, xmasList))
					{
						//std::cout << "Found an xmas going DOWN!" << std::endl;
						xmasCount++;
					}
				}
				// case 4: samx going up
				if(i - 3 >= 0)
				{
					if(MasCheckerUpDown("MAS", i, -1, j, xmasList))
					{
						//std::cout << "Found an xmas going UP!" << std::endl;
						xmasCount++;
					}
				}
				// case 5: xmas diagonally down to the right
				if(i + 3 < xmasList.size() && j + 3 < xmasList[i].size())
				{
					if(XMasCheckerDiagonalUpDown("MAS", i, 1, j, 1, xmasList))
					{
						//std::cout << "Found an xmas going diagonally DOWN to the RIGHT!" << std::endl;
						xmasCount++;
					}
				}
				//case 6: xmas diagonally up to the left
				if(i - 3 >= 0 && j - 3 >= 0)
				{
					if(XMasCheckerDiagonalUpDown("MAS", i, -1, j, -1, xmasList))
					{
						//std::cout << "Found an xmas going diagonally UP to the LEFT!" << std::endl;
						xmasCount++;
					}
				}
				//case 7: xmas diagonally down to the left
				if(i + 3 < xmasList.size() && j - 3 >= 0)
				{
					if(XMasCheckerDiagonalUpDown("MAS", i, 1, j, -1, xmasList))
					{
						//std::cout << "Found an xmas going diagonally DOWN to the LEFT!" << std::endl;
						xmasCount++;
					}
				}
				//case 8: xmas diagonally up to the right
				if(j + 3 < xmasList[i].size() && i - 3 >= 0)
				{
					if(XMasCheckerDiagonalUpDown("MAS", i, -1, j, 1, xmasList))
					{
						//std::cout << "Found an xmas going diagonally UP to the RIGHT!" << std::endl;
						xmasCount++;
					}
				}
			}
			//MAS | SAM checks
			std::string checkMas = xmasList[i];
			std::string nextCheck = "";
			std::string nextCheckMas = "";
			if(i + 2 < xmasList.size())
			{
				nextCheck = xmasList[i + 2];
				while (std::regex_search(checkMas, foundFirstMass, masMatch))
				{
					firstMatch = foundFirstMass.str(0);
					//MS
					if(firstMatch == foundFirstMass.str(1))
					{
						//get the actual position from the string
						topPos = foundFirstMass.position();
						while(std::regex_search(nextCheck, foundSecondMass, masMatch))
						{
							//check 2 lines down

							nextCheck = foundSecondMass.suffix().str();
						}
					}
					//MM
					else if(firstMatch == foundFirstMass.str(2))
					{
						topPos = foundFirstMass.position();
					}
					//SM
					else if(firstMatch == foundFirstMass.str(3))
					{
						topPos = foundFirstMass.position();
					}
					//SS
					else if(firstMatch == foundFirstMass.str(4))
					{
						topPos = foundFirstMass.position();
					}

					checkMas = foundFirstMass.suffix().str();
				}
			}
		}
		
	}
	std::cout << "There are " << xmasCount << " xmas's in the word search" << std::endl;
	std::cout << "There are " << x_masCount << " x-mas's in the word search" << std::endl;

	return 0;
}

//upDown = -1 for up, 1 for down
bool MasCheckerUpDown(std::string _mas, int currI, int upDown, int currJ, const std::vector<std::string> & xmasList)
{
	bool goodXmas = true;
	for(unsigned int k = 1; k < 4; k++)
	{
		// i + (1 * 1) + k or
		// i + (1 * -1) + k
		if(xmasList[(currI  + (k * upDown))][currJ] != _mas[k - 1])
		{
			//std::cout << "Bad up/down xmas" << std::endl;
			goodXmas = false;
			break;
		}
	}
	return goodXmas;
}

// |X    | S    |    S |    X |
// | M   |  A   |   A  |   M  |
// |  A  |   M  |  M   |  A   |
// |   S |    X | X    | S    |

//leftRight = -1 for left, 1 for right
bool XMasCheckerDiagonalUpDown(std::string _mas, int currI, int upDown, int currJ, int leftRight, const std::vector<std::string> & xmasList)
{
	bool goodXmas = true;
	for(unsigned int k = 1; k < 4; k++)
	{
		//std::cout << "Checking: " << xmasList[(currI + (k * upDown))][currJ + (k * leftRight)] << std::endl;
		//std::cout << "Value: " << _mas[k - 1] << std::endl;
		if((xmasList[(currI + (k * upDown))][currJ + (k * leftRight)] != _mas[k - 1]))
		{
			//std::cout << "Bad xmas" << std::endl;
			goodXmas = false;
			break;
		}
	}
	return goodXmas;
}

bool MasCheckerDiagonalUpDown(int currI, int currJ, const std::vector<std::string> & xmasList)
{
	bool goodXmas = true;

	return goodXmas;
}