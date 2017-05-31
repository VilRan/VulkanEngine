#pragma once
#include "VulkanApplication.h"

#include "Ruleset.h"
#include "GameMap.h"
#include "Camera3D.h"


class DemoApplication :
	public VulkanApplication
{
public:
	DemoApplication();
	virtual ~DemoApplication();

	virtual char* GetTitle() { return "Demo Application"; }

protected:
	virtual void OnLoadContent();
	virtual void OnStart();
	virtual void OnUpdate(UpdateEvent update);
	virtual void OnKey(KeyEvent key);

private:
	SpriteFont* Font;
	Scene* UiScene;
	Scene* TerrainScene;

	Ruleset Ruleset;
	GameMap Map;
	std::shared_ptr<Camera3D> Camera;
	Label* FpsLabel;
};
