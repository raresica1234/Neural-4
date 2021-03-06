#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

using namespace sf;

class Game {
private:
	RenderWindow window;

	float width = 800;
	float height = 800;

	float pieceWidth, pieceHeight;
	float borderWidth, borderHeight;

	int connectWidth = 7;
	int connectHeight = 6;

	char connectGrid[7 * 6];

	bool player1 = true;

	bool gameFinished = false;

public:
	Game();

	void Render();
	bool Move(int x);

	void Start();
	
	void DrawRect(float x, float y, float width, float height, Color color);

	void DrawGrid();

	void CheckGame();
};