#pragma once
#include "IApplication.h"

#include <GLFW/glfw3.h>

class GlfwApplication :
	public IApplication
{
public:
	GlfwApplication();
	virtual ~GlfwApplication();

	virtual void Run();
	virtual void Exit();

	virtual void Resize(uint32_t width, uint32_t height);
	virtual void SetBorder(bool enabled);
	virtual float GetAspectRatio();
	virtual int GetKeyState(int keyId);
	virtual int GetMouseButtonState(int buttonId);
	const uint32_t GetWidth() const { return Width; }
	const uint32_t GetHeight() const { return Height; }
	const double GetFpsLimit() const { return FpsLimit; }
	void SetFpsLimit(double fpsLimit) { FpsLimit = fpsLimit; }

protected:
	virtual void BeginRun() = 0;
	virtual void BeginUpdate(UpdateEvent update) = 0;
	virtual void EndUpdate(UpdateEvent update) = 0;
	virtual void EndRun() = 0;
	virtual void OnWindowResized() = 0;
	virtual void OnInitializeWindow();

	GLFWwindow* GetWindow() const { return Window; }

private:
	GLFWwindow* Window;
	uint32_t Width = 800;
	uint32_t Height = 600;
	bool Border = false;
	std::vector<double> DeltaTimes;
	size_t DeltaTimeWritePosition = 0;
	size_t UpdateNumber = 0;
	double PreviousTime = 0;
	double PreviousCursorX = 0;
	double PreviousCursorY = 0;
	double FpsLimit = 1000;
	bool ExitCalled = false;

	void InitializeWindow();
	void Update();
	static void HandleWindowResized(GLFWwindow* window, int width, int height);
	static void HandleKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void HandleCursorPosition(GLFWwindow* window, double x, double y);
	static void HandleClickEvent(GLFWwindow* window, int button, int action, int mods);
	static void HandleScrollEvent(GLFWwindow* window, double deltaX, double deltaY);
};
