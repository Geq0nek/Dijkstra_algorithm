#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class App {
private:
	sf::RenderWindow window;
	sf::Vector2i statringNode;
	sf::Vector2i endingNode;
	std::vector<sf::RectangleShape*> grid;
	std::vector<sf::RectangleShape> path;

public:
	App();
	void createGrid();
	void displayGrid(sf::RenderWindow& window);
	void run();
	~App();
};

