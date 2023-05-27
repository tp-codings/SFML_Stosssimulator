#pragma once
#include "bomb.h"
#include "Masse.h"

using namespace sf;

class EnginePi
{
public:
	EnginePi();
	virtual ~EnginePi();

	const bool running() const;

	void run();

private:

	//window
	RenderWindow* window;
	VideoMode videomode;
	Event ev;

	//Game objects
	bomb* Bomb = new bomb();
	Masse* m1 = new Masse(50.0, 5.0, Color(170, 190, 197), Vector2f(100, 750));
	Masse* m2 = new Masse(50.0, -5.0, Color(170, 210, 212), Vector2f(700, 750));


	//Game logic
	bool play = false;
	bool ma1 = true;
	bool ma2 = false;
	bool endSim = false;
	int collisions = 0;

	//GUI
	Font font;
	Text text;
	Text resultat;

	//World
	bool collision = false;
	//Resources

	//private Functions:
	void update();
	void updateDirection();
	void updateCollision();
	void updateInput();
	void updateGUI();
	void render();
	void renderGUI(RenderTarget*);
	void initWindow();
	void initGUI();
	void initVariables();
	void initFirstPosition();
	void pollEvent();
};



