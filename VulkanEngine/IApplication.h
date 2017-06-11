#pragma once

#include "Model.h"
#include "Sprite.h"
#include "Scene.h"
#include "Rectangle.h"
#include "SpriteFont.h"
#include "UpdateEvent.h"
#include "KeyEvent.h"
#include "CursorPositionEvent.h"
#include "ClickEvent.h"
#include "ScrollEvent.h"

class IApplication
{
public:
	IApplication();
	virtual ~IApplication();

	virtual void Run() = 0;
	virtual void Exit() = 0;
	virtual void Resize(uint32_t width, uint32_t height) = 0;
	virtual void SetBorder(bool enabled) = 0;
	virtual float GetAspectRatio() = 0;
	virtual Model* CreateModel(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) = 0;
	virtual Model* LoadModel(const char* path) = 0;
	virtual Texture* LoadTexture(const char* path) = 0;
	virtual Sprite* CreateSprite(Texture* texture) = 0;
	virtual Sprite* CreateSprite(Texture* texture, Rectangle area) = 0;
	virtual SpriteFont* LoadFont(Texture* texture, const char* metaPath) = 0;
	virtual SpriteFont* LoadFont(const char* texturePath, const char* metaPath) = 0;
	virtual Scene* GetRootScene() = 0;
	virtual char* GetTitle() = 0;
	virtual int GetKeyState(int keyId) = 0;
	virtual int GetMouseButtonState(int buttonId) = 0;

protected:
	virtual void OnLoadContent() = 0;
	virtual void OnStart() = 0;
	virtual void OnUpdate(UpdateEvent update) = 0;
	virtual void OnKey(KeyEvent key) = 0;
	virtual void OnCursor(CursorPositionEvent cursor) = 0;
	virtual void OnClick(ClickEvent click) = 0;
	virtual void OnScroll(ScrollEvent scroll) = 0;
};
