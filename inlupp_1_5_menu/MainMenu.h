#ifndef INLUPP_1_5_MENU_MAINMENU_H
#define INLUPP_1_5_MENU_MAINMENU_H

#include <SFML/Graphics/CircleShape.hpp>
#include "State.h"
#include "Event.h"

class MainMenu : public State
{
public:
	MainMenu();
	void handle(Event e) override;
	void draw(sf::RenderWindow window) override;
private:
	sf::CircleShape m_shape;
};

#endif //INLUPP_1_5_MENU_MAINMENU_H
