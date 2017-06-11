#pragma once
class UpdateEvent
{
public:
	UpdateEvent();
	UpdateEvent(const double deltaTime, const double averageDeltaTime);
	UpdateEvent(const double deltaTime, const double averageDeltaTime, const double minDeltaTime, const double maxDeltaTime);
	virtual ~UpdateEvent();

	const double GetDeltaTime() const { return DeltaTime; }
	const double GetAverageDeltaTime() const { return AverageDeltaTime; }
	const double GetMinDeltaTime() const { return MinDeltaTime; }
	const double GetMaxDeltaTime() const { return MaxDeltaTime; }
	const double GetFramesPerSecond() const { return 1.0 / DeltaTime; }
	const double GetAverageFramesPerSecond() const { return 1.0 / AverageDeltaTime; }

private:
	double DeltaTime, AverageDeltaTime, MinDeltaTime, MaxDeltaTime;
};
