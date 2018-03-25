#include "Game.h"

Game::Game()
	: window(VideoMode(800, 800), "Neural 4") {

	pieceWidth = ((float)width - 280) / 7.f;
	pieceHeight = ((float)height - 280) / 6.f;
	borderWidth = 280.f / 8.f;
	borderHeight = 280.f / 7.f;
	memset(connectGrid, 0, connectWidth * connectHeight);
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
	for (int y = 0; y < connectHeight; y++) {
		if (connectGrid[y * connectWidth + x] == 0) {
			connectGrid[y * connectWidth + x] = player1 ? 1 : 2;
			player1 ^= true;

			return true;
		}
	}
	return false;
}


void Game::Start() {
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (!gameFinished) {
				if (event.type == Event::MouseButtonPressed) {
					int x = event.mouseButton.x;
					for (int i = 0; i < connectWidth; i++) {
						if (x > (i * (borderWidth + pieceWidth)) && x < (i + 1) * ((borderWidth + pieceWidth))) {
							Move(i);
							break;
						}
					}
				}
			}
			else {
				if (event.type == Event::KeyReleased) {
					if (event.key.code == Keyboard::Space) {
						gameFinished = false;
						memset(connectGrid, 0, connectWidth * connectHeight);
					}
				}
			}
		}

		Render();

		if(!gameFinished)
			CheckGame();

		window.display();
	}
}

void Game::DrawGrid() {
	for (int y = 0; y < connectHeight; y++) {
		for (int x = 0; x < connectWidth; x++) {
			char current = connectGrid[y * connectWidth + x];
			if(current == 2)
				DrawRect(x * (borderWidth + pieceWidth) + borderWidth, (5 - y) * (borderHeight + pieceHeight) + borderHeight, pieceWidth, pieceHeight, Color::Red);
			else if (current == 1)									   
				DrawRect(x * (borderWidth + pieceWidth) + borderWidth, (5 - y) * (borderHeight + pieceHeight) + borderHeight, pieceWidth, pieceHeight, Color::Blue);
			else 
				DrawRect(x * (borderWidth + pieceWidth) + borderWidth, (5 - y) * (borderHeight + pieceHeight) + borderHeight, pieceWidth, pieceHeight, Color::Black);

		}
	}
}

void Game::CheckGame() {
	static Vector2i dir[] = {
		{ 1,  0 }, // Up
		{ 1,  1 }, // Diagonal Up-Right
		{ 0,  1 }, // Right
		{ 0, -1 }, // Left
		{ 1, -1 }, // Diagonal Up-Left
	};

	for (int y = 0; y < connectHeight; y++)
		for (int x = 0; x < connectWidth; x++) {
			if (connectGrid[y * connectWidth + x] != 0) {
				// Check all directions for 4 the same
				char currentPlayer = connectGrid[y * connectWidth + x];
				for (int k = 0; k < 5; k++) {
					Vector2i direction = dir[k];

					bool result = true;
					// Test if nigga is in boundries
					if (y + direction.y * 3 < 0 || y + direction.y * 3 > connectHeight || x + direction.x * 3 < 0 || x + direction.x * 3 > connectWidth) {
						//Not in boundries
						continue;
					}

					for (int j = 1; j < 4; j++) {
						if (connectGrid[(y + direction.y * j) * connectWidth + x + direction.x * j] != currentPlayer) {
							result = false;
							break;
						}
					}

					if (result) {
						// Game has finished
						std::cout << "Game finished, Player" << (int)currentPlayer << " won!" << std::endl;
						std::cout << "Direction " << dir[k].x << " " << dir[k].y << " position: " << x << " " << y << std::endl;
						gameFinished = true;
						return;
					}

				}
			}
		}
}