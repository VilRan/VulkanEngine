#include "OpenGLApplication.h"

#include "FileHelper.h"
#include <iostream>

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

	int success;
	char log[512];
	glViewport(0, 0, GetWidth(), GetHeight());
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	ShaderProgram = glCreateProgram();
	CreateShader("../Shaders/shader-opengl.vert", GL_VERTEX_SHADER, ShaderProgram, &VertexShader);
	CreateShader("../Shaders/shader-opengl.frag", GL_FRAGMENT_SHADER, ShaderProgram, &FragmentShader);
	glLinkProgram(ShaderProgram);
	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ShaderProgram, 512, NULL, log);
	}

	Sprites.Initialize(&Models);
	Fonts.Initialize(&Textures, &Sprites);

	OnLoadContent();

	RootScene = new OpenGLScene(ShaderProgram, GetAspectRatio());

	OnStart();
}

void OpenGLApplication::BeginUpdate(UpdateEvent update)
{
}

void OpenGLApplication::EndUpdate(UpdateEvent update)
{
	glfwSwapBuffers(GetWindow());
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	RootScene->Draw();
}

void OpenGLApplication::EndRun()
{
	glDeleteProgram(ShaderProgram);
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
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

void OpenGLApplication::CreateShader(const char* path, GLenum type, GLuint program, GLuint* shader)
{
	int success;
	char log[512];
	*shader = glCreateShader(type);
	auto vertexShaderSource = FileHelper::ReadText(path);
	auto vertexShaderData = vertexShaderSource.data();
	glShaderSource(*shader, 1, &vertexShaderData, NULL);
	glCompileShader(*shader);
	glAttachShader(program, *shader);

	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*shader, 512, NULL, log);
		std::cout << log;
	}
}
