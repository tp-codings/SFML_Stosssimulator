#include "Engine.h"
#include <iostream>
#include <math.h>
#include <cmath>
#include <sstream>
#include <iomanip>

Engine::Engine()
{
	this->initWindow();
	this->initVariables();
	this->initGUI();
}

Engine::~Engine()
{
	delete this->window;
	delete this->Bomb;
	delete this->m1;
	delete this->m2;
}

const bool Engine::running() const
{
	return this->window->isOpen();
}

void Engine::run()
{
	while (this->running())
	{
		this->update();
		this->render();
	}
}

void Engine::update()
{
	this->pollEvent();
	this->updateCollision();
	this->updateDirection();
	if (play)
	{
		this->m1->update();
		this->m2->update();
	}
	else
	{
		this->initFirstPosition();
	}
	
	this->updateGUI();
	this->updateMousePosition();
	this->updateInput();
	//std::cout << m1->getPos().x << "  " << m1->getPos().y;
	
}

void Engine::updateDirection()
{
	CircleShape sM1 = m1->getShape();
	CircleShape sM2 = m2->getShape();
	if(collision)
	{
		
		float ma1 = m1->getMass();
		float ma2 = m2->getMass();
		float vel1 = m1->getVel();
		float vel2 = m2->getVel();
		Vector2f posM1 = m1->getPos();
		Vector2f posM2 = m2->getPos();


		m1->setDir(Vector2f(
			(posM2.x - posM1.x) / (std::sqrt(std::pow((posM2.x - posM1.x), 2))),
			(posM2.y - posM1.y) / (std::sqrt(std::pow((posM2.x - posM1.x), 2))))
		);
		m2->setDir(Vector2f(
			(posM2.x - posM1.x) / (std::sqrt(std::pow((posM2.x - posM1.x), 2))),
			(posM2.y - posM1.y) / (std::sqrt(std::pow((posM2.x - posM1.x), 2))))
		);
		m1->setVel(
			2* 
			(ma1*vel1 + ma2*vel2)/
			(ma2 + ma1)
			-vel1
		);
		m2->setVel(
			2 *
			(ma1 * vel1 + ma2 * vel2) /
			(ma2 + ma1)
			- vel2
		);
	}
	
	//oben
	if (m1->getPos().y <= 0)
	{
		m1->setDir(Vector2f(m1->getDir().x, -m1->getDir().y));
	}
	if (m2->getPos().y <= 0)
	{
		m2->setDir(Vector2f(m2->getDir().x, -m2->getDir().y));
	}

	//rechts
	if (m1->getPos().x >= this->window->getSize().x-2*sM1.getRadius())
	{
		m1->setDir(Vector2f(m1->getDir().x, m1->getDir().y));
		m1->setVel(-m1->getVel());
	}
	if (m2->getPos().x >= this->window->getSize().x - 2*sM2.getRadius())
	{
		m2->setDir(Vector2f(m2->getDir().x, m2->getDir().y));
		m2->setVel(-m2->getVel());
	}

	//unten
	if (m1->getPos().y >= this->window->getSize().y - 2*sM1.getRadius())
	{
		m1->setDir(Vector2f(m1->getDir().x, -m1->getDir().y));
	}
	if (m2->getPos().y >= this->window->getSize().y - 2*sM2.getRadius())
	{
		m2->setDir(Vector2f(m2->getDir().x, -m2->getDir().y));
	}

	//links
	if (m1->getPos().x <= 0)
	{
		m1->setDir(Vector2f(m1->getDir().x, m1->getDir().y));
		m1->setVel(-m1->getVel());
	}
	if (m2->getPos().x <= 0)
	{
		m2->setDir(Vector2f(m2->getDir().x, m2->getDir().y));
		m2->setVel(-m2->getVel());
	}

}

void Engine::updateCollision()
{
	CircleShape sM1 = m1->getShape();
	CircleShape sM2 = m2->getShape();

	if (sM1.getGlobalBounds().intersects(sM2.getGlobalBounds()))
	{
		this->collision = true;
	}
	else
	{
		this->collision = false;
	}
}

void Engine::updateInput()
{
	if (Event::KeyPressed)
	{
		if (this->ev.key.code == Keyboard::M)
		{
			float ma1;
			float ma2;
			std::cout << "Masse 1 eingeben: ";
			std::cin >> ma1;
			std::cout << "Masse 2 eingeben: ";
			std::cin >> ma2;

			m1->setMass(ma1);
			m2->setMass(ma2);
		}
		if(this->ev.key.code == Keyboard::V)
		{
			float vel1;
			float vel2;
			std::cout << "Geschwindigkeit 1 eingeben: ";
			std::cin >> vel1;
			std::cout << "Geschwindigkeit 2 eingeben: ";
			std::cin >> vel2;

			m1->setVel(vel1);
			m2->setVel(vel2);
		}
	}
	
}

