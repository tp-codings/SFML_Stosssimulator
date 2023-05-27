#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
using namespace sf;

class bomb
{
public:
	bomb();
	virtual ~bomb();

	void update();
	void render(RenderTarget* target);

	const Vector2f& getPos() const;

	void explode();
	void respawn();
private:
	CircleShape shape;

	void initShape();

};

