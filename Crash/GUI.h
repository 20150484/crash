#ifndef GUI_H
#define GUI_H

#include "Menu.h"

class GUI : public Drawable
{
public:
	GUI();
	~GUI();

	struct Player
	{
		Text numberText;
		int number;
	};
	void setCurrentPlayer(Player);
	void setCurrentPlayer(int);
	Player getCurrentPlayer();

	bool gamePaused;

	void restart();
	void update(RenderWindow* window, bool& isPaoused, bool& isRestart,Vector2f mouse ,Event event);
private:
	Font font;

	Menu menu;
	Player player1;
	Player player2;
	Player currentPlayer;

	virtual void draw(RenderTarget& target, RenderStates states) const;
};

#endif // !GUI_H