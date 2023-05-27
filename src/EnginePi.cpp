#define _USE_MATH_DEFINES

#include "EnginePi.h"
#include <iostream>
#include <math.h>
#include <cmath>
#include <sstream>
#include <iomanip>


EnginePi::EnginePi()
{
	this->initWindow();
	this->initVariables();
	this->initGUI();
}

EnginePi::~EnginePi()
{
	delete this->window;
	delete this->Bomb;
	delete this->m1;
	delete this->m2;
}

const bool EnginePi::running() const
{
	return this->window->isOpen();
}

void EnginePi::run()
{
	while (this->running())
	{
		this->render();
		this->update();
	}
}

void EnginePi::update()
{
	this->pollEvent();
	this->updateCollision();
	this->updateDirection();
	if (this->play && !this->endSim)
	{
		this->m1->update();
		this->m2->update();
	}
	else if(!this->play && !this->endSim)
	{
		this->initFirstPosition();
	}
	else
	{

	}

	this->updateGUI();
	this->updateInput();
}

void EnginePi::updateDirection()
{
	CircleShape sM1 = m1->getShape();
	CircleShape sM2 = m2->getShape();
	if (collision)
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
			2 *
			(ma1 * vel1 + ma2 * vel2) /
			(ma2 + ma1)
			- vel1
		);
		m2->setVel(
			2 *
			(ma1 * vel1 + ma2 * vel2) /
			(ma2 + ma1)
			- vel2
		);
	}

	
	//rechts
	if (m2->getPos().x >= this->window->getSize().x - 2 * sM2.getRadius() && abs(this->m1->getVel()) < abs(this->m2->getVel()))
	{
		this->endSim = true;
	}

	//links
	if (m1->getPos().x <= 0)
	{
		m2->stopUpdate();
		m1->setVel(-m1->getVel());
		
		this->collisions++;
	}
	else if(m1->getPos().x >= 0)
	{
		m2->playUpdate();
	}

}

void EnginePi::updateCollision()
{
	CircleShape sM1 = m1->getShape();
	CircleShape sM2 = m2->getShape();

	if (sM1.getGlobalBounds().intersects(sM2.getGlobalBounds()))
	{
		this->collision = true;
		if (!endSim)
		{
			this->collisions++;
		}
		
	}
	else
	{
		this->collision = false;
	}
}

void EnginePi::updateInput()
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
		if (this->ev.key.code == Keyboard::V)
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

void EnginePi::updateGUI()
{
	std::stringstream ss1;
	ss1 << std::setprecision(4) << "Legende:" << "\n" <<
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
		"Position 2:   " << "(" << m2->getPos().x << "," << m2->getPos().y << ")" << "\n";

	this->text.setString(ss1.str());

	std::stringstream ss2;
	ss2 << std::setprecision(4) << "Kollisionen:" << collisions << "\n";
	if (endSim)
	{
		ss2 << std::setprecision(4) << "Resultat:" << (collisions / M_PI) << "\n";
	}
	this->resultat.setString(ss2.str());
}

void EnginePi::render()
{
	this->window->clear(Color::White);
	this->renderGUI(this->window);
	//this->Bomb->render(this->window);
	this->m1->render(this->window);
	this->m2->render(this->window);
	this->window->display();
}

void EnginePi::renderGUI(RenderTarget* target)
{
	target->draw(this->text);
	target->draw(this->resultat);
}

void EnginePi::initWindow()
{
	this->videomode.height = 700;
	this->videomode.width = 1800;
	this->window = new RenderWindow(this->videomode, "Stoßsimulation", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void EnginePi::initGUI()
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
	this->text.setPosition(this->window->getSize().x - 6.5 * this->text.getGlobalBounds().width, 0);

	this->resultat.setFont(font);
	this->resultat.setCharacterSize(40);
	this->resultat.setFillColor(Color(153, 205, 178));
	this->resultat.setString("none");
	this->resultat.setPosition(0.5 * this->window->getSize().x - 2*this->resultat.getGlobalBounds().width, 300);
}

void EnginePi::initVariables()
{

}

void EnginePi::initFirstPosition()
{
	this->play = true;
	this->m1->setPos(Vector2f(100, 550));
	this->m2->setPos(Vector2f(300, 550));

	float ma1;
	float ma2;
	float vel1;
	float vel2;

	std::cout << "Masse 1: ";
	std::cin >> ma1;
	std::cout << "Masse 2: ";
	std::cin >> ma2;
	/*std::cout << "Geschwindigkeit 1: ";
	std::cin >> vel1;
	std::cout << "Geschwindigkeit 2: ";
	std::cin >> vel2;*/

	m1->setMass(ma1);
	m2->setMass(ma2);
	m1->setVel(0);
	m2->setVel(-1);

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

void EnginePi::pollEvent()
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
