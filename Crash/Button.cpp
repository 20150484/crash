#include "Button.h"

Button::Button(string str, Vector2f pos)
{
	shape.setPosition(pos);
	shape.setSize(Vector2f(200.f, 50.f));
	shape.setFillColor(Color(0, 0, 0, 150));

	font.loadFromFile("./sfx/FreeSerif.ttf");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setString(str);
	text.setPosition(Vector2f(
		shape.getPosition().x + (shape.getLocalBounds().width / 2.f - text.getLocalBounds().width / 2.f),
		shape.getPosition().y + (shape.getLocalBounds().height / 2.f - text.getLocalBounds().height)));
	pressed = false;
}

Button::~Button()
{
}

void Button::setPosition(float x, float y)
{
	shape.setPosition(x, y);
	text.setPosition(shape.getPosition().x + 10.f, shape.getPosition().y + 10.f);
}

bool Button::mouseCheck(Vector2f mouse)
{
	if (shape.getGlobalBounds().left <= mouse.x &&
		mouse.x <= (shape.getGlobalBounds().left + shape.getGlobalBounds().width) &&
		shape.getGlobalBounds().top <= mouse.y &&
		mouse.y <= (shape.getGlobalBounds().top + shape.getGlobalBounds().height)) 
	{
		shape.setFillColor(Color(0, 90, 170, 180));
		return true;
	}
	shape.setFillColor(Color(0, 0, 0, 150));
	return false;
}

void Button::updateEvent(Vector2f mouse, Event event)
{
	if (event.mouseButton.button == Mouse::Left && mouseCheck(mouse)) {
		if (event.type == Event::MouseButtonPressed) {
			shape.setOutlineThickness(-2);
			pressed = true;
		}
		if (event.type == Event::MouseButtonReleased) {
			shape.setOutlineThickness(0);
			pressed = false;
		}
	}
}

void Button::update(Vector2f mouse, Event event)
{
	mouseCheck(mouse);
	updateEvent(mouse, event);
}

void Button::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(shape);
	target.draw(text);
}
