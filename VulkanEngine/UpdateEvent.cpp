#include "UpdateEvent.h"

UpdateEvent::UpdateEvent(const double deltaTime, const double averageDeltaTime)
	: DeltaTime(deltaTime), AverageDeltaTime(averageDeltaTime)
{
}

UpdateEvent::~UpdateEvent()
{
}
