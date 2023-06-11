#include "..\include\window.hpp"

App::App() {
	window.create(sf::VideoMode(800, 600), "Dijsktra algorithm", sf::Style::Close);
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 34; j++) {
			grid.push_back(new sf::RectangleShape(sf::Vector2f(25, 25)));
		}
	}
	createGrid();
};


void App::createGrid() {
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 24; j++) {
			grid.at(i * 25 + j)->setPosition(sf::Vector2f(i * 25, j * 25));
			grid.at(i * 25 + j)->setOutlineColor(sf::Color::Black);
			grid.at(i * 25 + j)->setOutlineThickness(1);
		};
	}
};

void App::displayGrid(sf::RenderWindow& window) {
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 24; j++) {
			window.draw(sf::RectangleShape(*grid.at(i * 25 + j)));
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

		displayGrid(window);
		window.display();
	}
};

App::~App() {
};
