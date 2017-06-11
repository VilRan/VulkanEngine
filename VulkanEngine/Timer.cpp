#include "Timer.h"

Timer::Timer()
{
}

Timer::Timer(std::function<void(TimerEvent)> event, double interval, bool repeating)
{
	Event = event;
	Interval = interval;
	Repeating = repeating;
}

Timer::~Timer()
{
}

void Timer::Update(UpdateEvent update)
{
	if (Running == false)
	{
		return;
	}

	Counter += update.GetDeltaTime();
	while (Counter >= Interval)
	{
		Counter -= Interval;

		Event(TimerEvent(Counter));

		if (Repeating == false)
		{
			Running = false;
			Counter = 0;
		}
	}
}
