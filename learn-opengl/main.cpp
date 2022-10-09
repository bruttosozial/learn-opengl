#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGLStuff.h"
#include "Shader.h"

int main() {
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "opengl lern", NULL, NULL);
	if (window == nullptr) {
		std::cout << "no window here :((" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, OpenGLStuff::framebuffer_size_callback);

	float verticesTriangle[] = {
		-0.5f, -0.5f,  0.0f, // lower left
		 0.5f, -0.5f,  0.0f, // lower right
		 0.0f,  0.5f,  0.0f  // up
	};
	
	float twoTrianglesVertices[] = {
		-0.5f, -0.5f,  0.0f,  // 1 - lower left
		 0.5f, -0.5f,  0.0f,  // 1 - lower right
		 0.0f,  0.5f,  0.0f,  // 1 - up
		-0.5f, -1.5f,  0.0f,  // 2 - lower left
		 0.5f, -1.5f,  0.0f,  // 2 - lower right
		 0.0f, -0.5f,  0.0f   // 2 - up
	};

	float squareVertices[] = {
		-0.5f,  0.5f, 0.0f, // Upper left
		 0.5f,  0.5f, 0.0f, // upper right
		-0.5f, -0.5f, 0.0f, // lower left
		 0.5f, -0.5f, 0.0f  // lower right
	};

	unsigned int indices[] = {
		2, 0, 1,
		1, 3, 2
	};

	// Initialise Vertex Array Object (Stores references to VBO)
	unsigned int vao_id;
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

	// Initialise Vertex Buffer Object (Stores vertex data)
	unsigned int vbo_id;
	glGenBuffers(1, &vbo_id);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

	// insert triangle into Vertex Buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangle), verticesTriangle, GL_STATIC_DRAW);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(twoTrianglesVertices), twoTrianglesVertices, GL_STATIC_DRAW);

	// draw square using element buffer object
	// glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
	// unsigned int EBO;
	// glGenBuffers(1, &EBO);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	float verticesTriangle2[] = {
		-0.5f, -1.5f,  0.0f,  // 2 - lower left
		 0.5f, -1.5f,  0.0f,  // 2 - lower right
		 0.0f, -0.5f,  0.0f   // 2 - up
	};

	unsigned int vao_2_id;
	glGenVertexArrays(1, &vao_2_id);
	glBindVertexArray(vao_2_id);
	
	unsigned int vbo_2_id;
	glGenBuffers(1, &vbo_2_id);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_2_id);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangle2), verticesTriangle2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	//Shader s = Shader("shader/position_shader.vert", "shader/orange_shader.frag");
	Shader s = Shader("shader/position_shader.vert", "shader/uniform_color_shader.frag");
	Shader s2 = Shader("shader/position_shader.vert", "shader/yellow_shader.frag");

	float time;
	float redValue;
	
	while (!glfwWindowShouldClose(window)) {
		// input stufffff
		OpenGLStuff::processInput(window);

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		s.use();

		time = glfwGetTime();
		redValue = (sin(time) / 2.0f) + 0.5f;
		const char * t = "ourColor";
		s.set4f(t, redValue, 0.0f, 0.0f, 1.0f);
		glBindVertexArray(vao_id);

		// drawing triangle without element buffer object
		glDrawArrays(GL_TRIANGLES, 0, 3);

		 //s2.use();
		 //glBindVertexArray(vao_2_id);
		 //glDrawArrays(GL_TRIANGLES, 0, 3);
		
		// drawing square with element buffer object
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}