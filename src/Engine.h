#pragma once
#include "bomb.h"
#include "Masse.h"

using namespace sf;

class Engine
{
public:
	Engine();
	virtual ~Engine();

	const bool running() const;

	void run();

private:

	//window
	RenderWindow* window;
	VideoMode videomode;
	Event ev;

	//Game objects
	bomb *Bomb = new bomb();
	Masse *m1 = new Masse(50.0, 5.0,  Color(170,190,197), Vector2f(100, 500));
	Masse* m2 = new Masse(50.0, -5.0, Color::White, Vector2f(900, 500));
	
	//Game logic
	bool play = false;
	bool ma1 = true;
	bool ma2 = false;
	bool mouseheld = false;

	//GUI
	Font font;
	Text text;

	//Mouse positions
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	//World
	bool collision = false;
	//Resources

	//private Functions:
	void update();
	void updateDirection();
	void updateCollision();
	void updateInput();
	void updateGUI();
	void updateMousePosition();
	void render();
	void renderGUI(RenderTarget*);
	void initWindow();
	void initGUI();
	void initVariables();
	void initFirstPosition();
	void pollEvent();
};

