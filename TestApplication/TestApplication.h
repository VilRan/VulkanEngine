#pragma once

#include "VulkanApplication.h"
#include "Camera3D.h"
#include "Camera2D.h"

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
	virtual void OnUpdate(UpdateEvent update);
	virtual void OnKey(KeyEvent key);

private:
	std::shared_ptr<Camera3D> Camera;
	std::shared_ptr<Camera2D> Camera2;
	::Model* Model = nullptr;
	::Model* Model2 = nullptr;
	::Texture* Texture = nullptr;
	::Texture* Texture2 = nullptr;
	::Texture* Texture3 = nullptr;
	::SpriteFont* Font = nullptr;
	::Scene* Scene2 = nullptr;
	::Scene* Scene3 = nullptr;
	::Actor* Actor = nullptr;
	::Actor* Actor2 = nullptr;
	::Actor* Actor3 = nullptr;
	::Actor* Actor4 = nullptr;
	::Actor* Actor5 = nullptr;
	::Actor* Actor6 = nullptr;
	::Sprite* Sprite = nullptr;
	float TestCounter = 0.0f;
};

