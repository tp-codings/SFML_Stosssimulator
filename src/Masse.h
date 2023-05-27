#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <math.h>
using namespace sf;

class Masse
{
public:
	Masse(float, float, Color, Vector2f);
	virtual ~Masse();

	void update();
	void render(RenderTarget* target);

	const Vector2f& getPos() const;
	const Vector2f& getDir() const;
	const CircleShape getShape() const;
	const float getMass() const;
	const float getVel() const;
	const Vector2f getSplitVel() const;

	void setDir(Vector2f);
	void setPos(Vector2f);
	void setVel(float);
	void setVelX(float);
	void setVelY(float);
	void setMass(float);
	void setColor(Color);

	void stopUpdate();
	void playUpdate();

private:
	float masse;
	float geschw;
	float geschwX;
	float geschwY;
	Vector2f direction;

	CircleShape shape;

	bool updateStop = false;

	void initShape(float, float, Color, Vector2f);
};

