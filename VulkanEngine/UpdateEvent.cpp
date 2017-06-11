#include "UpdateEvent.h"

UpdateEvent::UpdateEvent()
	: UpdateEvent(1.0, 1.0, 1.0, 1.0)
{
}

UpdateEvent::UpdateEvent(const double deltaTime, const double averageDeltaTime)
	: UpdateEvent(deltaTime, averageDeltaTime, deltaTime, deltaTime)
{
}

UpdateEvent::UpdateEvent(const double deltaTime, const double averageDeltaTime, const double minDeltaTime, const double maxDeltaTime)
	: DeltaTime(deltaTime), AverageDeltaTime(averageDeltaTime), MinDeltaTime(minDeltaTime), MaxDeltaTime(maxDeltaTime)
{
}

UpdateEvent::~UpdateEvent()
{
}
