#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow* window);

int main2() {
	
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

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Information for OpenGL to translate internal coordinates to screen coordinates
	// (Internal OpenGL Coordinates go from -1 to 1)
	glViewport(0, 0, 800, 600);

	// Everytime the window gets resized, GLFW executes the callback to give the OpenGL context the new information
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// The vertices of the first triangle
	float verticesTriangle[] = {
		-0.5f, -0.5f,  0.0f, // lower left
		 0.5f, -0.5f,  0.0f, // lower right
		 0.0f,  0.5f,  0.0f  // up
	};

	float verticesTriangleWithColor[] = {
		-0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, // lower left , red
		 0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, // lower right, green
		 0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // up, blue
	};
	
	float twoTrianglesVertices[] = {
		-0.5f, -0.5f,  0.0f,  // 1 - lower left
		 0.5f, -0.5f,  0.0f,  // 1 - lower right
		 0.0f,  0.5f,  0.0f,  // 1 - up
		-0.5f, -1.5f,  0.0f,  // 2 - lower left
		 0.5f, -1.5f,  0.0f,  // 2 - lower right
		 0.0f, -0.5f,  0.0f   // 2 - up
	};

	// vertices with position, color and texCoordinates
	float squareVertices[] = {
		-0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 2.0f, // Upper left  / blue		/ Upper left 
		 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	2.0f, 2.0f, // upper right / red		/ upper right
		-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f, // lower left  / green		/ lower left
		 0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	2.0f, 0.0f  // lower right / blue		/ lower right
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
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangle), verticesTriangle, GL_STATIC_DRAW);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangleWithColor), verticesTriangleWithColor, GL_STATIC_DRAW);
	
	//glBufferData(GL_ARRAY_BUFFER, sizeof(twoTrianglesVertices), twoTrianglesVertices, GL_STATIC_DRAW);

	
	// draw square using element buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
	unsigned int ebo_id;
	glGenBuffers(1, &ebo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	

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
	
	
	// LOAD TEXTURES BABYYYYY
	int width, height, nr_channels;
	unsigned char * data = stbi_load("textures/container.jpg", &width, &height, &nr_channels, 0);

	unsigned int texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	//glActiveTexture(GL_TEXTURE0);
	

	int width2, height2, nr_channels2;
	stbi_set_flip_vertically_on_load(true);
	unsigned char * data2 = stbi_load("textures/test.jpg", &width2, &height2, &nr_channels2, 0);
	unsigned int texture2_id;
	glGenTextures(1, &texture2_id);
	glBindTexture(GL_TEXTURE_2D, texture2_id);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
	glGenerateMipmap(GL_TEXTURE_2D);

	
	//glActiveTexture(GL_TEXTURE1);
	
	
	stbi_image_free(data);
	stbi_image_free(data2);

	//Shader s = Shader("shader/position_shader.vert", "shader/orange_shader.frag");
	//Shader s = Shader("shader/position_shader.vert", "shader/uniform_color_shader.frag");
	//Shader s = Shader("shader/position_color_shader.vert", "shader/input_color_shader.frag");
	
	Shader s = Shader(
		"shader/position_color_texcoords_shader.vert",
		"shader/input_color_sampler2D_shader.frag");
	
	Shader s2 = Shader("shader/position_shader.vert", "shader/yellow_shader.frag");

	
	// USE SHADER BEFORE CHANGING / INITIALISING UNIFORMS!!!!!! AAARGHH
	s.use();
	const char * a = "texture1";
	s.setInt(a, 0);
	const char * b = "texture2";
	s.setInt(b, 1);
	
	float time;
	float redValue;

	float box_amount = 0.5f;
	const char * c = "amount";



	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);

	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 1.0f));
	vec = trans * vec;


	
	while (!glfwWindowShouldClose(window)) {
		// input stufffff
		processInput(window);

		if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			box_amount = box_amount - 0.1f;
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			box_amount = box_amount + 0.1f;
		}
		
		if(box_amount < 0.0f) {box_amount = 0.0f;}
		if(box_amount > 1.0f) {box_amount = 1.0f;}
		
		glClearColor(0.38f, 0.38f, 0.38f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2_id);
		
		s.use();

		s.setFloat(c, box_amount);

		time = glfwGetTime();
		redValue = (sin(time) / 2.0f) + 0.5f;
		const char * t = "ourColor";
		//s.set4f(t, redValue, 0.0f, 0.0f, 1.0f);

		
		glBindVertexArray(vao_id);

		// drawing triangle without element buffer object
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		 //s2.use();
		 //glBindVertexArray(vao_2_id);
		 //glDrawArrays(GL_TRIANGLES, 0, 3);
		
		// drawing square with element buffer object
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
