#include "MouseButtonEvent.h"

MouseButtonEvent::MouseButtonEvent(const int button, const int action, const int mods, const double x, const double y)
	: Button(button), Action(action), Mods(mods), X(x), Y(y)
{
}

MouseButtonEvent::~MouseButtonEvent()
{
}
