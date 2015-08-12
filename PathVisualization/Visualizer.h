#ifndef _VISUALIZER_H_
#define _VISUALIZER_H_

#include "PathView.h"

class Visualizer
{
public:
	Visualizer(string logDir, sf::RenderWindow& window);
	void draw();
	void processEvent(sf::Event evt);

private:
	void initPathsFromDir(string dir);

	sf::RenderWindow& _window;
	vector<string> _logFiles;
	vector<Path> _paths;
	vector<PathView> _pathViews;

	int _currentIndex;
};

#endif