#include "CursorPositionEvent.h"

CursorPositionEvent::CursorPositionEvent(const double x, const double y, const double deltaX, const double deltaY)
	: X(x), Y(y), DeltaX(deltaX), DeltaY(deltaY)
{
}

CursorPositionEvent::~CursorPositionEvent()
{
}
