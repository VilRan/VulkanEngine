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
	::Texture* Texture;
	::Texture* Texture2;
	::Actor* Actor;
	::Actor* Actor2;
	float TestCounter = 0.0f;
};

