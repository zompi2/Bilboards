#pragma once

/**
* Billboards example.
*
* This is an engine class where the core application's mechanics
* are stored and processed.
*
* (c) 2015 Damian Nowakowski
*/

#include "inih/cpp/INIReader.h"

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW/glfw3.h>

/// Useful macros for easier data handling
// Define the simple getting engine using singletone
#define ENGINE			Engine::GetEngine()

// Define the simple engine initialization
#define ENGINE_INIT		Engine::Create(); \
						ENGINE->Init();

// Define the simple engine cleaning
#define ENGINE_CLEAN	Engine::Clean();

// Define the simple glfw window getting
#define WINDOW			ENGINE->window->glfwWindow

// Define the path to the configuration file
#define CONFIG_PATH		"Data/config.ini"

// Define the minimum update period (1/120 seconds)
#define UPDATE_PERIOD	(double)0.008333333

// Define the minimum render period (1/60 seconds)
#define RENDER_PERIOD	(double)0.016666667


// Predefine classes for visibility
class Scene;
class Window;

class Engine
{
public:

	INIReader*	config;	///< The configuration ini file reader
	Window*		window;	///< The glfw window (and opengl initializator)
	Scene*		scene;	///< The scene where all fun stuff happens

	/**
	* Get the engine instance (singleton).
	*/
	static Engine*	GetEngine();

	/**
	* Create the engine. Must be used first.
	*/
	static void Create();

	/**
	* Initialize the engine. Must be used after creation.
	* It can't be inside creation, because some objects needs the
	* already existing engine instance.
	*/
	void Init();

	/**
	* Clean the engine. Use it before tha application close.
	*/
	static void Clean();

	/**
	* Check if the engine is running. Best use to decide if
	* application has to exit.
	* @returns true if engine is running.
	*/
	bool IsRunning();

	/**
	* Stop the engine. Use it when client want to close the applictaion.
	*/
	void StopEngine();

	/**
	* Poll all engine events. Best use inside the main loop.
	*/
	void Poll();

	/**
	* Simple destructor
	*/
	~Engine();

private:

	/**
	* Method for updating all game
	* @param updateDeltaTime - the time of passed tick.
	*/
	void Update(double updateDeltaTime);

	/**
	* Method for drawing all game
	*/
	void Draw();

	static Engine* engine;	///< The handler of the engine instance
	bool isRunning;			///< Flag telling if the engine is running
	bool VSync;				///< Tells if VSync is on

	double prevTime;		///< Value of previous time used to calculating delta time

	double updateTimer;		///< Time of the one update tick
	double renderTimer;		///< Time of the one render tick	
};

