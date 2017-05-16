#pragma once

#include "Model.h"
#include "Scene.h"

class IApplication
{
public:
	IApplication();
	virtual ~IApplication();

	virtual void Run() = 0;
	virtual Model* LoadModel(const char* path) = 0;
	virtual Scene* GetRootScene() = 0;

protected:
	virtual void OnLoadContent() = 0;
	virtual void OnStart() = 0;
	virtual void OnUpdate() = 0;
};

