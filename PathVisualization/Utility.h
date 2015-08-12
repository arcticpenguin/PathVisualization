//VisManager: https://bitbucket.org/fmamimi/hapticchairio-vrsimulation/src/5df4ffe426d44f859d0bf93c6544a9493737704b/Assets/MyCode/Path/VisualizationManager.cs?at=master
//Line Shape: https://github.com/SFML/SFML/wiki/Source:-Drawable-Line-Shape
#ifndef _UTILITY_H_
#define _UTILITY_H_

#define WINDOW

//defines
#define PI 3.141592653589793
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define ENTRY_SIZE 7

//include
#include<SFML\Graphics.hpp>
#include<SFML\System.hpp>
#include<SFML\Graphics\Shape.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\System\Clock.hpp>
#include<TGUI\TGUI.hpp>
#include<iostream>
#include<string>
#include<vector>
#include"Line.h"
//#include"LineShape.h"
#include"DrawableLineShape.h"
#include "vec.h"
#include <sys/types.h>
//#include <dirent.h>
#include "tinydir.h"
#include <windows.h>
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

	inline static vector<string> getAllFileNamesWithinFolder(string folder)
	{
		vector<string> names;

		tinydir_dir dir;
		tinydir_open(&dir, folder.c_str());
		int i = 0;
		while (dir.has_next)
		{
			i++;
			tinydir_file file;
			if (!tinydir_readfile(&dir, &file) && i > 2) //why? "." ".."
			{
				string str(file.name);
				names.push_back(str);
			}
			
			//for directories
			//printf("%s", file.name);
			/*if (file.is_dir)
			{
				printf("/");
			}
			printf("\n");*/

			tinydir_next(&dir);
			
		}

		tinydir_close(&dir);

		return names;
	}

};

class Debug
{
public:
	static void Error(string msg);
	static void Log(string msg);
};



#endif