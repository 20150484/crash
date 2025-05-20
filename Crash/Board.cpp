#include "Board.h"

Board::Board()
{
	board.loadFromFile("./images/bg.png", sf::IntRect(0, 0, 700.f, 700.f));
	hurdle.loadFromFile("./images/stone.png", sf::IntRect(0, 0, 64, 64));
	water.loadFromFile("./images/water.png", sf::IntRect(0, 0, 127, 127));
	sprite1.setTexture(board);		//gamemap
	//hurdle
	sprite2.setTexture(hurdle);
	sprite3.setTexture(hurdle);
	sprite4.setTexture(hurdle);
	sprite5.setTexture(hurdle);
	sprite6.setTexture(hurdle);
	sprite7.setTexture(hurdle);
	
	sprite8.setTexture(water);
	sprite1.setPosition(450.f, 100.f);
	sprite2.setPosition(450.f, 100.f);
	sprite3.setPosition(1086.f, 100.f);
	sprite4.setPosition(450.f, 736.f);
	sprite5.setPosition(550.f, 350.f);
	sprite6.setPosition(1086.f, 736.f);
	sprite7.setPosition(1000.f, 450.f);
	sprite8.setPosition(736.5f, 386.5f);
	initBorderLines();
	initCliffs();
}

Board::~Board()
{
	lines.clear();
	cliffs.clear();
}

vector<Line> Board::getBorderLines()
{
	return lines;
}

vector<Line> Board::getCliff()
{
	return cliffs;
}

void Board::render(RenderTarget* target)
{
	target->draw(sprite1);
	target->draw(sprite2);
	target->draw(sprite3);
	target->draw(sprite4);
	target->draw(sprite5);
	target->draw(sprite6);
	target->draw(sprite7);
	target->draw(sprite8);
	/*
	//draw board and hole Lines
	for (auto i : cliffs)
	{
		target->draw(i);
	}
	for (auto i : lines)
	{
		target->draw(i);
	}*/
}

void Board::initBorderLines()
{
	//hurdle1
	Line hurdleTop1(450.f, 100.f, 515.f, 100.f);
	lines.push_back(hurdleTop1);
	Line hurdleLeft1(450.f, 100.f, 450.f, 164.f);
	lines.push_back(hurdleLeft1);
	Line hurdleRight1(515.f, 100.f, 515.f, 164.f);
	lines.push_back(hurdleRight1);
	Line hurdleDown1(450.f, 164.f, 515.f, 164.f);
	lines.push_back(hurdleDown1);

	//hurdle2
	Line hurdleTop2(1086.f, 100.f, 1150.f, 100.f);
	lines.push_back(hurdleTop2);
	Line hurdleLeft2(1086.f, 100.f, 1086.f, 164.f);
	lines.push_back(hurdleLeft2);
	Line hurdleRight2(1150.f, 100.f, 1150.f, 164.f);
	lines.push_back(hurdleRight2);
	Line hurdleDown2(1086.f, 164.f, 1150.f, 164.f);
	lines.push_back(hurdleDown2);

	//hurdle3
	Line hurdleTop3(550.f, 350.f, 614.f, 350.f);
	lines.push_back(hurdleTop3);
	Line hurdleLeft3(550.f, 350.f, 550.f, 414.f);
	lines.push_back(hurdleLeft3);
	Line hurdleRight3(614.f, 350.f, 614.f, 414.f);
	lines.push_back(hurdleRight3);
	Line hurdleDown3(550.f, 414.f, 614.f, 414.f);
	lines.push_back(hurdleDown3);

	//hurdle4
	Line hurdleTop4(450.f, 736.f, 514.f, 736.f);
	lines.push_back(hurdleTop4);
	Line hurdleLeft4(450.f, 736.f, 450.f, 800.f);
	lines.push_back(hurdleLeft4);
	Line hurdleRight4(514.f, 736.f, 514.f, 800.f);
	lines.push_back(hurdleRight4);
	Line hurdleDown4(450.f, 800.f, 514.f, 800.f);
	lines.push_back(hurdleDown4);

	//hurdle5
	Line hurdleTop5(1086.f, 736.f, 1150.f, 736.f);
	lines.push_back(hurdleTop5);
	Line hurdleLeft5(1086.f, 736.f, 1086.f, 800.f);
	lines.push_back(hurdleLeft5);
	Line hurdleRight5(1150.f, 736.f, 1150.f, 800.f);
	lines.push_back(hurdleRight5);
	Line hurdleDown5(1086.f, 800.f, 1150.f, 800.f);
	lines.push_back(hurdleDown5);

	//hurdle6
	Line hurdleTop6(1000.f, 450.f, 1064.f, 450.f);
	lines.push_back(hurdleTop6);
	Line hurdleLeft6(1000.f, 450.f, 1000.f, 514.f);
	lines.push_back(hurdleLeft6);
	Line hurdleRight6(1064.f, 450.f, 1064.f, 514.f);
	lines.push_back(hurdleRight6);
	Line hurdleDown6(1000.f, 514.f, 1064.f, 514.f);
	lines.push_back(hurdleDown6);
}

void Board::initCliffs()
{
	//water
	Line waterTop1(751.5f, 401.5f, 848.5f, 401.5f);
	cliffs.push_back(waterTop1);
	Line waterLeft1(751.5f, 401.5f, 751.5f, 498.5f);
	cliffs.push_back(waterLeft1);
	Line waterRight1(848.5f, 401.5f, 848.5f, 498.5f);
	cliffs.push_back(waterRight1);
	Line waterDown1(751.5f, 498.5f, 848.5f, 498.5f);
	cliffs.push_back(waterDown1);

	//cliif
	Line lineTop(435.f, 85.f, 1165.f, 85.f);
	cliffs.push_back(lineTop);
	Line lineLeft(435.f, 85.f, 435.f, 815.f);
	cliffs.push_back(lineLeft);
	Line lineRight(1165.f, 85.f, 1165.f, 815.f);
	cliffs.push_back(lineRight);
	Line lineDown(435.f, 815.f, 1165.f, 815.f);
	cliffs.push_back(lineDown);
}