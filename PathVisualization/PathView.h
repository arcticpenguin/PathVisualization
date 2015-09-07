#ifndef _PATHVIEW_H_
#define _PATHVIEW_H_

#include "Utility.h"
#include "Path.h"

class PathView
{
public:
	PathView(Path& path, sf::RenderWindow& window);
	void draw(string mode = "Triangle");
	bool isVisible();
	void setVisibility(bool visible);
	Path& getPath();
	

private:
	float calculateAngleToVerticalAxis();

	bool _isVisible;
	Path& _path;
	sf::RenderWindow& _window;

	sf::Transform _transform;
	
	//polyline
	sf::VertexArray _va;
	static  sf::Color pathColor;
	static int pathAlpha;
	//triangle
	vector<sf::ConvexShape> _orients;

	//enter/exit path
	sf::Vertex _eePath[6];

	//marks
	vector<sf::CircleShape> markViews;
	//for transform
	float _angleToVerticalAxis;
};
#endif