//VisManager: https://bitbucket.org/fmamimi/hapticchairio-vrsimulation/src/5df4ffe426d44f859d0bf93c6544a9493737704b/Assets/MyCode/Path/VisualizationManager.cs?at=master
//Line Shape: https://github.com/SFML/SFML/wiki/Source:-Drawable-Line-Shape
#ifndef _UTILITY_H_
#define _UTILITY_H_

#define WINDOW

//defines
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define ENTRY_SIZE 7

//include
#include<SFML\Graphics.hpp>
#include<SFML\Graphics\Shape.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\System\Clock.hpp>
#include<TGUI\TGUI.hpp>
#include<iostream>
#include<string>
#include<vector>
#include"Line.h"
//#include"LineShape.h"
#include "vec.h"

using namespace std;



class Utility
{
public:
	inline static vector<string> split(string str, std::string pattern)
	{
		std::string::size_type pos;
		std::vector<std::string> result;
		str += pattern; //add a pattern at the end
		int size = str.size();

		for (int i = 0; i < size; i++)
		{
			pos = str.find(pattern, i);
			if (pos < size)
			{
				std::string s = str.substr(i, pos - i);
				if (s != "")
				{
					result.push_back(s);
				}
				i = pos + pattern.size() - 1;
			}
		}
		return result;
	}

};

class Debug
{
public:
	static void Error(string msg);
};



#endif