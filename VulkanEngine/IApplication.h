#pragma once
class IApplication
{
public:
	IApplication();
	virtual ~IApplication();

	virtual void Run() = 0;
};

