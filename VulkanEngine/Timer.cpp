#include "Timer.h"

Timer::Timer()
{
}

Timer::Timer(std::function<void(TimerEvent)> event, double interval, bool repeating, bool oncePerUpdate)
{
	Event = event;
	Interval = interval;
	Repeating = repeating;
	OncePerUpdate = oncePerUpdate;
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

		if (OncePerUpdate)
		{
			Counter = fmod(Counter, Interval);
		}

		if (Repeating == false)
		{
			Running = false;
			Counter = 0;
			break;
		}
	}
}
