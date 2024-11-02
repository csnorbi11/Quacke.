#ifndef QUACKE
#define QUACKE

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <stdio.h>


#include "AssetManager.hpp"
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
#pragma warning(push, 0)
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#pragma warning(pop)
#endif // IMGUI

#endif // !QUACKE



