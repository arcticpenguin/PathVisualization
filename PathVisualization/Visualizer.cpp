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
		PathView pv(_paths[_paths.size()-1], _window);
		_pathViews.push_back(pv);
		int percent = (i + 1 ) * 100 / _logFiles.size();
		cout<<"[LOG] "<<i<<" out of " <<_logFiles.size()<<" loaded."<<endl;
	}
	return;
}

void Visualizer::draw()
{
	_pathViews[_currentIndex].draw();
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