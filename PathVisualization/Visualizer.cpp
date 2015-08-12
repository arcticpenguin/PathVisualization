#include "Visualizer.h"


Visualizer::Visualizer(string logDir, sf::RenderWindow& window) :
_window(window)
{
	//load files from dir
	initPathsFromDir(logDir);
	_currentIndex = 0;
	
}

void Visualizer::initPathsFromDir(string dir)
{
	_logFiles = Utility::getAllFileNamesWithinFolder(dir);
	for (int i = 0; i < _logFiles.size(); i++)
	{
		Path path;
		path.readDataFromFile(dir + _logFiles[i]);
		_paths.push_back(path);
		
		cout<<"[LOG] "<<i+1<<" out of " <<_logFiles.size()<<" loaded."<<endl;
	}
	for (int i = 0; i < _logFiles.size(); i++)
	{
		PathView pv(_paths[i], _window);
		_pathViews.push_back(pv);
	}
	return;
}

void Visualizer::filter(int conditionIndex, int trialIndex)
{
	for (int i = 0; i < _pathViews.size(); i++)
	{
		_pathViews[i].setVisibility(false);
		Path& path = _pathViews[i].getPath();
		if (path.getConditionIndex() == conditionIndex && path.getTrialIndex() == trialIndex)
		{
			_pathViews[i].setVisibility(true);
		}
	}
}

void Visualizer::draw()
{
	for (int i = 0; i < _pathViews.size(); i++)
	{
		if (_pathViews[i].isVisible())
		{
			_pathViews[i].draw();
		}
	}
}

void Visualizer::processEvent(sf::Event evt)
{
	if (evt.type == sf::Event::KeyPressed)
	{
		if (evt.key.code == sf::Keyboard::Right)
		{
			_currentIndex++;
			_currentIndex %= _logFiles.size();
			cout << _currentIndex << endl;
		}
		if (evt.key.code == sf::Keyboard::Left)
		{
			_currentIndex--;
			_currentIndex = (_currentIndex + _logFiles.size()) % _logFiles.size();
			cout << _currentIndex << endl;
		}
	}
}