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

const char WALL = '#';

void PrintMap(const std::vector<std::string> & _map);
void CheckWallRow(std::vector<std::string> & _inMap, int & inTempRow, int & inCol, int upDown, int & totalSpaces, bool & oob, char & direction, int & origLine);
void CheckWallCol(std::vector<std::string> & _inMap, int & inRow, int & inTempCol, int leftRight, int & totalSpaces, bool & oob, char & direction, int & origCol);

int main()
{
	//\^|\>|\<|v|#
	//open input file
	std::ifstream day6File;
	day6File.open("sample");

	std::vector<std::string> overheadMap;
	std::string mapLine = "";
	std::vector<char> facingDirection = { '^', '>', 'v', '<' };
	

	//get guard position
	char currentDirection;
	int currentLine = 0;
	int mapLineCount = 0;
	int mapColumnPos = 0;

	if(day6File)
	{
		getline(day6File, mapLine);
		//std::cout << mapLine << std::endl;
		overheadMap.push_back(mapLine);
	}

	//get the map
	while(!day6File.eof())
	{
		getline(day6File, mapLine);
		if(!day6File.eof())
		{
			//y pos
			mapLineCount++;
			//x pos
			for(auto& direction : facingDirection)
				if(mapLine.find(direction) != std::string::npos)
				{
					currentLine = mapLineCount;
					mapColumnPos = mapLine.find(direction);
					std::cout << "Guard found at: " << currentLine << ", " << mapColumnPos << std::endl;
					currentDirection = direction;
				}
			overheadMap.push_back(mapLine);
		}
	}

	//move the guard along
	int tempColumn = mapColumnPos;
	int tempRow = currentLine;
	int totalSpacesMoved = 0;
	bool outOfBounds = false;
	//testing :)
	while(!outOfBounds)
	{
		switch(currentDirection)
		{
			//column will not change
			case '^':
				//temp row and static column
				CheckWallRow(overheadMap, tempRow, mapColumnPos, -1, totalSpacesMoved, outOfBounds, currentDirection, currentLine);
				break;
			//row will not change
			case '>':
				//temp column and static row
				CheckWallCol(overheadMap, currentLine, tempColumn, 1, totalSpacesMoved, outOfBounds, currentDirection, mapColumnPos);
				break;
			//column will not change
			case 'v':
				//temp row and static column
				CheckWallRow(overheadMap, tempRow, mapColumnPos, 1, totalSpacesMoved, outOfBounds, currentDirection, currentLine);
				break;
			//column will not change
			case '<':
				//temp column and static row
				CheckWallCol(overheadMap, currentLine, tempColumn, -1, totalSpacesMoved, outOfBounds, currentDirection, mapColumnPos);
				break;
		}
	}

	std::cout << "Total distinct positions visited: " << totalSpacesMoved << std::endl;

	return 0;
}

void PrintMap(const std::vector<std::string> & _map)
{
	for(auto& line : _map)
					std::cout << line << std::endl;
	std::cout << std::endl;
	return;
}

void CheckWallRow(std::vector<std::string> & _inMap, int & inTempRow, int & inCol, int upDown, int & totalSpaces, bool & oob, char & direction, int & origLine)
{
	while(_inMap[inTempRow][inCol] != '>' || _inMap[inTempRow][inCol] != '<')
	{
		if(_inMap[inTempRow + (1 * upDown)][inCol] != WALL)
		{
			_inMap[inTempRow][inCol] = 'x';
			inTempRow += 1 * upDown;
			if(_inMap[inTempRow][inCol] != 'x')
				totalSpaces++;

			//-1 for up, 1 for down
			if(upDown == -1)
				_inMap[inTempRow][inCol] = '^';
			else if(upDown == 1)
				_inMap[inTempRow][inCol] = 'v';
			if(inTempRow + (1 * upDown) < 0 && upDown == -1)
			{
				totalSpaces++;
				_inMap[0][inCol] = 'x';
				oob = true;
				break;
			}
			else if(inTempRow + (1 * upDown) >= _inMap.size() && upDown == 1)
			{
				totalSpaces++;
				_inMap[_inMap.size() - 1][inCol] = 'x';
				oob = true;
				break;
			}
		}
		else
		{
			origLine = inTempRow;
			if(upDown == -1)
			{
				_inMap[inTempRow][inCol] = '>';
				direction = '>';
				break;
			}
			else if(upDown == 1)
			{
				_inMap[inTempRow][inCol] = '<';
				direction = '<';
				break;
			}
		}
		PrintMap(_inMap);
	}
	PrintMap(_inMap);
	
	return;
}

//-1 for left, 1 for right
void CheckWallCol(std::vector<std::string> & _inMap, int & inRow, int & inTempCol, int leftRight, int & totalSpaces, bool & oob, char & direction, int & origCol)
{
	while(_inMap[inRow][inTempCol] != 'v' || _inMap[inRow][inTempCol] != '^')
	{
		if(_inMap[inRow][inTempCol + (1 * leftRight)] != WALL)
		{
			_inMap[inRow][inTempCol] = 'x';
			inTempCol += 1 * leftRight;
			if(_inMap[inRow][inTempCol] != 'x')
				totalSpaces++;
			if(leftRight == -1)
				_inMap[inRow][inTempCol] = '<';
			else if(leftRight == 1)
				_inMap[inRow][inTempCol] = '>';
			if(inTempCol + (1 * leftRight) >= _inMap[inRow].size() && leftRight == 1)
			{
				totalSpaces++;
				_inMap[inRow][_inMap[inRow].size() - 1] = 'x';
				oob = true;
				break;
			}
			else if(inTempCol + (1 * leftRight) < 0 && leftRight == -1)
			{
				totalSpaces++;
				_inMap[inRow][0] = 'x';
				oob = true;
				break;
			}
		}
		else
		{
			origCol = inTempCol;
			if(leftRight == -1)
			{
				_inMap[inRow][inTempCol] = '^';
				direction = '^';
				break;
			}
			else if(leftRight == 1)
			{
				_inMap[inRow][inTempCol] = 'v';
				direction = 'v';
				break;
			}
			
		}
		PrintMap(_inMap);
	}
	PrintMap(_inMap);

	return;
}