#include "Game.h"

Game::Game()
{
	initWindow();
	initGame();
}

Game::~Game()
{
	blackBalls.clear();
	whiteBalls.clear();
	delete board;
	delete gui;
	delete window;
}

const bool Game::running() const
{
	return window->isOpen();
}

void Game::pollEvents()
{
	if (!order) {
		while (window->pollEvent(sfmlEvent))
		{
			switch (sfmlEvent.type)
			{
			case Event::Closed:
				window->close();
				break;
			case Event::KeyPressed:
				if (sfmlEvent.key.code == Keyboard::Escape)
				{
					gui->gamePaused = 1 - gui->gamePaused;
					std::cout << 1 - gui->gamePaused;
				}
			case Event::MouseButtonPressed:
				if (sfmlEvent.mouseButton.button == Mouse::Right)
				{
					for (auto blackBall : blackBalls)
					{
						if (blackBall->checkCollisionPoint(m_mouse))
						{
							draggedBall = blackBall;
							dragged = true;
						}
					}
				}
				break;
			case Event::MouseButtonReleased:
				if (sfmlEvent.mouseButton.button == Mouse::Right && dragged)
				{
					draggedBall->setVelocity(Vector2f((draggedBall->getPosition().x - m_mouse.x),
						(draggedBall->getPosition().y - m_mouse.y)));
					dragged = false;
					move = true;
					order = true;
					playSFX(CUE, draggedBall);
				}
				break;

			case Event::MouseMoved:
				m_mouse.x = sfmlEvent.mouseMove.x;
				m_mouse.y = sfmlEvent.mouseMove.y;
			}
		}
	}

	if(order) {
		while (window->pollEvent(sfmlEvent))
		{
			switch (sfmlEvent.type)
			{
			case Event::Closed:
				window->close();
				break;
			case Event::KeyPressed:
				if (sfmlEvent.key.code == Keyboard::Escape)
				{
					gui->gamePaused = 1 - gui->gamePaused;
				}
			case Event::MouseButtonPressed:
				if (sfmlEvent.mouseButton.button == Mouse::Right)
				{
					for (auto whiteBall : whiteBalls)
					{
						if (whiteBall->checkCollisionPoint(m_mouse))
						{
							draggedBall = whiteBall;
							dragged = true;
						}
					}
				}
				break;
			case Event::MouseButtonReleased:
				if (sfmlEvent.mouseButton.button == Mouse::Right && dragged)
				{
					draggedBall->setVelocity(Vector2f((draggedBall->getPosition().x - m_mouse.x),
						(draggedBall->getPosition().y - m_mouse.y)));
					dragged = false;
					move = true;
					order = false;
					playSFX(CUE, draggedBall);
				}
				break;

			case Event::MouseMoved:
				m_mouse.x = sfmlEvent.mouseMove.x;
				m_mouse.y = sfmlEvent.mouseMove.y;
			}
		}
	}
}

void Game::collisionCircleLine(Ball* circle, Line* line)
{
	Vector2f p = Vector2f(circle->getPosition());		//center of circle
	Vector2f s = line->getPoints()[0].position;			//strat of line
	Vector2f e = line->getPoints()[1].position;			//end of line
	Vector2f ps = p - s;
	Vector2f se = e - s;
	float lengthLine = (e.x - s.x) * (e.x - s.x) + (e.y - s.y) * (e.y - s.y);
	float t = ((ps.x * se.x) + (ps.y * se.y)) / lengthLine; //point of normal on line
	Vector2f st;
	st.x = s.x + t * se.x;
	st.y = s.y + t * se.y;

	Vector2f distance = p - st;
	float distanceBetween = sqrtf((distance.x * distance.x) + (distance.y * distance.y));

	Vector2f normal = distance / distanceBetween;
	float dotProductNormal = circle->getVelocity().x * normal.x +
		circle->getVelocity().y * normal.y;

	Vector2f tangential = Vector2f(-normal.y, normal.x);
	float dotProductTangential = circle->getVelocity().x * tangential.x +
		circle->getVelocity().y * tangential.y;

	float overlap = distanceBetween - circle->getRadius();
	if (distanceBetween <= circle->getRadius())
	{
		if (t > -0.f && t < 1.f)
		{
			circle->setPosition(p.x - distance.x * overlap / distanceBetween,
				p.y - distance.y * overlap / distanceBetween);
			circle->setVelocity(Vector2f(-normal.x * dotProductNormal + tangential.x * dotProductTangential,
				-normal.y * dotProductNormal + tangential.y * dotProductTangential));

			playSFX(CIRCLEBOARD, circle);
		}
	}
}

