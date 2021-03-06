/**
* Billboards example.
*
* This is a scene class. It contains all elements displaying on the scene.
*
* (c) 2015 Damian Nowakowski
*/

#include "Scene.h"
#include "Window.h"
#include "Camera.h"
#include "Billboard.h"
#include "Shaders.h"

/**
* Initialize the scene
* It can't be used in constructor because many objects created inside the scene
* needs the reference to itself.
*/
void Scene::Init()
{
	// Remember the configuration reader so we can use it in future.
	INIReader * localINIReader = ENGINE->config;

	/// Get the background color (the clear color) from the configuration ini file
	bgColor[0] = GLfloat(localINIReader->GetReal("Render", "ClearColor_R", 0));
	bgColor[1] = GLfloat(localINIReader->GetReal("Render", "ClearColor_G", 0));
	bgColor[2] = GLfloat(localINIReader->GetReal("Render", "ClearColor_B", 0));
	bgColor[3] = GLfloat(localINIReader->GetReal("Render", "ClearColor_A", 1));

	/// Create all objects that are on scene
	camera		= new Camera();
	billboard	= new Billboard();

	// Set the proper viewport
	glViewport(0, 0, camera->renderWidth, camera->renderHeight);
}

/**
* Update the scene in this tick.
* @param deltaTime - the time of passed tick.
*/
void Scene::OnRun(double deltaTime)
{
	// When there was input in camera update it
	if (camera->HandleInput() == true)
	{
		camera->Update((float)deltaTime);
	}
}

/**
* Draw whole scene.
*/
void Scene::OnDraw()
{
	glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	billboard->Draw();
}

/**
* Simple destructor clearing all data.
*/
Scene::~Scene()
{
	delete camera;
	delete billboard;
}