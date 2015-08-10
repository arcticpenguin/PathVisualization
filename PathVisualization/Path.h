#ifndef _PATH_H_
#define _PATH_H_

#include "Utility.h"

class TimeStamp {
public:
	inline TimeStamp()
	{
	}
	int enter[3];
	int exit[3];
};

class Path
{
public:
	Path(){}
	void readDataFromFile(string fileName);
	void reset();

private:
	void parsePathEntry(vector<string> strEntry, int index);


	vector<vec3> _markPositions;
	vector<vec3> _positions;
	vector<vec3> _rotations;

	vector<vector<string>> _pathStrData;
	int _side; //??????
	TimeStamp _timeStamp;
	vec3 _realStop;

	//calculation variables
	float _traveledDist[3];
};

#endif