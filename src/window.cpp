#include "..\include\window.hpp"

App::App() {
	window.create(sf::VideoMode(800, 800), "Dijsktra algorithm", sf::Style::Close);
	window.setFramerateLimit(FPS);
	this->grid.reserve(380);

	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			grid.push_back(new sf::RectangleShape(sf::Vector2f(25, 25)));
		}
	}

	startingNode = sf::Vector2i(0, 0);
	endingNode = sf::Vector2i(1, 1);
	createGrid(startingNode, endingNode);
};


void App::createGrid(sf::Vector2i startingNode, sf::Vector2i endingNode) {
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			if (i == startingNode.x && j == startingNode.y) {
				grid.at(i * 32 + j)->setFillColor(sf::Color(0, 255, 0));
			} 
			else if (i == endingNode.x && j == endingNode.y)
			{
				grid.at(i * 32 + j)->setFillColor(sf::Color(255, 0, 0));
			} 
			else
			{
				grid.at(i * 32 + j)->setFillColor(sf::Color(240, 248, 255));
			}

			grid.at(i * 32 + j)->setPosition(sf::Vector2f(i * 25, j * 25));
			grid.at(i * 32 + j)->setOutlineColor(sf::Color::Black);
			grid.at(i * 32 + j)->setOutlineThickness(1);
		};
	}
};

void App::displayGrid(sf::RenderWindow& window) {
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			window.draw(sf::RectangleShape(*grid.at(i * 32 + j)));
		};
	}
};

void App::run() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			setStartingNode(mousePosition);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			setEndingNode(mousePosition);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			drawObstacles(mousePosition);
		}

		displayGrid(window);
		window.display();
	}
};

void App::setStartingNode(sf::Vector2i mousePosition) {
	sf::Vector2i pos = convertMousePosToInt(mousePosition);
	if (pos.x < 32 || pos.y < 32 || pos.x > 0 || pos.y > 0) {
		startingNode = pos;
		createGrid(pos, endingNode);
	}
};


void App::setEndingNode(sf::Vector2i mousePosition) {
	sf::Vector2i pos = convertMousePosToInt(mousePosition);
	if (pos.x < 32 || pos.y < 32 || pos.x > 0 || pos.y > 0) {
		endingNode = pos;
		createGrid(startingNode, pos);
	}
};

sf::Vector2i App::convertMousePosToInt(sf::Vector2i mousePosition) {
	sf::Vector2i intpos;
	intpos.x = (mousePosition.x - (mousePosition.x % 25)) / 25;
	intpos.y = (mousePosition.y - (mousePosition.y % 25)) / 25;
	return intpos;
};

void App::drawObstacles(sf::Vector2i mousePosition) {
	sf::Vector2i pos = convertMousePosToInt(mousePosition);
	if (pos.x < 32 || pos.y < 32 || pos.x > 0 || pos.y > 0) {
		grid.at(pos.x * 32 + pos.y)->setFillColor(sf::Color(105, 105, 105));
		obstacles.push_back(new sf::RectangleShape(sf::Vector2f(25, 25)));
	}
};

void App::findPath() {
	path.emplace_back(startingNode.x, startingNode.y, 0);
};

App::~App() {
};
