#ifndef INLUPP_1_5_MENU_STATE_H
#define INLUPP_1_5_MENU_STATE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "Event.h"

class State
{
public:
	virtual ~State() = 0;
	virtual void handle(Event e) = 0;
	virtual void draw(sf::RenderWindow window) = 0;
};

#endif //INLUPP_1_5_MENU_STATE_H
