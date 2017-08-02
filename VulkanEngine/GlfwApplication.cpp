#define STB_IMAGE_IMPLEMENTATION
#include "GlfwApplication.h"

#include <thread>

GlfwApplication::GlfwApplication()
{
}

GlfwApplication::~GlfwApplication()
{
}

void GlfwApplication::Run()
{
	InitializeWindow();
	BeginRun();

	//OnStart();

	DeltaTimes.resize(100);
	PreviousTime = glfwGetTime();

	while (glfwWindowShouldClose(Window) == false && ExitCalled == false)
	{
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - PreviousTime;
		
		double frameTimeLimit = 1.0 / FpsLimit;
		if (deltaTime < frameTimeLimit)
		{
			std::this_thread::sleep_for(std::chrono::duration<double>(frameTimeLimit - deltaTime));
			deltaTime = frameTimeLimit;
		}
		
		DeltaTimes[DeltaTimeWritePosition] = deltaTime;
		DeltaTimeWritePosition++;
		if (DeltaTimeWritePosition >= DeltaTimes.size())
		{
			DeltaTimeWritePosition = 0;
		}

		double totalDeltaTime = 0.0, minDeltaTime = DBL_MAX, maxDeltaTime = 0.0;
		for (auto time : DeltaTimes)
		{
			totalDeltaTime += time;
			if (time < minDeltaTime)
			{
				minDeltaTime = time;
			}
			else if (time > maxDeltaTime)
			{
				maxDeltaTime = time;
			}
		}
		double averageDeltaTime = totalDeltaTime / DeltaTimes.size();

		PreviousTime = currentTime;

		UpdateEvent update(deltaTime, averageDeltaTime, minDeltaTime, maxDeltaTime, UpdateNumber);

		BeginUpdate(update);
		glfwPollEvents();

		OnUpdate(update);

		EndUpdate(update);
		UpdateNumber++;
	}

	EndRun();
	glfwDestroyWindow(Window);
	glfwTerminate();
}

void GlfwApplication::Exit()
{
	ExitCalled = true;
}

void GlfwApplication::Resize(uint32_t width, uint32_t height)
{
	Width = width;
	Height = height;
	if (Window != nullptr)
	{
		glfwSetWindowSize(Window, Width, Height);
	}
}

void GlfwApplication::SetBorder(bool enabled)
{
	Border = enabled;
}

float GlfwApplication::GetAspectRatio()
{
	return Width / (float)Height;
}

int GlfwApplication::GetKeyState(int keyId)
{
	return glfwGetKey(Window, keyId);
}

int GlfwApplication::GetMouseButtonState(int buttonId)
{
	return glfwGetMouseButton(Window, buttonId);
}

void GlfwApplication::OnInitializeWindow()
{
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void GlfwApplication::InitializeWindow()
{
	glfwInit();

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	Width = mode->width;
	Height = mode->height;

	OnInitializeWindow();
	glfwWindowHint(GLFW_DECORATED, Border);

	Window = glfwCreateWindow(Width, Height, GetTitle(), nullptr, nullptr);

	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowUserPointer(Window, this);
	glfwSetWindowSizeCallback(Window, GlfwApplication::HandleWindowResized);
	glfwSetKeyCallback(Window, GlfwApplication::HandleKeyboardEvent);
	glfwSetCursorPosCallback(Window, GlfwApplication::HandleCursorPosition);
	glfwSetMouseButtonCallback(Window, GlfwApplication::HandleClickEvent);
	glfwSetScrollCallback(Window, GlfwApplication::HandleScrollEvent);

	glfwMakeContextCurrent(Window);
}

void GlfwApplication::HandleWindowResized(GLFWwindow* window, int width, int height)
{
	if (width == 0 || height == 0)
	{
		return;
	}

	GlfwApplication* application = reinterpret_cast<GlfwApplication*>(glfwGetWindowUserPointer(window));
	application->OnWindowResized();
}

void GlfwApplication::HandleKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	GlfwApplication* application = reinterpret_cast<GlfwApplication*>(glfwGetWindowUserPointer(window));
	application->OnKey(KeyEvent(key, scancode, action, mods));
}

void GlfwApplication::HandleCursorPosition(GLFWwindow* window, double x, double y)
{
	GlfwApplication* application = reinterpret_cast<GlfwApplication*>(glfwGetWindowUserPointer(window));
	application->OnCursor(CursorPositionEvent(x, y, x - application->PreviousCursorX, y - application->PreviousCursorY));
	application->PreviousCursorX = x;
	application->PreviousCursorY = y;
}

void GlfwApplication::HandleClickEvent(GLFWwindow* window, int button, int action, int mods)
{
	GlfwApplication* application = reinterpret_cast<GlfwApplication*>(glfwGetWindowUserPointer(window));
	application->OnMouseButton(MouseButtonEvent(button, action, mods, application->PreviousCursorX, application->PreviousCursorY));
}

void GlfwApplication::HandleScrollEvent(GLFWwindow* window, double deltaX, double deltaY)
{
	GlfwApplication* application = reinterpret_cast<GlfwApplication*>(glfwGetWindowUserPointer(window));
	application->OnScroll(ScrollEvent(deltaX, deltaY));
}
