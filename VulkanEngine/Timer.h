#pragma once

#include <functional>
#include "TimerEvent.h"
#include "UpdateEvent.h"

class Timer
{
public:
	Timer();
	Timer(std::function<void(TimerEvent)> event, double interval, bool repeating = true);
	virtual ~Timer();

	void Update(UpdateEvent update);
	void Start() { Running = true; }
	void Stop() { Running = false; }
	void SetEvent(std::function<void(TimerEvent)> event) { Event = event; }
	const double GetInterval() const { return Interval; }
	void SetInterval(double interval) { Interval = interval; }
	const bool IsRepeating() const { return Repeating; }
	void SetRepeating(bool repeating) { Repeating = repeating; }
	const bool IsRunning() const { return Running; }

private:
	std::function<void(TimerEvent)> Event;
	double Interval = 1.0, Counter = 0.0;
	bool Repeating = true, Running = false;
};
