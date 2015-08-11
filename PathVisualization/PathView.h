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

	sf::Transform _transform;
	//polyline
	sf::VertexArray _va;
	static  sf::Color pathColor;
	static int pathAlpha;
};
#endif