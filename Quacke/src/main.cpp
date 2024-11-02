#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <stdio.h>

#include "ResourceManager.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "EnviromentEntity.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"
#include "Physics.hpp"
#include "Utilities.hpp"


#define IMGUI
#define PROFILING

#ifdef IMGUI
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#endif // IMGUI


bool wireframeRender = false;
bool pReleased = true;

bool start_app(GLFWwindow** window);
void frame_buffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Player& player);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

double lastX;
double lastY;
Camera camera;

#ifdef IMGUI
void imgui_init(GLFWwindow* window);
#endif // IMGUI


int main()
{
	GLFWwindow* window = nullptr;
	assert(start_app(&window) == true);

	Physics physics;
	physics.instance();

#ifdef IMGUI
	imgui_init(window);
#endif // IMGUI

	ResourceManager resourceManager;
	resourceManager.instance();
	resourceManager.instance().createModel("models/env2.obj");

	resourceManager.instance().createShader("textured", "shaders/TEXTURED.vert", "shaders/TEXTURED.frag");
	Shader textured = resourceManager.instance().getShader("textured");


	Player player;
	player.position.z = -2;
	player.position.y = 30;
	player.moveSpeed =20.0f;

	std::vector<Enemy> enemies;
	
	std::vector<EnviromentEntity> enviroment;
	enviroment.push_back(EnviromentEntity("textured", "models/env2.obj", "asd", 0, 100.1f, mVector3(0, -20., 0.), mVector3(0.0, 0.0, 0.0)));
	enviroment.push_back(EnviromentEntity("textured", "models/env2.obj", "asd", 0, 100.1f, mVector3(0, -20., 0.), mVector3(0.0, 0.0, 0.0)));
	enviroment.push_back(EnviromentEntity("textured", "models/env2.obj", "asd", 0, 100.1f, mVector3(0, -20., 0.), mVector3(0.0, 0.0, 0.0)));
	enviroment.push_back(EnviromentEntity("textured", "models/env2.obj", "asd", 0, 100.1f, mVector3(0, -20., 0.), mVector3(0.0, 0.0, 0.0)));

	double startofFrame = 0.0f;
	double endofFrame = 0.0f;
	double deltaTime = 0.0f;
	double timeSinceLast = 0.0;

#ifdef PROFILING
	double partTime = glfwGetTime();
	double inputTime = 0.0f;
	double updateTime = 0.0f;
	double renderTime = 0.0f;
	double IMGUIinputTime = 0.0f;
	double IMGUIupdateTime = 0.0f;
	double IMGUIrenderTime = 0.0f;
	double frameTime = 0.0f;
	double FPS = 0.0f;

	float sinceLastUpdate = 0.0f;
#endif // PROFILING
	
	Renderer renderer;
	renderer.instance();
	
	
	
	//////////********//////////
	//////////GAMELOOP//////////
	//////////********//////////
	while (!glfwWindowShouldClose(window))
	{
		startofFrame = glfwGetTime();
		timeSinceLast += deltaTime;

#ifdef PROFILING
		partTime = glfwGetTime();
#endif //PROFILING

		////*****////
		////INPUT//// 
		////*****////
		glfwPollEvents();
		processInput(window, player);


#ifdef IMGUI
#ifdef PROFILING
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::SetNextWindowSize(ImVec2(100, 100));
		ImGui::Text("FPS: %f",FPS);
		ImGui::Text("frameTime: %f",frameTime);
		ImGui::Text("inputTime: %f",IMGUIinputTime);
		ImGui::Text("updateTime: %f",IMGUIupdateTime);
		ImGui::Text("renderTime: %f",IMGUIrenderTime);
#endif
#endif // IMGUI & PORFILING		
#ifdef PROFILING
		inputTime = glfwGetTime() - partTime;
		partTime = glfwGetTime();
#endif // PORFILING
		

		////**********////
		////GAME LOGIC////
		////**********////	
		physics.instance().updatePhysics(player, enviroment, enemies, deltaTime);
		player.update(deltaTime);

		camera.update(deltaTime, player);
		
		//system("CLS");

		////*********////
		////RENDERING////
		////*********////
#ifdef PROFILING
		updateTime = glfwGetTime() - partTime;
		partTime = glfwGetTime();
#endif // PORFILING

		if (wireframeRender)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glClearColor(0.0f, 0.3f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = glm::mat4(1.0f); 
		view = camera.getView();
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(90.0f), (float)1280 / (float)720, 0.1f, 200.0f);
		textured.setMat4("projection", projection); 
		textured.setMat4("view", view);

		renderer.instance().render(enviroment);
		


#ifdef IMGUI
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif // IMGUI

		glfwSwapBuffers(window);



#ifdef PROFILING
		renderTime = glfwGetTime() - partTime;
#endif
		
		endofFrame = glfwGetTime();
		deltaTime = endofFrame - startofFrame;

#ifdef IMGUI
#ifdef PROFILING
		sinceLastUpdate += deltaTime;
		if (sinceLastUpdate > 1)
		{
			IMGUIinputTime = inputTime*1000;
			IMGUIupdateTime = updateTime * 1000;
			IMGUIrenderTime = renderTime * 1000;
			FPS = 1 / deltaTime;
			frameTime = deltaTime * 1000;
			sinceLastUpdate = 0;
		}
#endif
#endif // IMGUI & PORFILING
	}
	////*************////
	////ENDOFGAMELOOP////
	////*************////
	glfwTerminate();

#ifdef IMGUI
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif // IMGUI
	
	return 0;
}

bool start_app(GLFWwindow** window)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	*window = glfwCreateWindow(1280, 720, "Quacke", NULL, NULL);

	glfwMakeContextCurrent(*window);
	glfwSwapInterval(0);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "cannot init glad" << std::endl;
		return false;
	}
	glEnable(GL_DEPTH_TEST);


	glfwSetCursorPosCallback(*window, mouse_callback);
	glfwSetFramebufferSizeCallback(*window, frame_buffer_size_callback);
	return true;
}

void frame_buffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, Player& player)
{
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_TRUE)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_TRUE && pReleased)
	{
		if (wireframeRender)
			wireframeRender = false;
		else
			wireframeRender = true;
		pReleased = false;
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_FALSE)
	{
		pReleased = true;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		player.moveInput.z = 1.0f;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		player.moveInput.z = -1.0f;
	else 
		player.moveInput.z = 0.0f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		player.moveInput.x = 1.0f;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		player.moveInput.x = -1.0f;
	else 
		player.moveInput.x = 0.0f;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && player.character->canJump())
		player.character->jump();
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	double xpos = xposIn;
	double ypos = yposIn;

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.processMouse(xoffset, yoffset);
}


#ifdef IMGUI
void imgui_init(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
}
#endif // IMGUI