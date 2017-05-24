#pragma once

#include "Model.h"
#include "Scene.h"

class IApplication
{
public:
	IApplication();
	virtual ~IApplication();

	virtual void Run() = 0;
	virtual void Resize(uint32_t width, uint32_t height) = 0;
	virtual void SetBorder(bool enabled) = 0;
	virtual Model* LoadModel(const char* path) = 0;
	virtual Texture* LoadTexture(const char* path) = 0;
	virtual Scene* GetRootScene() = 0;
	virtual char* GetTitle() = 0;

protected:
	virtual void OnLoadContent() = 0;
	virtual void OnStart() = 0;
	virtual void OnUpdate() = 0;
};

