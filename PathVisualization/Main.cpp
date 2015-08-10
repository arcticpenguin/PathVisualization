#include"Utility.h"

#ifdef WINDOW

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Path Visualization");
	tgui::Gui gui(window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// Pass the event to all the widgets (if there would be widgets)
			gui.handleEvent(event);
		}

		window.clear(sf::Color::White);
		// Draw all created widgets
		gui.draw();
		window.display();
	}


	return 0;
}

#endif