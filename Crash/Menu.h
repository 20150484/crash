#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <map>
#include <vector>

#include "Button.h"

class Menu : public Drawable
{
public:
	Menu();
	~Menu();

	void update(RenderWindow* window, bool& isPaused, bool& isRestart, Vector2f mouse, Event event);
	map <Button::btnType, Button*> buttons;
private:
	RectangleShape background;
	virtual void draw(RenderTarget& target, RenderStates states) const;
};

#endif // !MENU_H