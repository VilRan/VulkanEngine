#pragma once
#include <glad/glad.h>
#include "GlfwApplication.h"

#include "OpenGLModelManager.h"
#include "OpenGLTextureManager.h"
#include "FontManager.h"
#include "OpenGLScene.h"

class OpenGLApplication :
	public GlfwApplication
{
public:
	OpenGLApplication();
	virtual ~OpenGLApplication();

	virtual ModelManager* GetModels() { return &Models; }
	virtual TextureManager* GetTextures() { return &Textures; }
	virtual SpriteManager* GetSprites() { return &Sprites; }
	virtual FontManager* GetFonts() { return &Fonts; }
	virtual Scene* GetRootScene() { return RootScene; }

protected:
	virtual void BeginRun();
	virtual void BeginUpdate(UpdateEvent update);
	virtual void EndUpdate(UpdateEvent update);
	virtual void EndRun();
	virtual void OnWindowResized();
	virtual void OnInitializeWindow();

private:
	OpenGLModelManager Models;
	OpenGLTextureManager Textures;
	SpriteManager Sprites;
	FontManager Fonts;
	OpenGLScene* RootScene;
	GLuint ShaderProgram;
	GLuint VertexShader;
	GLuint FragmentShader;

	void CreateShader(const char* path, GLenum type, GLuint program, GLuint* shader);
};
