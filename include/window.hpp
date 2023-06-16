#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class App {
private:
	sf::RenderWindow window;
	std::vector<sf::RectangleShape*> grid;
	std::vector<sf::Vector3i> path;
	std::vector<sf::RectangleShape*> obstacles;
	sf::Vector2i startingNode;
	sf::Vector2i endingNode;

	const unsigned int FPS = 60;
	static const sf::Time TimePerFrame;

public:
	App();
	void createGrid(sf::Vector2i startingNode, sf::Vector2i endingNode);
	void displayGrid(sf::RenderWindow& window);
	void setStartingNode(sf::Vector2i mousePosition);
	void setEndingNode(sf::Vector2i mousePosition);
	sf::Vector2i convertMousePosToInt(sf::Vector2i mousePosition);
	void drawObstacles(sf::Vector2i mousePosition);
	void App::findPath();
	void drawPath();
	void run();
	~App();
};


