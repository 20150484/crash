#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <cmath>

using namespace std;
using namespace sf;

const double PI = acos(-1); // Circumference

class Ball : public Drawable, Transformable
{
public:
	Ball();
	Ball(Vector2f center, float radius, Color color);
	~Ball();
	Ball(const Ball&);
	Ball& operator=(const Ball&);
	void setPosition(float x, float y);
	void setAngle(float angle);					//angle
	void setAcceleration(Vector2f acceleration);
	void setVelocity(Vector2f velocity);		
	void setColor(Color color);

	Vector2f	getPosition();
	const Vector2f	getVelocity() const;
	float getRadius();
	float getMass();

	void move(Vector2f velocity);
	void rotate(float angle);

	void updateVelocity(float deltaTime);
	bool checkCollisionPoint(const Vector2f& mouse);	//check cursor on the ball
	void updateCollisionBorder(const RenderWindow& window); //ball screen frame impulse

	void update(const RenderWindow& window, float deltaTime);
private:
	unsigned int MAX_POINTS; //Maximum vertices
	float VISCOSITY;		//VISCOSITY
	VertexArray m_vertices;
	Color COLOR_SHAPE;
	Color m_color;
	Vector2f viscosity;
	Vector2f m_center;
	Vector2f m_velocity;
	Vector2f m_acceleration;
	float m_radius;
	float m_angle;
	float m_mass;
	void initVariables();
	void initShape();
	virtual void draw(RenderTarget& target, RenderStates states) const;
};

#endif // !BALL_H