#pragma once
class CursorPositionEvent
{
public:
	CursorPositionEvent(const double x, const double y, const double deltaX, const double deltaY);
	virtual ~CursorPositionEvent();

	const double GetX() const { return X; }
	const double GetY() const { return Y; }
	const double GetDeltaX() const { return DeltaX; }
	const double GetDeltaY() const { return DeltaY; }

private:
	const double X, Y, DeltaX, DeltaY;
};
