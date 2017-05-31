#pragma once

#include "VulkanApplication.h"

class TemplateApplication :
	public VulkanApplication
{
public:
	TemplateApplication();
	virtual ~TemplateApplication();

	virtual char* GetTitle() { return "Template Application"; }

protected:
	virtual void OnLoadContent();
	virtual void OnStart();
	virtual void OnUpdate();
};