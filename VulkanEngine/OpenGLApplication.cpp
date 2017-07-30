#include "OpenGLApplication.h"

OpenGLApplication::OpenGLApplication()
{
}

OpenGLApplication::~OpenGLApplication()
{
	delete RootScene;
}

void OpenGLApplication::BeginRun()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Failed to initialize GLAD!");
	}

	glViewport(0, 0, GetWidth(), GetHeight());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Sprites.Initialize(&Models);
	Fonts.Initialize(&Textures, &Sprites);

	OnLoadContent();

	RootScene = new OpenGLScene();

	OnStart();
}

void OpenGLApplication::BeginUpdate(UpdateEvent update)
{
}

void OpenGLApplication::EndUpdate(UpdateEvent update)
{
	glfwSwapBuffers(GetWindow());
	glClear(GL_COLOR_BUFFER_BIT);
	RootScene->Draw();
}

void OpenGLApplication::EndRun()
{
}

void OpenGLApplication::OnWindowResized()
{
	glViewport(0, 0, GetWidth(), GetHeight());
}

void OpenGLApplication::OnInitializeWindow()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}
