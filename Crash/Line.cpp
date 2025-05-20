#include "Line.h"

Line::Line()
{
}

Line::Line(float x1, float y1, float x2, float y2, Color color)
{
	m_color = color;
	Vertex start = Vertex(Vector2f(x1, y1), m_color);
	Vertex end = Vertex(Vector2f(x2, y2), m_color);
	m_points.setPrimitiveType(LineStrip);
	m_points.append(start);
	m_points.append(end);
}

Line::~Line()
{
	m_points.clear();
}

VertexArray Line::getPoints()
{
	return m_points;
}

void Line::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_points);
}
