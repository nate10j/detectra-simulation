#include <SFML/Graphics.hpp>
#include <vector>

class Component {
public:
	virtual void render(sf::RenderTarget& target) = 0;
};

struct Point {
public:
	sf::Vector2f position;
};

class Road : public Component {
public:
	Point point1;
	Point point2;

	void render(sf::RenderTarget& target) override;
};

class Cross : public Component {
public:
	void render(sf::RenderTarget& target) override;
};

// simulations are like the scenes
class Simulation {
public:
	void add(Component* component);
	void render(sf::RenderTarget& target);
private:
	std::vector<Component*> components;
};
