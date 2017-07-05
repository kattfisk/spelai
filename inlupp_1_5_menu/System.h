#ifndef INLUPP_1_5_MENU_SYSTEM_H
#define INLUPP_1_5_MENU_SYSTEM_H

#include <memory>
#include "Event.h"
#include "State.h"

class System
{

public:
	void dispatch(Event e);
	void push(std::unique_ptr<State> s);
	void pop();
	void transit(std::unique_ptr<State> s);

private:
	std::unique_ptr<State> m_state; // todo: change to stack

};

#endif //INLUPP_1_5_MENU_SYSTEM_H
