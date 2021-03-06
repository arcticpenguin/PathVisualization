#include "Path.h"


Path::Path(DataOutput& dataOutput):
_dataOutput(dataOutput)
{
}

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
	//calculate
	calculatePath();
	//csv
	outputCalculatedData();
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

int Path::getSubjectIndex()
{
	return _subjectIndex;
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
		_enterExits.push_back(sf::Vector2f(point.x, point.z));
	}
	else if (timeFlag == "enter1")
	{
		_side = -1;
		_timeStamp.enter[1] = index;
		_enterExits.push_back(sf::Vector2f(point.x, point.z));
	}
	else if (timeFlag == "exit1")
	{
		_side = 1;
		_timeStamp.exit[1] = index;
		_enterExits.push_back(sf::Vector2f(point.x, point.z));
	}
	else if (timeFlag == "enter2")
	{
		_side = -1;
		_timeStamp.enter[2] = index;
		_enterExits.push_back(sf::Vector2f(point.x, point.z));
	}
	else if (timeFlag == "exit2")
	{
		_side = 2;
		_timeStamp.exit[2] = index;
		_enterExits.push_back(sf::Vector2f(point.x, point.z));
	}
	else if (timeFlag == "enter0")
	{
		_side = -1;
		_timeStamp.enter[0] = index;
		_enterExits.push_back(sf::Vector2f(point.x, point.z));
	}
}

vector <sf::Vector2f> & Path::getEnterExistPoints()
{
	return _enterExits;
}

void Path::calculatePath()
{
	//Date, Time, 
	//ID, C-Seq., C-No., T-Seq., T-No., Alpha, Dir, 
	//S1, S2, S3, S-All, T1, T2, T3, T-All,	 
	//Closeness, Signed Distance Error, Absolute Distance Error, Signed Relative Distance Error, Absolute Relative Distance Error, 
	//Signed Traveled Error, Absolute Traveled Error, 
	//Signed Angle Error_World, Signed Angle Error_Triangle, Absolute Angle Error, 
	//Trv1, Trv2, Trv3, Trv-All

	/*int _alpha;
	string _dir;
	float _traveledDist[3];*/

	vec3 realStop(_realStop.x, _realStop.z, 0);
	vec3 markPos[3];
	for (int i = 0; i < 3; i++)
	{
		markPos[i] = vec3(_markPositions[i].x, _markPositions[i].z, 0);
	}

	//_sides and _times
	for (int index = 0; index < 3; index++)
	{
		_sides[index] = vec::length(markPos[(index + 1) % 3] - markPos[index]);
		_times[index] = (_timeStamp.enter[(index + 1) % 3] - _timeStamp.exit[index]) * 0.4;
	}
	//_closeness
	_closeness = vec::length(realStop - markPos[0]);
	//_signedDistanceError and _absDistanceError;
	float realDist = vec::length(realStop - markPos[2]);
	float rightDist = _sides[2];
	_signedDistanceError = realDist - rightDist;
	_absDistanceError = abs(_signedDistanceError);
	// _signedRelativeDistError and _absRelativeDistError
	_signedRelativeDistError = _signedDistanceError / rightDist;
	_absRelativeDistError = abs(_signedRelativeDistError);
	// _signedAngleError and _absAngleError
	vec3 v1 = markPos[0] - markPos[2];
	vec3 v2 = realStop - markPos[2];
	_absAngleError = vec::dot(v1, v2) / (vec::length(v1) * vec::length(v2));
	_absAngleError = acos(_absAngleError) * 180 / PI;
	//pay attention to flipped Y axis!!!
	//side->real path: CW+, CCW- in SFML; flipped in real
	int sign = vec::cross(v1, v2).z >= 0 ? 1 : -1;
	_signedAngleError_World = sign * _absAngleError;
	if ((_trialIndex % 2 == 1 && _trialIndex <= 3) || (_trialIndex % 2 == 0 && _trialIndex > 3))
	{
		//CCW in real, CW in SFML
		_signedAngleError_Triangle = -_signedAngleError_World;
	}
	else
	{
		_signedAngleError_Triangle = _signedAngleError_World;
	}

}

void Path::showCalculatedData()
{
	//Date, Time, 
	//ID, C-Seq., C-No., T-Seq., T-No., Alpha, Dir, 
	//S1, S2, S3, S-All, T1, T2, T3, T-All,	 
	//Closeness, Signed Distance Error, Absolute Distance Error, Signed Relative Distance Error, Absolute Relative Distance Error, 
	//Signed Traveled Error, Absolute Traveled Error, 
	//Signed Angle Error, Absolute Angle Error, 
	//Trv1, Trv2, Trv3, Trv-All

	cout << "\n****************Path****************" << endl;
	cout << "ID=" << _subjectIndex << ", C-Seq=" << _conditionSequence << ", C-No=" << _conditionIndex << ", T-Seq=" << _trialSequence << ", T-No=" << _trialIndex << endl << endl;
	cout << "Sides: " << _sides[0] << ", " << _sides[1] << ", " << _sides[2] << ", All=" << (_sides[0] + _sides[1] + _sides[2]) << endl << endl;
	cout << "Times: " << _times[0] << ", " << _times[1] << ", " << _times[2] << ", All=" << (_times[0] + _times[1] + _times[2]) << endl << endl;
	cout << "Closeness=" << _closeness << ", SDE=" << _signedDistanceError << ", AbsDE=" << _absDistanceError << endl << endl;
	cout << "SRDE=" << _signedRelativeDistError << ", AbsRDE=" << _absRelativeDistError << endl << endl;
	cout << "STE=" << _traveledDist[2] - _sides[2] << ", AbsTE=" << abs(_traveledDist[2] - _sides[2]) << endl << endl;
	cout << "SAE_W=" << _signedAngleError_World << ", SAE_T="<<_signedAngleError_Triangle<<", AbsAE=" << _absAngleError << endl << endl;
	cout << "Traveled: " << _traveledDist[0] << ", " << _traveledDist[1] << ", " << _traveledDist[2] << ", All=" << (_traveledDist[0] + _traveledDist[1] + _traveledDist[2]) << endl << endl;
	cout << "************************************"<<endl<<endl;
}

void Path::outputCalculatedData()
{
	ostringstream ss;
	ss << _date << ", " << _time << ","
		<< _subjectIndex << "," << _conditionSequence << "," << _conditionIndex << "," << _trialSequence << "," << _trialIndex << ","
		<< _sides[0] << ", " << _sides[1] << ", " << _sides[2] << "," << (_sides[0] + _sides[1] + _sides[2]) << ","
		<< _times[0] << ", " << _times[1] << ", " << _times[2] << "," << (_times[0] + _times[1] + _times[2]) << ","
		<< _closeness << "," << _signedDistanceError << "," << _absDistanceError << ","
		<< _signedRelativeDistError << "," << _absRelativeDistError << ","
		<< _traveledDist[2] - _sides[2] << "," << abs(_traveledDist[2] - _sides[2]) << ","
		<< _signedAngleError_World << "," << _signedAngleError_Triangle << "," << _absAngleError << ","
		<< _traveledDist[0] << ", " << _traveledDist[1] << ", " << _traveledDist[2] << "," << (_traveledDist[0] + _traveledDist[1] + _traveledDist[2]) << "\n";
	
	_dataOutput.appendOutput(ss.str());
}