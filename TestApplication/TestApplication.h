#pragma once

#include "VulkanApplication.h"

class TestApplication :
	public VulkanApplication
{
public:
	TestApplication();
	virtual ~TestApplication();

protected:
	virtual void OnLoadContent();
	virtual void OnStart();
	virtual void OnUpdate();

private:
	::Model* Model;
	Actor* Actor;
	float TestCounter = 0.0f;
};

