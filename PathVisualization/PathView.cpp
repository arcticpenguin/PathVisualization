#include "PathView.h"

PathView::PathView(Path& path, sf::RenderWindow& window) :
_path(path),
_window(window)
{
}

void PathView::draw() //canvas, draw type
{
	
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(10, 10)),
		sf::Vertex(sf::Vector2f(150, 150))
	};

	sf::Color color = sf::Color::Red;
	color.a = 100;
	Line ln(sf::Vector2f(10, 10), sf::Vector2f(150, 150),color,8);
	ln.draw(_window,sf::RenderStates::Default);

	Line ln2(sf::Vector2f(150, 150), sf::Vector2f(450, 150), color, 8);
	ln2.draw(_window, sf::RenderStates::Default);
	/*sf::VertexArray va(sf::LinesStrip);
	va.append(sf::Vertex(sf::Vector2f(10, 10), sf::Color::Blue));
	va.append(sf::Vertex(sf::Vector2f(150, 150), sf::Color::Blue));*/

	//_window.draw(va);
}