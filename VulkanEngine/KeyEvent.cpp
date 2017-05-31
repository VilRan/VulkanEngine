#include "KeyEvent.h"

KeyEvent::KeyEvent(const int id, const int scancode, const int action, const int mods)
	: ID(id), Scancode(scancode), Action(action), Mods(mods)
{
}

KeyEvent::~KeyEvent()
{
}
