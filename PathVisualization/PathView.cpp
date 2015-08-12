#include "PathView.h"


int PathView::pathAlpha = 100;
sf::Color PathView::pathColor = sf::Color::Red;

PathView::PathView(Path& path, sf::RenderWindow& window) :
_path(path),
_window(window)
{
	//basic settings
	_isVisible = false;

	//path
	_va.setPrimitiveType(sf::LinesStrip);
	pathColor.a = pathAlpha;
	//pos -> _va
	_va.clear();
	vector<sf::Vector3f>& points = _path.getPositions();
	for (vector<sf::Vector3f>::iterator it = points.begin(); it != points.end(); it++)
	{
		_va.append(sf::Vertex(sf::Vector2f(it->x, it->z), pathColor));
	}

	//markViews
	vector<sf::Vector2f>& markPositions = _path.getMarkPositions2D();
	for (int i = 0; i < 3; i++)
	{
		float radius = 5;
		sf::CircleShape mv;
		mv.setRadius(radius);
		mv.setOutlineThickness(2);
		mv.setPosition(markPositions[i].x - radius, markPositions[i].y - radius);
		mv.setFillColor(sf::Color::Transparent);
		markViews.push_back(mv);
	}
	markViews[0].setOutlineColor(sf::Color::Green);
	markViews[1].setOutlineColor(sf::Color::Red);
	markViews[2].setOutlineColor(sf::Color::Blue);

	//transform
	vector<sf::Vector3f>& marks = _path.getMarkPositions();
	
	//4. translate to the right position
	_transform.translate(384, 540);
	//3. scale
	_transform.scale(3.8, 3.8);
	//2. rotate to origin
	calculateAngleToVerticalAxis();
	_transform.rotate(_angleToVerticalAxis, sf::Vector2f(0, 0));
	//1. translate to origin
	_transform.translate(-marks[0].x, -marks[0].z);
}

bool PathView::isVisible()
{
	return _isVisible;
}

void PathView::setVisibility(bool visible)
{
	_isVisible = visible;
}

Path& PathView::getPath()
{
	return _path;
}

float PathView::calculateAngleToVerticalAxis()
{
	vector<sf::Vector2f>& markPositions = _path.getMarkPositions2D();
	sf::Vector2f segmentVec = markPositions[1] - markPositions[0];
	vec2 v2(segmentVec.x, segmentVec.y);
	vec2 v1(0, -1);
	float cosA = vec::dot(v1, v2) / (vec::length(v1) * vec::length(v2));
	//sign
	vec3 v3_1(v1, 0);
	vec3 v3_2(v2, 0);
	int sign = vec::cross(v3_2, v3_1).z >= 0 ? 1 : -1;
	_angleToVerticalAxis = sign * acosf(cosA) * 180 / PI;
	
	//cout << "Angle: " << _angleToVerticalAxis << endl;
	return _angleToVerticalAxis;
}

void PathView::draw() //canvas, draw type
{
	glLineWidth(5);
	_window.draw(_va, _transform);
	for (int i = 0; i < 3; i++)
	{
		_window.draw(markViews[i], _transform);
	}
}