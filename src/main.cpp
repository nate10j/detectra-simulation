#include <SFML/Graphics.hpp>
#include "simulation.h"

int main()
{
	Simulation simulation;

	Road road;
	road.point1.position = sf::Vector2f(0, 300);
	road.point2.position = sf::Vector2f(400, 300);
	simulation.add(&road);

	sf::RenderWindow window(sf::VideoMode({800, 600}), "Simulation");
	window.setFramerateLimit(30);

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		while (const std::optional event = window.pollEvent())
		{
			// "close requested" event: we close the window
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		simulation.render(window);

		// end the current frame
		window.display();
	}
}
