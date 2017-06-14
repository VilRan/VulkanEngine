#pragma once
#include "GlfwApplication.h"

#include "FontManager.h"

class OpenGLApplication :
	public GlfwApplication
{
public:
	OpenGLApplication();
	virtual ~OpenGLApplication();

	virtual Model* CreateModel(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
	virtual Model* LoadModel(const char* path);
	virtual Texture* LoadTexture(const char* path);
	virtual Sprite* CreateSprite(Texture* texture);
	virtual Sprite* CreateSprite(Texture* texture, Rectangle area);
	virtual SpriteFont* LoadFont(Texture* texture, const char* metaPath);
	virtual SpriteFont* LoadFont(const char* texturePath, const char* metaPath);
	//virtual Scene* GetRootScene() { return RootScene; }

protected:
	virtual void BeginRun();
	virtual void BeginUpdate();
	virtual void EndUpdate();
	virtual void EndRun();
	virtual void OnWindowResized();

private:
	SpriteManager Sprites;
	FontManager Fonts;
};
