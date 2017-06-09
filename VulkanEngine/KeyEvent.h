#pragma once
class KeyEvent
{
public:
	KeyEvent(const int id, const int scancode, const int action, const int mods);
	virtual ~KeyEvent();

	const int GetId() const { return ID; }
	const int GetScancode() const { return Scancode; }
	const int GetAction() const { return Action; }
	const int GetMods() const { return Mods; }

private:
	const int ID, Scancode, Action, Mods;
};

