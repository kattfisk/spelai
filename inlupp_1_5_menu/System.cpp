#include "System.h"

void System::dispatch(Event e)
{
	m_state->handle(e);
}

void System::push(std::unique_ptr<State> s)
{
// todo: implement
}

void System::pop()
{
// todo: implement
}

void System::transit(std::unique_ptr<State> s)
{
	m_state = std::move(s);
}

