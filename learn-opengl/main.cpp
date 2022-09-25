#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGLStuff.h"
#include "Shader.h"

int main() {

	
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	
	const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

	const char *fragmentShaderSource_YELLOW = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"    FragColor = vec4(0.44f, 1.0f, 0.67f, 1.0f);\n"
	"}\0";

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

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

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

	// Initialising & compiling vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	int success;
	
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Initialising & compiling fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	int successF;
	char infoLogF[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successF);
	if(!successF)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogF);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogF << std::endl;
	}

	// Create shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int successP;
	char infoLogP[512];
	glGetProgramiv(fragmentShader, GL_COMPILE_STATUS, &successP);
	if(!successP)
	{
		glGetProgramInfoLog(fragmentShader, 512, NULL, infoLogP);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLogP << std::endl;
	}

	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float verticesTriangle2[] = {
		-0.5f, -1.5f,  0.0f,  // 2 - lower left
		 0.5f, -1.5f,  0.0f,  // 2 - lower right
		 0.0f, -0.5f,  0.0f   // 2 - up
	};

	unsigned int VAO_2;
	glGenVertexArrays(1, &VAO_2);
	glBindVertexArray(VAO_2);
	
	unsigned int VBO_2;
	glGenBuffers(1, &VBO_2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_2);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangle2), verticesTriangle2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Initialising & compiling vertex shader
	const unsigned int vertexShader_2 = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader_2, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader_2);
	int success_2;
	
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_2);
	if(!success_2)
	{
		char infoLog_2[512];
		glGetShaderInfoLog(vertexShader_2, 512, NULL, infoLog_2);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog_2 << std::endl;
	}

	// Initialising & compiling fragment shader
	const unsigned int fragmentShader_2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_2, 1, &fragmentShaderSource_YELLOW, NULL);
	glCompileShader(fragmentShader_2);
	int successF_2;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successF_2);
	if(!successF_2)
	{
		char infoLogF_2[512];
		glGetShaderInfoLog(fragmentShader_2, 512, NULL, infoLogF_2);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogF_2 << std::endl;
	}

	// Create shader program
	unsigned int shaderProgram_2;
	shaderProgram_2 = glCreateProgram();
	glAttachShader(shaderProgram_2, vertexShader_2);
	glAttachShader(shaderProgram_2, fragmentShader_2);
	glLinkProgram(shaderProgram_2);

	int successP_2;
	glGetProgramiv(shaderProgram_2, GL_COMPILE_STATUS, &successP_2);
	if(!successP_2)
	{
		char infoLogP_2[512];
		glGetProgramInfoLog(fragmentShader, 512, NULL, infoLogP_2);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLogP_2 << std::endl;
	}

	glDeleteShader(vertexShader_2);
	glDeleteShader(fragmentShader_2);
	
	Shader s = Shader("shader/position_shader.vert", "shader/orange_shader.frag");
	
	while (!glfwWindowShouldClose(window)) {
		// input stufffff
		OpenGLStuff::processInput(window);

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glUseProgram(shaderProgram);
		s.use();
		glBindVertexArray(VAO);

		// drawing triangle without element buffer object
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glUseProgram(shaderProgram_2);
		// glBindVertexArray(VAO_2);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		
		// drawing square with element buffer object
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}