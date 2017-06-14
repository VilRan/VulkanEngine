#include "UpdateEvent.h"

UpdateEvent::UpdateEvent()
	: UpdateEvent(1.0, 1.0, 1.0, 1.0, 0)
{
}

UpdateEvent::UpdateEvent(const double deltaTime, const double averageDeltaTime)
	: UpdateEvent(deltaTime, averageDeltaTime, deltaTime, deltaTime, 0)
{
}

UpdateEvent::UpdateEvent(const double deltaTime, const double averageDeltaTime, const double minDeltaTime, const double maxDeltaTime, size_t frameNumber)
	: DeltaTime(deltaTime), AverageDeltaTime(averageDeltaTime), MinDeltaTime(minDeltaTime), MaxDeltaTime(maxDeltaTime), FrameNumber(frameNumber)
{
}

UpdateEvent::~UpdateEvent()
{
}
