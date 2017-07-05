#include "MainMenu.h"

MainMenu::MainMenu()
	: m_shape(100.f)
{
	m_shape.setFillColor(sf::Color::Green);
}

void MainMenu::handle(Event e)
{
	switch(e)
	{
	case Event::ENTER:
		break;
	case Event::EXIT:
		break;
	}
	// todo: writeme
}

void MainMenu::draw(sf::RenderWindow window)
{
	window.draw(m_shape);
}

