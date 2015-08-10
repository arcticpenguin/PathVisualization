#include "Path.h"


void Path::reset()
{
		_side = -1;
		
		_markPositions.clear();
		_positions.clear();
		_rotations.clear();

		for (int index = 0; index < 3; index++)
		{
			_traveledDist[index] = 0;
		}
	
}

/*************************************************
Function:			readDataFromFile
Parameters:		string fileName

Return:				void.
**************************************************/
void Path::readDataFromFile(string fileName)
{
	reset();

	//open file
	fstream infs;
	infs.open(fileName, ios::in);

	if (infs.fail())
	{
		Debug::Error("Cannot open file " + fileName);
	}

	//process file
	while (infs.good())
	{
		string line;
		getline(infs, line);

		if (line == "*Subject")
		{
			//do nothing
		}
		else if (line == "*Layout")
		{
			//int.TryParse(lines[index], out trialIndex);
			//parseLayout();
		}
		else if (line == "*Condition")
		{
			//parseCondition(lines[index]);
			// index++;
		}
		else if (line == "*Marks")
		{
			//read three marks
			for (int i = 0; i < 3; i++)
			{
				vec3 pos;
				getline(infs, line);
				vector<string> posStr = Utility::split(line, ",");
				for (int j = 0; j < 3; j++)
				{
					pos[j] = atof(posStr[j].c_str());
				}
				_markPositions.push_back(pos);
			}

		}
		else if (line == "*Path")
		{
			//read line for titles
			getline(infs, line);
			int index = 0;
			//read path data
			while (infs.good())
			{
				//read one entry
				getline(infs, line);
				parsePathEntry(Utility::split(line, ","), index);
				//_pathStrData.push_back(Utility::split(line,","));
				index++;
			}

			break;

		}
	}

	//close file
	infs.close();
}

void Path::parsePathEntry(vector<string> strEntry, int index)
{
	//point
	vec3 point;
	vec3 rot;

	//position
	for (int i = 0; i < 3; i++)
	{
		point[i] = atof(strEntry[i].c_str());
	}

	//rotation
	for (int i = 3; i < 6; i++)
	{
		rot[i - 3] = atof(strEntry[i].c_str());
	}

	if (_side != -1)
	{
		_positions.push_back(point);
		_rotations.push_back(rot);

		if (_positions.size() > 1)
		{
			_traveledDist[_side] += vec::length(_positions[_positions.size() - 1] - _positions[_positions.size() - 2]);
		}
	}

	//real stop
	if (strEntry[6] == "enter0")
	{
		_realStop = point;
	}

	//time stamp
	string timeFlag = strEntry[6];
	if (timeFlag == "exit0")
	{
		_side = 0;
		_timeStamp.exit[0] = index;
	}
	else if (timeFlag == "enter1")
	{
		_side = -1;
		_timeStamp.enter[1] = index;
	}
	else if (timeFlag == "exit1")
	{
		_side = 1;
		_timeStamp.exit[1] = index;
	}
	else if (timeFlag == "enter2")
	{
		_side = -1;
		_timeStamp.enter[2] = index;
	}
	else if (timeFlag == "exit2")
	{
		_side = 2;
		_timeStamp.exit[2] = index;
	}
	else if (timeFlag == "enter0")
	{
		_side = -1;
		_timeStamp.enter[0] = index;
	}
}