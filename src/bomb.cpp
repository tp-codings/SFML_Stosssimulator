#include "bomb.h"

bomb::bomb()
{
	this->initShape();
}

bomb::~bomb()
{
}

void bomb::update()
{
}

void bomb::render(RenderTarget* target)
{
	target->draw(this->shape);
}

const Vector2f& bomb::getPos() const
{
	return this->shape.getPosition();
}

void bomb::explode()
{
	this->shape.setFillColor(Color::White);
}

void bomb::respawn()
{
}

void bomb::initShape()
{
	this->shape.setPosition(480, 300);
	this->shape.setFillColor(Color::Blue);
	this->shape.setRadius(20.0);
}


 
















