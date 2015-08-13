#include "Path.h"


void Path::reset()
{
		_side = -1;
		
		_markPositions.clear();
		_positions.clear();
		_rotations.clear();
		_markPositions2D.clear();
		_positions2D.clear();
		_rotationsY.clear();

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
void Path::readDataFromFile(string filePath)
{
	reset();

	//open file
	fstream infs;
	infs.open(filePath, ios::in);

	if (infs.fail())
	{
		Debug::Error("Cannot open file " + filePath);
	}

	//store fileName
	vector<string> pathSplit = Utility::split(filePath, "/");
	pathSplit = Utility::split(pathSplit[pathSplit.size() - 1], ".");
	_fileName = pathSplit[0];

	//read title
	parseTitle(_fileName);

	//process file log
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
				_markPositions2D.push_back(sf::Vector2f(pos.x, pos.z));
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

void Path::parseTitle(string fileName)
{
	//Example: [0]data\log\Oculus [1]Subject0 [2]Condition1 [3]1 [4]Trial1 [5]0 [6]2015_4_16 [7]11_3_34
	vector<string> fileStrs = Utility::split(fileName, " ");
	//subject: can be one or two digits
	fileStrs[1] = fileStrs[1].erase(0,7); //Remove "Subject"
	_subjectIndex = atoi(fileStrs[1].c_str());

	//condition
	_conditionSequence = atoi(string(1, fileStrs[2][9]).c_str());
	_conditionIndex = atoi(string(1, fileStrs[3][0]).c_str());
	//trial
	_trialSequence = atoi(string(1, fileStrs[4][5]).c_str());
	_trialIndex = atoi(string(1, fileStrs[5][0]).c_str());
	////date
	_date = fileStrs[6];
	////time
	_time = fileStrs[7];

}

int Path::getConditionIndex()
{
	return _conditionIndex;
}

int Path::getTrialIndex()
{
	return _trialIndex;
}

vector<sf::Vector3f>& Path::getPositions()
{
	return _positions;
}

vector<sf::Vector2f>& Path::getPositions2D()
{
	return _positions2D;
}

vector<float>& Path::getRotationsY()
{
	return _rotationsY;
}

vector<sf::Vector3f>& Path::getMarkPositions()
{
	return _markPositions;
}

vector<float>& Path::getSpeeds()
{
	return _speeds;
}

vector<sf::Vector2f>& Path::getMarkPositions2D()
{
	return _markPositions2D;
}

int Path::nodeCount()
{
	return _positions.size();
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
		_positions2D.push_back(sf::Vector2f(point.x, point.z));
		_rotations.push_back(rot);
		_rotationsY.push_back(rot.y);
		if (_positions.size() < 2)
		{
			_speeds.push_back(0);
		}
		else
		{
			vec2 v1(point.x, point.z);
			vec2 v2(_positions2D[_positions.size() - 2].x, _positions2D[_positions.size() - 2].y);
			_speeds.push_back(vec::length(v1 - v2));
		}

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