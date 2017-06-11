#pragma once
class MouseButtonEvent
{
public:
	MouseButtonEvent(const int button, const int action, const int mods, const double x, const double y);
	virtual ~MouseButtonEvent();

	const int GetButton() const { return Button; }
	const int GetAction() const { return Action; }
	const int GetMods() const { return Mods; }
	const double GetX() const { return X; }
	const double GetY() const { return Y; }

private:
	const int Button, Action, Mods;
	const double X, Y;
};
