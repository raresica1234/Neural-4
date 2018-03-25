#include "Game.h"

Game::Game()
	: window(VideoMode(800, 800), "Neural 4") {

	pieceWidth = ((float)width - 280) / 7.f;
	pieceHeight = ((float)height - 280) / 6.f;
	borderWidth = 280.f / 8.f;
	borderHeight = 280.f / 7.f;
	memset(connectGrid, 0, 7 * 6);
}


void Game::Render() {
	for (int i = 0; i <= 7; i++)
		DrawRect(i * (borderWidth + pieceWidth), 0, borderWidth, height, Color::Green);

	for (int i = 0; i <= 6; i++)
		DrawRect(0, i * (borderHeight + pieceHeight), width, borderHeight, Color::Green);

	DrawGrid();
}

void Game::DrawRect(float x, float y, float width, float height, Color color) {
	RectangleShape shape;
	shape.setPosition({ x, y });
	shape.setSize({ width, height });
	shape.setFillColor(color);
	window.draw(shape);
}

bool Game::Move(int x) {
	// x remains put, just need to check the bottom y
	for (int y = 0; y <= 6; y++) {
		if (connectGrid[y * 7 + x] == 0) {
			connectGrid[y * 7 + x] = player1 ? 1 : 2;
			player1 ^= true;

			return true;
		}
	}
	return false;
}


void Game::Start() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				int x = event.mouseButton.x;
				int y = event.mouseButton.y;
				for (int i = 0; i <= 7; i++) {
					if (x > (i * (borderWidth + pieceWidth)) && x < (i + 1) * ((borderWidth + pieceWidth) + borderWidth)) {
						Move(i);
					}

				}


			}
		}

		Render();

		window.display();
	}
}

void Game::DrawGrid() {
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 7; x++) {
			char current = connectGrid[y * 7 + x];
			if(current == 2)
				DrawRect(x * (borderWidth + pieceWidth) + borderWidth, (7 - y) * (borderHeight + pieceHeight) + borderHeight, pieceWidth, pieceHeight, Color::Red);
			else if (current == 1)
				DrawRect(x * (borderWidth + pieceWidth) + borderWidth, (7 - y) * (borderHeight + pieceHeight) + borderHeight, pieceWidth, pieceHeight, Color::Blue);
		}
	}
}