#include "Ball.h"

Ball::Ball()
{
	initVariables();
	initShape();
}

Ball::Ball(Vector2f center, float radius, Color color)
{
	initVariables();
	m_center = center;
	m_radius = radius;
	COLOR_SHAPE = color;
	m_color = COLOR_SHAPE;
	m_mass = m_radius;
	initShape();
}

Ball::Ball(const Ball& other)
{
	initVariables();
	m_center = other.m_center;
	m_radius = other.m_radius;
	COLOR_SHAPE = other.m_color;
	m_color = COLOR_SHAPE;
}

Ball::~Ball()
{
	m_vertices.clear();
}

Ball& Ball::operator=(const Ball& other)
{
	m_vertices.clear();
	m_vertices = other.m_vertices;
	m_center = other.m_center;
	m_radius = other.m_radius;
	COLOR_SHAPE = other.m_color;
	m_color = COLOR_SHAPE;
	return *this;
}

void Ball::setPosition(float x, float y)
{
	m_center.x = x;
	m_center.y = y;
	initShape();
}

void Ball::setAngle(float angle)
{
	m_angle = angle;
}

void Ball::setAcceleration(Vector2f acceleration)
{
	m_acceleration = acceleration;
}

void Ball::setVelocity(Vector2f velocity)
{
	m_velocity = velocity;
}

void Ball::setColor(Color color)
{
	COLOR_SHAPE = color;
	m_color = COLOR_SHAPE;
}

Vector2f Ball::getPosition()
{
	return m_center;
}

const Vector2f Ball::getVelocity() const
{
	return m_velocity;
}

float Ball::getRadius()
{
	return m_radius;
}

float Ball::getMass()
{
	return m_mass;
}

void Ball::move(Vector2f velocity)
{
	setPosition(m_center.x + velocity.x, m_center.y + velocity.y);
}

void Ball::rotate(float angle)
{
	setAngle(m_angle + angle);
}

void Ball::updateVelocity(float deltaTime)
{
	m_acceleration = -m_velocity * VISCOSITY;
	m_velocity += (m_acceleration * deltaTime);
	setPosition(m_center.x + m_velocity.x * deltaTime, m_center.y + m_velocity.y * deltaTime);
	setAngle(atan2f(m_velocity.y, m_velocity.x) * 180.f / PI);
	if (abs(m_velocity.x) < 0.1f || abs(m_velocity.y) < 0.1f) {
		m_velocity = Vector2f(0.f, 0.f);
	}
}

bool Ball::checkCollisionPoint(const Vector2f& mouse)
{
	float x_mouse = mouse.x;
	float y_mouse = mouse.y;
	if (((x_mouse - m_center.x) * (x_mouse - m_center.x) +
		(y_mouse - m_center.y) * (y_mouse - m_center.y)) <= m_radius * m_radius)
	{
		return true;
	}
	m_color = COLOR_SHAPE;
	return false;
}

void Ball::updateCollisionBorder(const RenderWindow& window)
{
	if ((m_center.x + m_radius) > window.getSize().x) {
		setPosition(window.getSize().x - m_radius, m_center.y);
		m_velocity.x = -m_velocity.x;
	}
	if ((m_center.y + m_radius) < 0.f) {
		setPosition(m_radius, m_center.y);
		m_velocity.x = -m_velocity.x;
	}
	if ((m_center.y + m_radius) > window.getSize().y) {
		setPosition(m_center.x, window.getSize().y - m_radius);
		m_velocity.y = -m_velocity.y;
	}
	if ((m_center.y - m_radius) < 0.f) {
		setPosition(m_center.x, m_radius);
		m_velocity.y = -m_velocity.y;
	}
}

void Ball::update(const RenderWindow& window, float deltaTime)
{
	updateCollisionBorder(window);
	updateVelocity(deltaTime);
}

void Ball::initVariables()
{
	MAX_POINTS = 20;
	VISCOSITY = 1.5f;
	COLOR_SHAPE = Color::Red;
	m_radius = 10.f;
	m_angle = 0.f;
	m_center = Vector2f(100.f, 100.f);
	m_velocity = Vector2f(0.f, 0.f);
	m_acceleration = Vector2f(0.f, 0.f);
	m_vertices.setPrimitiveType(TrianglesFan);
	m_vertices.clear();
	m_vertices.resize(MAX_POINTS);
	m_color = COLOR_SHAPE;
	m_mass = m_radius;
}

void Ball::initShape()
{
	float x = 0.f;
	float y = 0.f;

	for (unsigned long i = 0; i != MAX_POINTS - 1; i++) {
		x = m_center.x + m_radius * cos(((360.f) / (static_cast<float>(MAX_POINTS - 2)) * i + m_angle) * PI / 180.f);
		y = m_center.y + m_radius * sin(((360.f) / (static_cast<float>(MAX_POINTS - 2)) * i + m_angle) * PI / 180.f);
		m_vertices[i] = Vertex(Vector2f(x, y), m_color);
	}
}

void Ball::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vertices);
}
