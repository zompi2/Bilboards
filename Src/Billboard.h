#pragma once

/**
 * Billboards example.
 *
 * This is a billboard class. It handles its creation and rendering.
 *
 * This file is a part of a project from http://zompi.pl/billboards-with-geometry-shader/
 * (c) 2015 Damian Nowakowski
 */

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <IL/il.h>

class Billboard
{
public:

	/**
	 * Simple constructor and destructor.
	 */
	Billboard();
	~Billboard();

	glm::vec3 position;		///< Position of the center of the billboard.

	/**
	 * Draw the billboard.
	 */
	void Draw();

private:

	GLuint shader;		///< Handler of the shader that draws light marker.
	GLuint texture;		///< Handler of the texture used in billboard.

	GLuint VAO;			///< Vertex array object needed for shader.
	GLuint VBO;			///< Vertex buffer object needed for shader.
	GLuint vertex_loc;	///< Vertex pointer needed for shader.

	glm::vec2 size;		///< The normalized size of the billboard.

	/**
	 * Load the image file into the texture.
	 * @param filePath - the path to the file.
	 */
	void LoadImageFile(const char * filePath);
};

