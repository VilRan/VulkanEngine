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
	::Model* Model = nullptr;
	::Model* Model2 = nullptr;
	::Texture* Texture = nullptr;
	::Texture* Texture2 = nullptr;
	::Texture* Texture3 = nullptr;
	::Actor* Actor = nullptr;
	::Actor* Actor2 = nullptr;
	::Actor* Actor3 = nullptr;
	::Actor* Actor4 = nullptr;
	float TestCounter = 0.0f;
};