void Game::collisionCircles(Ball* ball1, Ball* ball2)
{
	Vector2f distance = ball1->getPosition() - ball2->getPosition();
	float distanceBetween = (sqrtf((distance.x * distance.x) + (distance.y * distance.y)));
	if (ball1 != ball2)
	{
		if (distanceBetween < (ball1->getRadius() + ball2->getRadius()))
		{

			float overlap = (distanceBetween - ball1->getRadius() - ball2->getRadius()) / 2.f;
			float moveX = (overlap * (ball1->getPosition().x - ball2->getPosition().x) / distanceBetween);
			float moveY = (overlap * (ball1->getPosition().y - ball2->getPosition().y) / distanceBetween);
			ball1->setPosition(ball1->getPosition().x - moveX, ball1->getPosition().y - moveY);
			ball2->setPosition(ball2->getPosition().x + moveX, ball2->getPosition().y + moveY);

			Vector2f normal;
			normal.x = distance.x / distanceBetween;
			normal.y = distance.y / distanceBetween;

			Vector2f tangential;
			tangential.x = -normal.y;
			tangential.y = normal.x;

			float dotProductTangential1 = ball1->getVelocity().x * tangential.x +
				ball1->getVelocity().y * tangential.y;
			float dotProductTangential2 = ball2->getVelocity().x * tangential.x +
				ball2->getVelocity().y * tangential.y;

			float dotProductNormal1 = ball1->getVelocity().x * normal.x + ball1->getVelocity().y * normal.y;
			float dotProductNormal2 = ball2->getVelocity().x * normal.x + ball2->getVelocity().y * normal.y;

			float m1 = (2.f * ball2->getMass() * dotProductNormal2 +
				dotProductNormal1 * (ball1->getMass() - ball2->getMass())) /
				(ball1->getMass() + ball2->getMass());
			
			float m2 = (2.f * ball1->getMass() * dotProductNormal1 +
				dotProductNormal2 * (ball2->getMass() - ball1->getMass())) /
				(ball1->getMass() + ball2->getMass());
			ball1->setVelocity(dotProductTangential1 * tangential + m1 * normal);
			ball2->setVelocity(dotProductTangential2 * tangential + m2 * normal);

			playSFX(CIRCLES, ball1);
		}
	}
}

void Game::BlackCollisionCircleCliff(Ball* circle, Line* cliff, int num)
{
	Vector2f s = cliff->getPoints()[0].position;
	Vector2f e = cliff->getPoints()[1].position;
	Vector2f p = circle->getPosition();
	Vector2f se = e - s;
	Vector2f ps = p - s;

	float lengthLine = (e.x - s.x) * (e.x - s.x) + (e.y - s.y) * (e.y - s.y);
	float t = ((ps.x * se.x) + (ps.y * se.y)) / lengthLine;

	Vector2f st;
	st.x = s.x + t * se.x;
	st.y = s.y + t * se.y;

	Vector2f distance = p - st;
	float distanceBetween = sqrtf(distance.x * distance.x + distance.y * distance.y);

	if (distanceBetween <= circle->getRadius() && (t > -0.f && t < 1.f))
	{

		playSFX(CIRCLEHOAL, circle);

		drop = true;
		blackBalls.erase(blackBalls.begin() + num); 
	}
}

void Game::WhiteCollisionCircleCliff(Ball* circle, Line* cliff, int num)
{
	Vector2f s = cliff->getPoints()[0].position;
	Vector2f e = cliff->getPoints()[1].position;
	Vector2f p = circle->getPosition();
	Vector2f se = e - s;
	Vector2f ps = p - s;

	float lengthLine = (e.x - s.x) * (e.x - s.x) + (e.y - s.y) * (e.y - s.y);
	float t = ((ps.x * se.x) + (ps.y * se.y)) / lengthLine;

	Vector2f st;
	st.x = s.x + t * se.x;
	st.y = s.y + t * se.y;

	Vector2f distance = p - st;
	float distanceBetween = sqrtf(distance.x * distance.x + distance.y * distance.y);

	if (distanceBetween <= circle->getRadius() && (t > -0.f && t < 1.f))
	{

		playSFX(CIRCLEHOAL, circle);

		drop = true;
		whiteBalls.erase(whiteBalls.begin() + num);
	}
}

void Game::playSFX(const int sfxType, const Ball* obj)
{
	Vector2f vol = obj->getVelocity();
	float volume = sqrtf(vol.x * vol.x + vol.y * vol.y) / 5.f;
	sound[sfxType].setVolume(volume);
	sound[sfxType].play();
}

void Game::updateDirectionLine()
{
	if (dragged)
	{
		Vector2f distance = (m_mouse - draggedBall->getPosition());
		float distanceBetween = sqrt(distance.x * distance.x + distance.y * distance.y);
		Vector2f invert = distance / distanceBetween;
		Color directionColor = Color(255, (255 - ((int)distanceBetween / 2) % 255), 0);
		if (distanceBetween > 510) { directionColor = Color::Red; }
		direction = new Line(draggedBall->getPosition().x, draggedBall->getPosition().y,
			draggedBall->getPosition().x - distanceBetween * invert.x,
			draggedBall->getPosition().y - distanceBetween * invert.y, directionColor);
	}
}

