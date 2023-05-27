#include "Masse.h"
#include <iostream>

Masse::Masse(float mass, float vel, Color color, Vector2f pos)
{
	this->initShape(mass, vel, color, pos);
}

Masse::~Masse()
{
}

void Masse::update()
{
	if (!updateStop)
	{
		this->shape.move(this->geschw * this->direction);
		//this->shape.move(this->geschwY * this->direction);
		//std::cout << geschwX << "\n" << geschwY << "\n\n\n";
	}
	
}

void Masse::render(RenderTarget* target)
{
	target->draw(this->shape);
}

const Vector2f& Masse::getPos() const
{
	return this->shape.getPosition();
}

const Vector2f& Masse::getDir() const
{
	return this->direction;
}

const CircleShape Masse::getShape() const
{
	return this->shape;
}

const float Masse::getMass() const
{
	return this->masse;
}

const float Masse::getVel() const
{
	return this->geschw;
	
}

const Vector2f Masse::getSplitVel() const
{
	return Vector2f(geschwX, geschwY);
}

void Masse::setDir(Vector2f dir)
{
	this->direction = dir;
}

void Masse::setPos(Vector2f pos)
{
	this->shape.setPosition(pos);
}

void Masse::setVel(float vel)
{
	float alpha = atan(
		direction.y /
		direction.x
	);
	this->geschw = vel;
	this->geschwX = vel * cos(alpha);
	this->geschwY = vel * sin(alpha);
}

void Masse::setVelX(float vel)
{
	this->geschwX = vel;
}

void Masse::setVelY(float vel)
{
	this->geschwY = vel;
}

void Masse::setMass(float mass)
{
	this->masse = mass;
}

void Masse::setColor(Color color)
{
	this->shape.setFillColor(color);
}

void Masse::stopUpdate()
{
	this->updateStop = true;
}

void Masse::playUpdate()
{
	this->updateStop = false;
}

void Masse::initShape(float mass, float vel, Color color, Vector2f pos)
{
	this->shape.setPosition(pos.x, pos.y);
	this->shape.setFillColor(color);
	this->shape.setRadius(30.0);
	this->masse = mass;
	this->geschw = vel;
}
