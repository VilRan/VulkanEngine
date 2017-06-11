#pragma once
class TimerEvent
{
public:
	TimerEvent(const double deltaTime);
	virtual ~TimerEvent();

	const double GetDeltaTime() const { return DeltaTime; }

private:
	const double DeltaTime;
};
