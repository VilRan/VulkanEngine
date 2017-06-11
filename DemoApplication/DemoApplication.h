#pragma once
#include "VulkanApplication.h"

#include "Ruleset.h"
#include "GameMap.h"
#include "FirstPersonCamera.h"
#include "Timer.h"

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
	virtual void OnCursor(CursorPositionEvent cursor);
	virtual void OnClick(ClickEvent click);
	virtual void OnScroll(ScrollEvent scroll);

private:
	SpriteFont* Font;
	Scene* UiScene;
	Scene* MapScene;

	Ruleset Ruleset;
	GameMap Map;
	std::shared_ptr<FirstPersonCamera> Camera;
	Label* FpsLabel;
	Timer FpsTimer;
	UpdateEvent FpsUpdate;

	void TryMoveCamera(UpdateEvent update);
	void UpdateFpsLabel(UpdateEvent update);
	void HandleFpsTimer(TimerEvent timer);
};
