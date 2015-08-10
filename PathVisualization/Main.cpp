#include"Utility.h"
#include "Path.h"

#ifdef WINDOW

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Path Visualization");
	tgui::Gui gui(window);

	//////////////////////////////////Test///////////////////////////////////
	Path path;
	path.readDataFromFile("Res/RawData/First Study/Desktop Subject0 Condition4 7 Trial1 5 2015_4_20 17_8_54.txt");

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