void Game::restart()
{
	gui->restart();
	blackBalls.clear();
	whiteBalls.clear();
	for (int i = 1; i < 6; i++) {
		Ball* newBall = new Ball(Vector2f((i * 100) + 500, 250), ballRadius, Color::White);
		whiteBalls.push_back(newBall);
	}
	for (int i = 1; i < 6; i++) {
		Ball* newBall = new Ball(Vector2f((i * 100) + 500, 650), ballRadius, Color::Black);
		blackBalls.push_back(newBall);
	}

	dragged = false;
	move = false;
	drop = false;
	restartGame = false;
	order = false;
}

void Game::updateAllCollisions()
{
	for (int i = 0; i < blackBalls.size(); i++)
	{
		for (Line line : board->getBorderLines())
		{
			collisionCircleLine(blackBalls[i], &line);
		}
		for (auto blackball2 : blackBalls)
		{
			collisionCircles(blackBalls[i], blackball2);
		}
		for (auto blackball3 : whiteBalls)
		{
			collisionCircles(blackBalls[i], blackball3);
		}
		for (auto cliff : board->getCliff())
		{
			BlackCollisionCircleCliff(blackBalls[i], &cliff, i);
			if (drop) { break; }
		}
	}
	for (int i = 0; i < whiteBalls.size(); i++)
	{
		for (Line line : board->getBorderLines())
		{
			collisionCircleLine(whiteBalls[i], &line);
		}
		for (auto whiteBall2 : whiteBalls)
		{
			collisionCircles(whiteBalls[i], whiteBall2);
		}
		for (auto whiteBall3 : blackBalls)
		{
			collisionCircles(whiteBalls[i], whiteBall3);
		}
		for (auto cliff : board->getCliff())
		{
			WhiteCollisionCircleCliff(whiteBalls[i], &cliff, i);
			if (drop) { break; }
		}
	}
}

void Game::updateGameLogic()
{
	if (drop) {
		drop = false;
	}
	if (move && draggedBall->getVelocity() == Vector2f(0.f, 0.f)) {
		move = false;
		gui->setCurrentPlayer(1 - gui->getCurrentPlayer().number);
	}
}

void Game::update()
{
	float deltaTime = 0.f;
	deltaTime = clock.restart().asSeconds();

	font.loadFromFile("./sfx/FreeSerif.ttf");
	FPS.setFont(font);
	FPS.setString("FPS: " + to_string(1 / deltaTime));
	FPS.setCharacterSize(25);
	FPS.setPosition(50, 30);

	pollEvents();

	updateDirectionLine();
	gui->update(window, gui->gamePaused, restartGame, m_mouse, sfmlEvent);
	updateGameLogic();
	if (!gui->gamePaused)
	{
		for (auto whiteBall : whiteBalls)
		{
			whiteBall->update(*window, deltaTime);
		}
		for (auto blackball : blackBalls)
		{
			blackball->update(*window, deltaTime);
		}
		updateAllCollisions();
	}
	if (restartGame)
	{
		restart();
	}

	if (blackBalls.size() == 0) { result.setString("WhiteWin!"); }
	if (whiteBalls.size() == 0) { result.setString("BlackWin!"); }
}

void Game::render()
{
	window->clear(Color(100, 100, 100));
	//window->clear(sf::Color::Black);
	board->render(window);
	for (auto i : whiteBalls)
	{
		window->draw(*i);
	}
	for (auto i : blackBalls)
	{
		window->draw(*i);
	}

	window->draw(*gui);

	if (blackBalls.size() == 0) {
		window->draw(result);
		gui->gamePaused = true;
	}

	if (whiteBalls.size() == 0) {
		window->draw(result);
		gui->gamePaused = true;
	}

	if (dragged)
	{
		window->draw(*direction);
	}

	window->draw(FPS);

	window->display();
}

void Game::initWindow()
{
	videoMode = VideoMode(1600, 900);
	window = new RenderWindow(videoMode, "Crash", Style::Default);
	window->setFramerateLimit(60);
}

void Game::initGame()
{
	restartGame = false;
	gui = new GUI();
	board = new Board();
	for (int i = 1; i < 6; i++) {
		Ball* newBall = new Ball(Vector2f((i * 100) + 500, 250), ballRadius, Color::White);
		whiteBalls.push_back(newBall);
	}
	for (int i = 1; i < 6; i++) {
		Ball* newBall = new Ball(Vector2f((i * 100) + 500, 650), ballRadius, Color::Black);
		blackBalls.push_back(newBall);
	}
	dragged = false;
	move = false;
	drop = false;
	order = false;

	result.setFont(font);
	result.setPosition(600, 100);
	result.setCharacterSize(100);

	// INIT SOUNDS
	buffer = new SoundBuffer;
	buffer->loadFromFile("./sfx/Circles.wav");
	sound[CIRCLES].setBuffer(*buffer);
	buffer = new SoundBuffer;
	buffer->loadFromFile("./sfx/CircleBoard.wav");
	sound[CIRCLEBOARD].setBuffer(*buffer);
	buffer = new SoundBuffer;
	buffer->loadFromFile("./sfx/Cue.wav");
	sound[CUE].setBuffer(*buffer);
	buffer = new SoundBuffer;
	buffer->loadFromFile("./sfx/CircleHole.wav");
	sound[CIRCLEHOAL].setBuffer(*buffer);
}
