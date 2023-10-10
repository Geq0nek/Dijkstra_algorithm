#include "..\include\app.hpp"


App::App() {
	window.create(sf::VideoMode(800, 800), "Dijsktra algorithm", sf::Style::Close);
	window.setFramerateLimit(FPS);
	this->grid.reserve(380);
	this->nodeState.reserve(380);

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
				nodeState.push_back(1);
			} 
			else if (i == endingNode.x && j == endingNode.y)
			{
				grid.at(i * 32 + j)->setFillColor(sf::Color(255, 0, 0));
				nodeState.push_back(2);
			} 
			else
			{
				grid.at(i * 32 + j)->setFillColor(sf::Color(240, 248, 255));
				nodeState.push_back(0);
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

void App::processHandler() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed){
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				findPath();
				finalPath();
				drawPath();
			}
		}
	}
};

void App::run() {
	sf::Clock clock;
	const sf::Time timePerFrame = sf::seconds(1.0f / 120.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (window.isOpen()) {
		processHandler();
		timeSinceLastUpdate += clock.restart();
		
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processHandler();

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
		if (grid.at(pos.x * 32 + pos.y)->getFillColor() != sf::Color(255, 0, 0) && grid.at(pos.x * 32 + pos.y)->getFillColor() != sf::Color(0, 255, 0)) {
			if (grid.at(pos.x * 32 + pos.y)->getFillColor() == sf::Color(240, 248, 255)) {
				grid.at(pos.x * 32 + pos.y)->setFillColor(sf::Color(105, 105, 105));
				nodeState.at(pos.x * 32 + pos.y) = 3;
			} else {
				grid.at(pos.x * 32 + pos.y)->setFillColor(sf::Color(240, 248, 255));
			}

		}
	}
};

bool App::isWall(int x, int y) {
	if (x > 32 || y > 32 || y < 0 || x < 0)
		return 1;
	return nodeState.at(x * 32 + y) == 3;
}


void App::checkNode(int x, int y, int z, std::vector<sf::Vector2i>& visitedNodes, std::vector<sf::Vector3i>& adjNodesList) {
	if (x > 32 || y > 32 || y < 0 || x < 0)
	{
		return;
	}
	else if (!isWall(x, y) && !isVisitedNode(x, y, visitedNodes))
	{
		adjNodesList.emplace_back(x, y, z);
		visitedNodes.emplace_back(x, y);
	}
};

bool App::isVisitedNode(int x, int y, std::vector<sf::Vector2i>& coords) {
	for (int i = 0; i < coords.size(); ++i)
	{
		if (coords.at(i).x == x && coords.at(i).y == y)
			return true;
	}
	return false;
};

void App::finalPath() {
	std::vector<sf::Vector3i> temp;
	sf::Vector3i end;
	for (auto step : path)
	{
		if (step.x == endingNode.x && step.y == endingNode.y)
		{
			end = step;
		}
	}
	temp.push_back(end);
	int i = end.z;
	while (i > 0)
	{
		temp.push_back(path.at(i - 1));
		i = path.at(i - 1).z;
	}
	path.erase(path.begin(), path.end());
	for (auto step : temp)
	{
		path.push_back(step);
	}
};

void App::drawPath() {
	int i, j, k = 0;
	std::cout << "path : " << std::endl;
	for (auto step : path)
	{
		if ((step.x != startingNode.x || step.y != startingNode.y) && (step.x != endingNode.x || step.y != endingNode.y))
		{
			i = step.x;
			j = step.y;
			std::cout << i << " " << j << std::endl;
			nodeState.at(i * 32 + j) = 4;
			grid.at(i * 32 + j)->setFillColor(sf::Color::Yellow);
			k++;
		}
	}
	std::cout << "length of path: " << k << std::endl;
};

void App::findPath() {
	path.emplace_back(startingNode.x, startingNode.y, 0);
	std::vector<sf::Vector3i> adjNodesList;
	std::vector<sf::Vector2i> visitedNodes;
	adjNodesList.emplace_back(path.at(0));
	visitedNodes.emplace_back(path.at(0).x, path.at(0).y);

	int c = 500;
	while (c--) {
		int noofnodes = adjNodesList.size();
		for (int i = 0; i < noofnodes; i++) {
			auto step = adjNodesList.at(i);
			checkNode(step.x, step.y - 1, path.size() - noofnodes + 1 + i, visitedNodes, adjNodesList);
			checkNode(step.x + 1, step.y, path.size() - noofnodes + 1 + i, visitedNodes, adjNodesList);
			checkNode(step.x, step.y + 1, path.size() - noofnodes + 1 + i, visitedNodes, adjNodesList);
			checkNode(step.x - 1, step.y, path.size() - noofnodes + 1 + i, visitedNodes, adjNodesList);
			checkNode(step.x + 1, step.y - 1, path.size() - noofnodes + 1 + i, visitedNodes, adjNodesList);
			checkNode(step.x + 1, step.y + 1, path.size() - noofnodes + 1 + i, visitedNodes, adjNodesList);
			checkNode(step.x - 1, step.y + 1, path.size() - noofnodes + 1 + i, visitedNodes, adjNodesList);
			checkNode(step.x - 1, step.y - 1, path.size() - noofnodes + 1 + i, visitedNodes, adjNodesList);
		}

		adjNodesList.erase(adjNodesList.begin(), adjNodesList.begin() + noofnodes - 1);

		for (auto step : adjNodesList)
		{
			path.push_back(step);
			if (step.x != endingNode.x || step.y != endingNode.y)
				grid.at(step.x * 32 + step.y)->setFillColor(sf::Color::Cyan);
			if (step.x == startingNode.x && step.y == startingNode.y)
			{
				return;
			}
		}
	}
};

App::~App() {
};
