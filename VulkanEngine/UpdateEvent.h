#pragma once
class UpdateEvent
{
public:
	UpdateEvent(const double deltaTime, const double averageDeltaTime);
	virtual ~UpdateEvent();

	const double GetDeltaTime() const { return DeltaTime; }
	const double GetAverageDeltaTime() const { return AverageDeltaTime; }
	const double GetFramesPerSecond() const { return 1.0 / DeltaTime; }
	const double GetAverageFramesPerSecond() const { return 1.0 / AverageDeltaTime; }

private:
	const double DeltaTime, AverageDeltaTime;
};
