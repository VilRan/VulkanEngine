#include "ScrollEvent.h"

ScrollEvent::ScrollEvent()
{
}

ScrollEvent::ScrollEvent(double deltaX, double deltaY)
	: DeltaX(deltaX), DeltaY(deltaY)
{
}

ScrollEvent::~ScrollEvent()
{
}
