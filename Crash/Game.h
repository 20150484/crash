#ifndef GAME_H
#define GAME_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <array>

#include "GUI.h"
#include "Board.h"
#include "Ball.h"
#include "Line.h"

class Game
{
public:
	Game();
	~Game();
	GUI* gui;
	Board* board;
	vector <Ball*> whiteBalls;
	vector <Ball*> blackBalls;
	Ball* draggedBall;
	Line* direction;
	Clock clock;
	const bool running() const;
	bool restartGame;
	bool dragged;
	bool move;
	bool drop;
	bool order;
	Text result;

	void pollEvents();
	void collisionCircleLine(Ball* circle, Line* line);
	void collisionCircles(Ball* ball1, Ball* ball2);
	void BlackCollisionCircleCliff(Ball* circle, Line* cliff, int num);
	void WhiteCollisionCircleCliff(Ball* circle, Line* cliff, int num);
	void playSFX(const int sfxType, const Ball* obj);
	void updateDirectionLine();
	void restart();
	void updateAllCollisions();
	void updateGameLogic();
	void update();
	void render();

	enum sfxType
	{
		CIRCLES,
		CIRCLEBOARD,
		CUE,
		CIRCLEHOAL,

		COUNT
	};
private:
	VideoMode videoMode;
	RenderWindow* window;
	Event sfmlEvent;
	Vector2f m_mouse;
	SoundBuffer* buffer;
	array<Sound, COUNT> sound;
	const float ballRadius = 15.f;
	void initWindow();
	void initGame();

	Font font;
	Text FPS;
};

#endif // ! GAME_H