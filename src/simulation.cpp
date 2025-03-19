#include "simulation.h"
#include <iostream>
#include <vector>

void Simulation::add(Component* component) {
	this->components.push_back(component);
}

struct {
	sf::Color Background = sf::Color(60, 177, 21);
	sf::Color Road = sf::Color(48, 48, 48);
} Palette;

void Simulation::render(sf::RenderTarget& target) {
	// clear with background color
	target.clear(Palette.Background);

	for (Component* component : this->components) {
		component->render(target);
	}
}

void Road::render(sf::RenderTarget& target) {
	sf::Vector2f direction = this->point2.position - this->point1.position;
	sf::Vector2f unitDirection = direction/std::sqrt(direction.x*direction.x+direction.y*direction.y);
	sf::Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

	float thickness = 70.f;
	sf::Vector2f offset = (thickness/2.f)*unitPerpendicular;

	std::array vertices =
		{
			sf::Vertex{.position = this->point1.position + offset},
			sf::Vertex{.position = this->point2.position + offset},
			sf::Vertex{.position = this->point1.position - offset},
			sf::Vertex{.position = this->point2.position - offset}
		};

	for (int i=0; i<4; ++i) {
		vertices[i].color = Palette.Road;
	}

	target.draw(vertices.data(), vertices.size(), sf::PrimitiveType::TriangleStrip);

	// dashed lines
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	float currentLength = 0;
	bool drawDash = true;

	while (currentLength < length) {
		if (drawDash) {
			sf::Vector2f dashedOffsetCurrent = (currentLength)*unitDirection;
			sf::Vector2f dashedOffsetNext = (currentLength+20.f)*unitDirection;
			std::array line = {
				sf::Vertex{this->point1.position + dashedOffsetCurrent}, // Change color if needed
				sf::Vertex{this->point1.position + dashedOffsetNext} // Change color if needed
			};
			target.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
			currentLength += 20.f;
		} else {
			currentLength += 20.f;
		}
		drawDash = !drawDash;
		// Toggle between drawing a dash and a gap
	}
}
