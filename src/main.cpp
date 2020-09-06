#include <iostream>
#include <vector>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Camera.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Cube.hpp"

int width = 800;
int height = 800;

bool trapCursor = true;

std::function<void(GLFWwindow*, float, float)> handleMouseCallback;

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
	width = w;
	height = h;
	glViewport(0, 0, w, h);
}

void CursorPosCallback(GLFWwindow* window, double x, double y)
{
	if (trapCursor)
		handleMouseCallback(window, x, y);
}

void KeyCallback(GLFWwindow* window, int key, int mode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		trapCursor = !trapCursor;
		glfwSetInputMode(window, GLFW_CURSOR, (trapCursor ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL));
		glfwSetCursorPos(window, width / 2, height / 2);
	}
}

void HandleKeyboard(GLFWwindow* window, Camera& cam, float frametime)
{
	static float movementSpeed = 4.5f;

	// Movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam.Move(cam.front * movementSpeed * frametime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.Move(-cam.front * movementSpeed * frametime);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.Move(-cam.right * movementSpeed * frametime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.Move(cam.right * movementSpeed * frametime);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cam.Move(glm::vec3(0.0f, 1.0f, 0.0f) * movementSpeed * frametime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cam.Move(-glm::vec3(0.0f, 1.0f, 0.0f) * movementSpeed * frametime);
}

void HandleMouse(GLFWwindow* window, Camera* cam, float x, float y)
{
	static const float sensitivity = 0.1f;

	static float pitch = 0.0f;
	static float yaw = -90.0f;

	pitch += (height / 2 - y) * sensitivity;
	yaw += (x - width / 2) * sensitivity;

	if (pitch > 89.0f)
		pitch = 89.0f;
	else if (pitch < -89.0f)
		pitch = -89.0f;

	cam->SetRotation(glm::vec2(pitch, yaw));
	
	glfwSetCursorPos(window, width / 2.0f, height / 2.0f);
}

int main(int argc, char** argv)
{
	// Initialize ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	// Initialize GLFW
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

	// Load OpenGL Bindings
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Finally initialize ImGui
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
	ImGui::StyleColorsDark();

	PrintVersionInfo();

	// Set Viewport  and callbacks
	glViewport(0, 0, 800, 800);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	Shader cubeShader("cube.vert", "cube.frag");
	cubeShader.Use();

	glm::mat4 perspective = glm::mat4(1.0f);

	Texture cubeTexture("crate.jpg");
	cubeShader.SetUniformInt("lauch", 0);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -7.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, 6.3f),
		glm::vec3(2.4f, -0.4f, 3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, 2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, 1.5f)
	};

	std::vector<Cube*> cubes;
	for (int i = 0; i < 10; i++)
	{
		Cube* newCube = new Cube(cubePositions[i], glm::vec3(0.5f));
		newCube->Rotate(glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));

		cubes.push_back(newCube);
	}

	// A camera
	Camera cam(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec2(0.0f, -90.0f));

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, width / 2, height / 2);
	handleMouseCallback = std::bind(HandleMouse, std::placeholders::_1, &cam, std::placeholders::_2, std::placeholders::_3);
	glfwSetCursorPosCallback(window, CursorPosCallback);
	glfwSetKeyCallback(window, KeyCallback);

	glEnable(GL_DEPTH_TEST);


	float lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		float currentTime = glfwGetTime();
		HandleKeyboard(window, cam, currentTime - lastTime);
		lastTime = currentTime;

		float t = glfwGetTime();

		static float PI = glm::pi<float>();

		static float fov = glm::radians(45.0f);
		static float zNear = 0.1f;
		static float zFar = 100.0f;

		static float orbitSpeed = 1.0f;
		static float orbitRadius = 10.0f;
		
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

		ImGui::End();

		perspective = glm::perspective(fov, (float)width/(float)height, zNear, zFar);

		cubeTexture.Bind();
		cubeShader.Use();
		cubeShader.SetUniformMat4("projection", &perspective[0][0]);
		cam.Use(cubeShader);

		for (Cube* cube : cubes)
			cube->Draw(cubeShader);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);

	return 0;
}