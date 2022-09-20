#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OpenGLStuff
{
public:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow* window);
};

