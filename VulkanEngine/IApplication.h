#pragma once

#include "Model.h"

class IApplication
{
public:
	IApplication();
	virtual ~IApplication();

	virtual void Run() = 0;
	virtual Model* LoadModel(const char* path) = 0;
};

