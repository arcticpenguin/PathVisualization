#ifndef _PATH_H_
#define _PATH_H_

#include "Utility.h"

class TimeStamp {
public:
	int enter[3];
	int exit[3];
};

class Path
{
public:
	Path(){}
	void readDataFromFile(string filePath);
	void reset();
	//original
	vector<sf::Vector3f>& getPositions();
	vector<sf::Vector3f>& getMarkPositions();
	vector<float>& getSpeeds();
	//2D
	vector<sf::Vector2f>& getMarkPositions2D();
	vector<sf::Vector2f>& getPositions2D();
	vector<float>& getRotationsY();
	int getConditionIndex();
	int getTrialIndex();
	int nodeCount();

private:
	void parsePathEntry(vector<string> strEntry, int index);
	void parseTitle(string fileName);
	
	//basic info
	string _fileName;
	int _subjectIndex;
	int _conditionSequence;
	int _conditionIndex;
	int _trialSequence;
	int _trialIndex;
	string _date;
	string _time;

	//data
	//original
	vector<sf::Vector3f> _markPositions;
	vector<sf::Vector3f> _positions;
	vector<sf::Vector3f> _rotations;
	vector<float> _speeds;
	//2d
	vector<sf::Vector2f> _markPositions2D;
	vector<sf::Vector2f> _positions2D;
	vector<float> _rotationsY;
	//support
	vector<vector<string>> _pathStrData;
	int _side;
	TimeStamp _timeStamp;
	sf::Vector3f _realStop;
	

	//calculation variables
	float _traveledDist[3];
};

#endif