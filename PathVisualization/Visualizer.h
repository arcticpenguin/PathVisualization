#ifndef _VISUALIZER_H_
#define _VISUALIZER_H_

#include "PathView.h"
#include "DataOutput.h"

class Visualizer
{
public:
	Visualizer(string logDir, sf::RenderWindow& window, DataOutput& dataOutput);
	void draw();
	void setDrawMode(string mode);
	void processEvent(sf::Event evt);
	int filter(int conditionIndex, int trialIndex, int subjectIndex = SELECT_ALL);

private:
	void initPathsFromDir(string dir);
	DataOutput& _dataOutput;
	sf::RenderWindow& _window;
	vector<string> _logFiles;
	vector<Path> _paths;
	vector<PathView> _pathViews;
	string _drawMode;

	int _currentIndex;
};

#endif