void Engine::updateGUI()
{
	std::stringstream ss;
	ss << std::setprecision(4) << "Legende:" << "\n" <<
		"Masse 1:   " << m1->getMass() << "\n" <<
		"Masse 2:   " << m2->getMass() << "\n" <<
		"\n" <<

		"Geschwindigkeit 1: " << m1->getVel() << "\n" <<
		"Geschwindigkeit 2: " << m2->getVel() << "\n" <<
		"\n" <<

		"Ekin 1:   " << pow(m1->getVel(), 2) * m1->getMass() * 0.5 << "\n" <<
		"Ekin 2:   " << pow(m2->getVel(), 2) * m2->getMass() * 0.5 << "\n" <<
		"Summe Energien:   " << pow(m1->getVel(), 2) * m1->getMass() * 0.5 + pow(m2->getVel(), 2) * m2->getMass() * 0.5 << "\n" <<
		"\n"

		"Richtung 1:   " << "(" << m1->getDir().x << "," << m1->getDir().y << ")" << "\n" <<
		"Richtung 2:   " << "(" << m2->getDir().x << ", " << m2->getDir().y << ")" <<
		"\n"

		"Position 1:   " << "(" << m1->getPos().x << "," << m1->getPos().y << ")" << "\n" <<
		"Position 2:   " << "(" << m2->getPos().x << "," << m2->getPos().y << ")" << "\n" <<
		
		"Mausposition:  " << "(" << this->mousePosView.x << "," << this->mousePosView.y << ")" << "\n";



	this->text.setString(ss.str());
}

void Engine::updateMousePosition()
{
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Engine::render()
{
	this->window->clear(Color::White);
	this->renderGUI(this->window);
	//this->Bomb->render(this->window);
	this->m1->render(this->window);
	this->m2->render(this->window);
	this->window->display();
}

void Engine::renderGUI(RenderTarget* target)
{
	target->draw(this->text);
}

void Engine::initWindow()
{
	this->videomode.height = 667;
	this->videomode.width = 1000;
	this->window = new RenderWindow(this->videomode, "Stoßsimulation", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Engine::initGUI()
{
	//Load Font
	if (!this->font.loadFromFile("Fonts/Silkscreen-Bold.ttf"))
	{
		std::cout << "Fuck it";
	}

	//Init text
	this->text.setFont(font);
	this->text.setCharacterSize(20);
	this->text.setFillColor(Color(153, 205, 178));
	this->text.setString("none");
	this->text.setPosition(this->window->getSize().x - 6.5*this->text.getGlobalBounds().width, 0);
}

void Engine::initVariables()
{

}

void Engine::initFirstPosition()
{
	if (!Mouse::isButtonPressed(Mouse::Left))
	{
		this->mouseheld = false;
	}
	if (this->ma1)
	{
		if (this->mousePosView.x > 0 && this->mousePosView.x < this->window->getSize().x - 2 * this->m1->getShape().getRadius() && this->mousePosView.y >= 0 && this->mousePosView.y < this->window->getSize().y - 2 * this->m1->getShape().getRadius())
		{
			this->m1->setPos(this->mousePosView);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				this->mouseheld = true;
				this->ma1 = false;
				this->ma2 = true;
			}
		}
	}

	if (this->ma2 && !this->mouseheld)
	{
		
		if (this->mousePosView.x > 0 && this->mousePosView.x < this->window->getSize().x - 2 * this->m2->getShape().getRadius() && this->mousePosView.y >= 0 && this->mousePosView.y < this->window->getSize().y - 2 * this->m2->getShape().getRadius())
		{
			
			this->m2->setPos(this->mousePosView);
			this->m2->setColor(Color(170, 210, 212));
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				this->ma2 = false;
				this->play = true;
			}
		}
	}
	
	this->m1->setVel(5);

	this->m2->setVel(-5);
	

	Vector2f posM1 = m1->getPos();
	Vector2f posM2 = m2->getPos();
	m1->setDir(Vector2f(
		(posM2.x - posM1.x) / (std::sqrt(std::pow((posM2.x - posM1.x), 2))),
		(posM2.y - posM1.y) / (std::sqrt(std::pow((posM2.x - posM1.x), 2))))
	);
	m2->setDir(Vector2f(
		(posM2.x - posM1.x) / (std::sqrt(std::pow((posM2.x - posM1.x), 2))),
		(posM2.y - posM1.y) / (std::sqrt(std::pow((posM2.x - posM1.x), 2))))
	);
}

void Engine::pollEvent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::F) this->window->close();
			break;
		}
	}
}
