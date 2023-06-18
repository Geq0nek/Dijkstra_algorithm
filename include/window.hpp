#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class App {
private:
	sf::RenderWindow window;
	std::vector<sf::RectangleShape*> grid;
	std::vector<sf::Vector3i> path;
	std::vector<int> nodeState;
	sf::Vector2i startingNode;
	sf::Vector2i endingNode;

	const unsigned int FPS = 60;

public:
	App();
	void createGrid(sf::Vector2i startingNode, sf::Vector2i endingNode);
	void displayGrid(sf::RenderWindow& window);
	void setStartingNode(sf::Vector2i mousePosition);
	void setEndingNode(sf::Vector2i mousePosition);
	sf::Vector2i convertMousePosToInt(sf::Vector2i mousePosition);
	void drawObstacles(sf::Vector2i mousePosition);
	void checkNode(int x, int y, int z, std::vector<sf::Vector2i>& visitedNodes, std::vector<sf::Vector3i>& adjNodesList);
	void findPath();
	void processHandler();
	void run();
	bool isWall(int x, int y);
	void finalPath();
	void drawPath();
	bool isVisitedNode(int x, int y, std::vector<sf::Vector2i>& coords);
	~App();
};


