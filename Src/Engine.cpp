/**
* Billboards example.
*
* This is an engine class where the core application's mechanics
* are stored and processed.
*
* (c) 2015 Damian Nowakowski
*/

#include <IL/il.h>
#include "Engine.h"
#include "Scene.h"
#include "Window.h"

// Set the default value of instance pointer to avoid memory ridings
Engine * Engine::engine = NULL;

/**
* Definition of key listener inside the engine that is listening for
* the Esc button. The Esc button stops the engine and thus the application
* starts to nicely close.
*/
void OnKey(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		ENGINE->StopEngine();
	}
}

/**
* Get the engine instance (singleton).
*/
Engine * Engine::GetEngine()
{
	return engine;
}

/**
* Create the engine. Must be used first.
*/
void Engine::Create()
{
	if (engine == NULL)
	{
		engine = new Engine();
	}
}

/**
* Initialize the engine. Must be used after creation.
* It can't be inside creation, because some objects needs the
* already existing engine instance.
*/
void Engine::Init()
{
	// Create a config reader with configuration ini file so it can be used in future
	config = new INIReader(CONFIG_PATH);

	// Create and initialize window.
	// If window cannot be created stop the engine.
	// Init is not inside a constructor because it has to return a value.
	window = new Window();
	if (window->Init() == false)
	{
		StopEngine();
		return;
	}

	// Initialize the DevIL library.
	ilInit();

	// Create and init the scene with all objects inside.
	// Init cannot be inside constructor, because many objects
	// inside scene needs an access to scene during creation.
	scene = new Scene();
	scene->Init();

	// Set the callback for key action (listening to Esc to close an application)
	glfwSetKeyCallback(window->glfwWindow, OnKey);

	// Remember the time for calculating the tick time
	prevTime = glfwGetTime();

	// Set the initial values for timers
	updateTimer = 0;
	renderTimer = 0;

	// Get information about VSync and turn it off if it's false
	// (it is turned on by default)
	VSync = config->GetBoolean("System", "VSync", true);
	if (VSync == false)
	{
		glfwSwapInterval(0);
	}

	// Say that engine is currently running
	isRunning = true;
}

/**
* Clean the engine. Use it before tha application close.
*/
void Engine::Clean()
{
	if (engine != NULL)
	{
		delete engine;
		engine = NULL;
	}
}

/**
* Check if the engine is running. Best use to decide if
* application has to exit.
* @returns true if engine is running.
*/
bool Engine::IsRunning()
{
	return engine && isRunning;
}

/**
* Stop the engine. Use it when client want to close the applictaion.
*/
void Engine::StopEngine()
{
	isRunning = false;
}

/**
* Poll all engine events. Best use inside the main loop.
*/
void Engine::Poll()
{
	// Calculate the one tick time
	double time = glfwGetTime();
	double deltaTime = time - prevTime;

	// Increment timers with the one tick time
	updateTimer += deltaTime;
	renderTimer += deltaTime;

	/// The following conditions are for updating and rendering the application
	/// only when it is necessary. No more than their periods.
	// When it is time for an update:
	if (updateTimer >= UPDATE_PERIOD)
	{
		// Update it as many times as the update periods passed 
		// from the previous tick.
		double updateDeltaTime = 0;
		while (updateTimer >= UPDATE_PERIOD)
		{
			updateDeltaTime += UPDATE_PERIOD;
			updateTimer -= UPDATE_PERIOD;
		}
		Update(updateDeltaTime);
	}

	// When VSync is off just render
	if (VSync == false)
	{
		Draw();
	}
	else
	{
		// When it is time for render
		if (renderTimer >= RENDER_PERIOD)
		{
			// Just render it once and set remaining render time.
			while (renderTimer > RENDER_PERIOD)
			{
				renderTimer -= RENDER_PERIOD;
			}
			Draw();
		}
	}

	// Remember current time for calculating next tick time.
	prevTime = time;
}

/**
* Method for updating all game
* @param updateDeltaTime - the time of passed tick.
*/
void Engine::Update(double updateDeltaTime)
{
	// Update scene
	scene->OnRun(updateDeltaTime);

	// Poll every glfw events
	glfwPollEvents();
}

/**
* Method for drawing all game
*/
void Engine::Draw()
{
	// Draw scene
	scene->OnDraw();

	// At the end flush opengl and swap buffers.
	glFlush();
	glfwSwapBuffers(window->glfwWindow);
}

/**
* Simple destructor
*/
Engine::~Engine()
{
	delete config;
	delete window;
	delete scene;
}