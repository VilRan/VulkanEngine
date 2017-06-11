#include "UpdateEvent.h"

UpdateEvent::UpdateEvent()
	: DeltaTime(1.0), AverageDeltaTime(1.0)
{
}

UpdateEvent::UpdateEvent(const double deltaTime, const double averageDeltaTime)
	: DeltaTime(deltaTime), AverageDeltaTime(averageDeltaTime)
{
}

UpdateEvent::~UpdateEvent()
{
}
