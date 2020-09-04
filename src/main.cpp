#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Shader.hpp"
#include "Texture.hpp"
#include "Cube.hpp"

void LogGlfwError(const char* message)
{
	const char* error;
	int code = glfwGetError(&error);
	std::cerr << message << std::endl
		<< "(" << code << ") " << error << std::endl;
}

void PrintVersionInfo()
{
	int glfwMajor, glfwMinor, glfwRev;
	glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRev);

	const char* vendor		= (const char*)glGetString(GL_VENDOR);
	const char* renderer	= (const char*)glGetString(GL_RENDERER);
	const char* version		= (const char*)glGetString(GL_VERSION);
	const char* glslVersion	= (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	const char* extensions	= (const char*)glGetString(GL_EXTENSIONS);

	std::cout << "Using GLFW " << glfwMajor << "." << glfwMinor << "." << glfwRev << std::endl;
	std::cout << "GPU Vendor: " << vendor << std::endl;
	std::cout << "GPU Model: " << renderer << std::endl;
	std::cout << "OpenGL Version: " << version << std::endl;
	std::cout << "GLSL Version: " << glslVersion << std::endl;
	if (extensions != nullptr)
		std::cout << "Loaded extensions: " << extensions << std::endl;
	std::cout << "----------------------------------------" << std::endl;
}

void FramebufferSizeCallback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

int main(int argc, char** argv)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	int success;
	success = glfwInit();
	if (!success)
	{
		LogGlfwError("Failed to initialize GLFW");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window;
	window = glfwCreateWindow(800, 800, "OpenGL Test", NULL, NULL);
	if (window == nullptr)
	{
		LogGlfwError("Failed to create GLFWwindow");
		return -1;
	}

	glfwMakeContextCurrent(window);

	ImGui_ImplGlfw_InitForOpenGL(window, true);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

	ImGui::StyleColorsDark();

	PrintVersionInfo();

	glViewport(0, 0, 800, 800);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	/*
	Shader shader("basic.vert", "basic.frag");
	Texture texture1("lauch.jpg");
	Texture texture2("tomato.jpg");

	shader.Use();
	shader.SetUniformInt("texture1", 0);
	shader.SetUniformInt("texture2", 1);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.f, -0.7f, 0.f));
	model = glm::rotate(model, glm::radians(-55.f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.f), 1.f, 0.1f, 100.0f);

	shader.SetUniformMat4("model", glm::value_ptr(model));
	shader.SetUniformMat4("view", glm::value_ptr(view));
	shader.SetUniformMat4("projection", glm::value_ptr(projection));

	float vertices[4 * (3 + 3 + 2)] = {
		// Position				//Color			// Texture
		-0.5f,  0.5f, 1.0f,		0.3f, 1.0f, 0.6f,	0.0f, 1.0f,
		 0.5f,  0.5f, 1.0f,		0.8f, 0.1f, 0.5f,	1.0f, 1.0f,
		 0.5f, -0.5f, 1.0f,		0.5f, 0.6f, 0.2f,	1.0f, 0.0f,
		-0.5f, -0.5f, 1.0f,		0.2f, 0.7f, 0.8f,	0.0f, 0.0f,
	};

	unsigned int indices[2 * 3] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 3 + 2) * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (3 + 3 + 2) * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (3 + 3 + 2) * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	*/

	Shader cubeShader("cube.vert", "cube.frag");
	Texture cubeTexture("crate.jpg");
	cubeShader.Use();

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 view = glm::mat4(1.0f);

	glm::mat4 perspective = glm::mat4(1.0f);

	cubeShader.SetUniformMat4("model", glm::value_ptr(model));
	cubeShader.SetUniformMat4("view", glm::value_ptr(view));

	cubeShader.SetUniformInt("lauch", 0);

	Cube cube(0.0f, 0.0f, 0.0f, 0.5f);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		float t = glfwGetTime();
		static float fov = glm::radians(45.0f);
		static float zNear = 0.1f;
		static float zFar = 100.0f;
		static float camX = 0.0f;
		static float camY = 0.0f;
		static float camZ = -3.0f;
		static float yaw = 0.0f;
		static float pitch = 0.0f;
		static float roll = 0.0f;
		//model = glm::rotate(model, glm::radians(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

		glClearColor(0.1f, 0.4f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Render ImGui
		ImGui::Begin("Rendering Controls");

		if (ImGui::CollapsingHeader("Projection"))
		{
			ImGui::SliderAngle("FOV", &fov, 10.0f, 120.0f, "%.0f°");
			ImGui::SliderFloat("zNear", &zNear, 0.1f, 10.0f);
			ImGui::SliderFloat("zFar", &zFar, 10.0f, 100.0f);
		}

		if (ImGui::CollapsingHeader("View"))
		{
			ImGui::SliderFloat("CamX", &camX, -2.0f, 2.0f);
			ImGui::SliderFloat("CamY", &camY, -2.0f, 2.0f);
			ImGui::SliderFloat("CamZ", &camZ, -10.0f, 0.0f);
			ImGui::Separator();
			ImGui::SliderAngle("Yaw", &yaw, -45.0f, 45.0f, "%.0f°");
			ImGui::SliderAngle("Pitch", &pitch, -45.0f, 45.0f, "%.0f°");
			ImGui::SliderAngle("Roll", &roll, -45.0f, 45.0f, "%.0f°");
		}

		ImGui::End();

		perspective = glm::perspective(fov, 1.0f, zNear, zFar);
		view = glm::mat4(1.0f);
		view = glm::rotate(view, yaw, glm::vec3(0.f, 1.f, 0.f));
		view = glm::rotate(view, pitch, glm::vec3(1.f, 0.f, 0.f));
		view = glm::rotate(view, roll, glm::vec3(0.f, 0.f, 1.f));
		view = glm::translate(view, glm::vec3(camX, camY, camZ));

		cubeTexture.Bind();
		cubeShader.Use();
		cubeShader.SetUniformMat4("projection", &perspective[0][0]);
		cubeShader.SetUniformMat4("view", &view[0][0]);

		for (int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));

			cubeShader.SetUniformMat4("model", &model[0][0]);
			cube.Draw(cubeShader);
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);

	return 0;
}