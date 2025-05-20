#ifndef LINE_H
#define LINE_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Line : public Drawable, Transformable
{
public:
	Line();
	Line(float x1, float y1, float x2, float y2, Color color = Color::White);
	~Line();

	VertexArray getPoints();
private:
	VertexArray m_points;
	Color m_color;
	virtual void draw(RenderTarget& target, RenderStates states) const;
};

#endif // !LINE_H