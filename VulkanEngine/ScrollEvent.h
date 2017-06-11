#pragma once
class ScrollEvent
{
public:
	ScrollEvent();
	ScrollEvent(double deltaX, double deltaY);
	virtual ~ScrollEvent();

	const double GetDeltaX() const { return DeltaX; }
	const double GetDeltaY() const { return DeltaY; }

private:
	double DeltaX, DeltaY;
};

