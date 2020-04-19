#pragma once

/**
* Billboards example.
*
* This is a scene class. It contains all elements displaying on the scene.
*
* (c) 2015 Damian Nowakowski
*/

#include "Engine.h"

// Predefine classes for visibility
class Camera;
class Billboard;

class Scene
{
public:
	/**
	* Simple destructor
	*/
	~Scene();

	float			bgColor[4];		///< Background color used in clearing scene (RGBA).

	Camera*			camera;			///< Handler of the camera in the scene.
	Billboard*		billboard;		///< Handler of the billboard in the scene.

	/**
	* Initialize the scene
	* It can't be used in constructor because many objects created inside the scene
	* needs the reference to itself.
	*/
	void Init();

	/**
	* Update the scene in this tick.
	* @param deltaTime - the time of passed tick.
	*/
	void OnRun(double deltaTime);

	/**
	* Draw whole scene.
	*/
	void OnDraw();	
};
