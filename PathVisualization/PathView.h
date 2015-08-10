#ifndef _PATHVIEW_H_
#define _PATHVIEW_H_

#include "Utility.h"
#include "Path.h"

class PathView
{
public:
	PathView(Path& path, sf::RenderWindow& window);
	void draw();

private:
	Path& _path;
	sf::RenderWindow& _window;
};
#endif