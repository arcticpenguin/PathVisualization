#include "Visualizer.h"


Visualizer::Visualizer(string logDir, sf::RenderWindow& window, DataOutput& dataOutput) :
_window(window), _dataOutput(dataOutput)
{
	//csv
	_dataOutput.appendOutput("Date, Time, ID, C-Seq., C-No., T-Seq., T-No., S1, S2, S3, S-All, T1, T2, T3, T-All,	Closeness, Signed Distance Error, Absolute Distance Error, Signed Relative Distance Error, Absolute Relative Distance Error, Signed Traveled Error, Absolute Traveled Error, SAE_W, SAE_T, Absolute Angle Error, Trv1, Trv2, Trv3, Trv-All\n");

	//load files from dir
	initPathsFromDir(logDir);
	_currentIndex = 0;
	_drawMode = "Triangle";

	
	
}

void Visualizer::setDrawMode(string mode)
{
	_drawMode = mode;
}

void Visualizer::initPathsFromDir(string dir)
{
	_logFiles = Utility::getAllFileNamesWithinFolder(dir);
	for (int i = 0; i < _logFiles.size(); i++)
	{
		Path path(_dataOutput);
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

int Visualizer::filter(int conditionIndex, int trialIndex, int subjectIndex)
{
	int num = 0;
	for (int i = 0; i < _pathViews.size(); i++)
	{
		_pathViews[i].setVisibility(false);
		Path& path = _pathViews[i].getPath();
		if (path.getConditionIndex() == conditionIndex && path.getTrialIndex() == trialIndex)
		{
			if (subjectIndex == SELECT_ALL || subjectIndex == path.getSubjectIndex())
			{
				//draw
				_pathViews[i].setVisibility(true);
				//print: TODO
				path.showCalculatedData();
				num++;
			}
			
		}
	}
	return num;
}

void Visualizer::draw()
{
	for (int i = 0; i < _pathViews.size(); i++)
	{
		if (_pathViews[i].isVisible())
		{
			_pathViews[i].draw(_drawMode);
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