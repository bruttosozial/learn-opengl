#include "OpenGLStuff.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void OpenGLStuff::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void OpenGLStuff::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
