#include "Menu.h"

Menu::Menu()
{
	background.setSize(Vector2f(600.f, 450.f));
	background.setPosition(500.f, 225.f);
	background.setFillColor(Color(0, 0, 0, 100));

	Button* btnContinue = new Button("Continue", Vector2f(700.f, 250.f));
	Button* btnNewGame = new Button("New Game", Vector2f(700.f, 350.f));
	Button* btnExit = new Button("Exit", Vector2f(700.f, 550.f));
	buttons.insert(pair<Button::btnType, Button*>(Button::CONTINUE, btnContinue));
	buttons.insert(pair<Button::btnType, Button*>(Button::NEW_GAME, btnNewGame));
	buttons.insert(pair<Button::btnType, Button*>(Button::EXIT, btnExit));
}

Menu::~Menu()
{
	buttons.clear();
}

void Menu::update(RenderWindow* window, bool& isPaused, bool& isRestart, Vector2f mouse, Event event)
{
	for (auto btn : buttons) {
		if (btn.first == Button::EXIT && btn.second->pressed) {
			window->close();
		}
		if (btn.first == Button::CONTINUE && btn.second->pressed) {
			isPaused = false;
		}
		if (btn.first == Button::NEW_GAME && btn.second->pressed) {
			isRestart = true;
		}
		btn.second->update(mouse, event);
	}
}

void Menu::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(background);
	for (auto btn : buttons) {
		target.draw(*btn.second);
	}
}
