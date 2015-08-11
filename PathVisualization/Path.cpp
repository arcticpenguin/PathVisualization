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
				sf::Vector3f pos;
				getline(infs, line);
				vector<string> posStr = Utility::split(line, ",");
				pos.x = atof(posStr[0].c_str());
				pos.y = atof(posStr[1].c_str());
				pos.z = atof(posStr[2].c_str());

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
				vector<string> strEntry = Utility::split(line, ",");
				if (strEntry.size() == ENTRY_SIZE)
				{
					parsePathEntry(strEntry, index);
				}
				index++;
			}

			break;

		}
	}

	//close file
	infs.close();
}

vector<sf::Vector3f>& Path::getPositions()
{
	return _positions;
}

vector<sf::Vector3f>& Path::getMarkPositions()
{
	return _markPositions;
}

void Path::parsePathEntry(vector<string> strEntry, int index)
{
	//point
	sf::Vector3f point;
	sf::Vector3f rot;

	//position
		point.x = atof(strEntry[0].c_str());
		point.y = atof(strEntry[1].c_str());
		point.z = atof(strEntry[2].c_str());

	//rotation
		rot.x = atof(strEntry[3].c_str());
		rot.y = atof(strEntry[4].c_str());
		rot.z = atof(strEntry[5].c_str());

	if (_side != -1)
	{
		_positions.push_back(point);
		_rotations.push_back(rot);

		if (_positions.size() > 1)
		{
			sf::Vector3f p1 = _positions[_positions.size() - 2];
			sf::Vector3f p2 = _positions[_positions.size() - 1];
			vec3 v1(p1.x, p1.y, p1.z);
			vec3 v2(p2.x, p2.y, p2.z);
			_traveledDist[_side] += vec::length(v1 - v2);
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