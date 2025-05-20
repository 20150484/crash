#ifndef BOARD_H
#define BOARD_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Line.h"

using namespace std;
using namespace sf;

class Board
{
public:
	Board();
	~Board();

	vector <Line> getBorderLines();
	vector <Line> getCliff();

	void render(RenderTarget* target);
private:
	Sprite sprite1, sprite2, sprite3, sprite4, sprite5, sprite6, sprite7, sprite8;
	Texture board, hurdle, water;

	vector <Line> lines;
	vector <Line> cliffs;
	void initBorderLines();
	void initCliffs();
};

#endif // !BOARD_H
