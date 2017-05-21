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
	::Model* Model2;
	::Texture* Texture;
	::Texture* Texture2;
	::Texture* Texture3;
	::Actor* Actor;
	::Actor* Actor2;
	::Actor* Actor3;
	float TestCounter = 0.0f;
};

