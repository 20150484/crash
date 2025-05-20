#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>

using namespace std;
using namespace sf;

class Button : public Drawable
{
public:
	Button(string str, Vector2f pos);
	~Button();

	void setPosition(float x, float y);

	bool mouseCheck(Vector2f mouse); //mouse coordinate
	bool pressed; //mouse state
	void updateEvent(Vector2f mouse, Event event);
	void update(Vector2f mouse, Event event);

	enum btnType
	{
		CONTINUE,
		NEW_GAME,
		EXIT
	};

private:
	RectangleShape shape;
	Text text;
	Font font;

	virtual void draw(RenderTarget& target, RenderStates states) const;
};

#endif // !BUTTON_H