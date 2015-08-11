#include "PathView.h"


int PathView::pathAlpha = 100;
sf::Color PathView::pathColor = sf::Color::Red;

PathView::PathView(Path& path, sf::RenderWindow& window) :
_path(path),
_window(window)
{
	_va.setPrimitiveType(sf::LinesStrip);
	pathColor.a = pathAlpha;
	//pos -> _va
	_va.clear();
	vector<sf::Vector3f>& points = _path.getPositions();
	for (vector<sf::Vector3f>::iterator it = points.begin(); it != points.end(); it++)
	{
		_va.append(sf::Vertex(sf::Vector2f(it->x, it->z), pathColor));
	}
	//transform
	vector<sf::Vector3f>& marks = _path.getMarkPositions();
	//translate to origin
	_transform.translate(-marks[0].x, - marks[0].z);
	//rotate to origin

}

void PathView::draw() //canvas, draw type
{

	//glLineWidth(5);
	_window.draw(_va, _transform);
}