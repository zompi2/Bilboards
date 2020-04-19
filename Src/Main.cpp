/**
 * Billboards example.
 *
 * This is the main file of Billboards example.
 *
 * (c) 2015 Damian Nowakowski
 */

#include "Engine.h"

/**
 * Start the application.
 */
int main()
{
	// Init application engine so it can run
	ENGINE_INIT

	// As long as the engine is running update it
	while (ENGINE->IsRunning() == true)
	{
		ENGINE->Poll();
	}

	// When engine has been stopped clear the memory
	ENGINE_CLEAN

	// Exit application with no errors
	exit(EXIT_SUCCESS);
	return 0;
}
