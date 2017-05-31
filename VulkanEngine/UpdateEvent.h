#pragma once
class UpdateEvent
{
public:
	UpdateEvent(const double deltaTime);
	virtual ~UpdateEvent();

	const double GetDeltaTime() const { return DeltaTime; }
	const double GetFramesPerSecond() const { return 1.0 / DeltaTime; }

private:
	const double DeltaTime;
};
