#include "GUI.h"

GUI::GUI()
{
	font.loadFromFile("./sfx/FreeSerif.ttf");
	player1.number = 0;

	player1.numberText.setFont(font);
	player1.numberText.setString("Player 1");
	player1.numberText.setPosition(200, 100);
	player1.numberText.setCharacterSize(40);

	player2.number = 1;

	player2.numberText.setFont(font);
	player2.numberText.setString("player2");
	player2.numberText.setPosition(1250, 100);
	player2.numberText.setCharacterSize(40);

	currentPlayer = player1;

	gamePaused = false;
}

GUI::~GUI()
{
}

void GUI::setCurrentPlayer(Player player)
{
	currentPlayer = player;
}

void GUI::setCurrentPlayer(int num)
{
	if (num == 0) {
		currentPlayer = player1;
	}
	if (num == 1) {
		currentPlayer = player2;
	}
}

GUI::Player GUI::getCurrentPlayer()
{
	return currentPlayer;
}

void GUI::restart()
{
	gamePaused = false;
	currentPlayer = player1;
}

void GUI::update(RenderWindow* window, bool& isPaused, bool& isRestart, Vector2f mouse, Event event)
{
	player1.numberText.setString("Player 1");
	player2.numberText.setString("Player 2");
	player1.numberText.setOutlineThickness(0.f);
	player2.numberText.setOutlineThickness(0.f);

	if (currentPlayer.number == 0)
	{
		player1.numberText.setOutlineThickness(3.f);
		player1.numberText.setOutlineColor(Color(0, 0, 0, 100));
	}
	if (currentPlayer.number == 1)
	{
		player2.numberText.setOutlineThickness(3.f);
		player2.numberText.setOutlineColor(Color(0, 0, 0, 100));
	}

	menu.update(window, isPaused, isRestart, mouse, event);
}

void GUI::draw(RenderTarget& target, RenderStates states) const
{
	if (gamePaused) {
		target.draw(menu);
	}
	target.draw(player1.numberText);
	target.draw(player2.numberText);
}
