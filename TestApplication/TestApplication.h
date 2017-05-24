#pragma once

#include "VulkanApplication.h"
#include "Camera3D.h"

class TestApplication :
	public VulkanApplication
{
public:
	TestApplication();
	virtual ~TestApplication();

	virtual char* GetTitle() { return "Test Application"; }

protected:
	virtual void OnLoadContent();
	virtual void OnStart();
	virtual void OnUpdate();

private:
	std::shared_ptr<Camera3D> Camera;
	::Model* Model = nullptr;
	::Model* Model2 = nullptr;
	::Texture* Texture = nullptr;
	::Texture* Texture2 = nullptr;
	::Texture* Texture3 = nullptr;
	::Scene* Scene2 = nullptr;
	::Actor* Actor = nullptr;
	::Actor* Actor2 = nullptr;
	::Actor* Actor3 = nullptr;
	::Actor* Actor4 = nullptr;
	float TestCounter = 0.0f;
};

