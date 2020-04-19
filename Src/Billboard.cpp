/**
 * Billboards example.
 *
 * This is a billboard class. It handles its creation and rendering.
 *
 * (c) 2015 Damian Nowakowski
 */

#include "Billboard.h"
#include "Shaders.h"
#include "Engine.h"
#include "Scene.h"
#include "Window.h"
#include "Camera.h"

#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

/**
 * Simple constructor with initialization
 */
Billboard::Billboard()
{
	// Remember the configuration reader so we can use it in future.
	INIReader * localINIReader = ENGINE->config;

	/// Remember the position of the center of the billboard on scene.
	position =		glm::vec3(	localINIReader->GetReal("Billboard", "Pos_X", 0.0), 
								localINIReader->GetReal("Billboard", "Pos_Y", 0.0),
								localINIReader->GetReal("Billboard", "Pos_Z", 0.0));

	// The Y scale is multiplied by the camera ratio, because the billboard is made using the  geometry shader 
	// and it won't pass the ViewProjection matrix to all verticies.
	// Without the ratio in scale the billboard won't have the correct, square, size.
	size = glm::vec2(	localINIReader->GetReal("Billboard", "Size", 1.0), 
						ENGINE->scene->camera->GetRatio()*localINIReader->GetReal("Billboard", "Size", 1.0));

	/// Create the shader that will be used to render the billboard
	Shaders::AttachShader(shader, GL_VERTEX_SHADER, "data/shaders/billboard_vs.glsl");
	Shaders::AttachShader(shader, GL_GEOMETRY_SHADER, "data/shaders/billboard_gs.glsl");
	Shaders::AttachShader(shader, GL_FRAGMENT_SHADER, "data/shaders/billboard_fs.glsl");
	Shaders::LinkProgram(shader);

	// Remember the location of vertex position in shader program
	vertex_loc	= glGetAttribLocation(shader, "inPosition");

	// Generate all necessary buffors for shader
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	/// Fill the buffer with the vertex data.
	/// Only one point is needed, bedause the whole billboard will be generated in geometry shader.
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glVertexAttribPointer(vertex_loc, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glBufferData(GL_ARRAY_BUFFER, sizeof(position), glm::value_ptr(position), GL_STATIC_DRAW);
		glEnableVertexAttribArray(vertex_loc);

	glBindVertexArray(0);

	/// Load the image into the billboard's texture.
	LoadImageFile(localINIReader->Get("Billboard", "Path", "").c_str());
}

/**
 * Load the image file into the texture.
 * @param filePath - the path to the file.
 */
void Billboard::LoadImageFile(const char * filePath)
{
	ILuint image;

	ilGenImages(1, &image);
	glGenTextures(1, &texture);

	ilBindImage(image);

	if (ilLoadImage(filePath))
	{
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH),
			ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE,
			ilGetData());

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
		ilBindImage(0);
	}
	
	ilDeleteImages(1, &image);
}

/**
 * Draw the point light marker (to see where is the source)
 */
void Billboard::Draw()
{
	// Get the view projection matrix from camera. It will be used for proper transformation of the billboard.
	glm::mat4 viewProjectionMatrix	= ENGINE->scene->camera->GetViewProjectionMatrix();
	
	/// Draw the billboard using given view projection matrix, position, size and the texture.
	/// We do not translate the position by the model matrix, because it has only one point position and it can
	/// be pass originally.
	glUseProgram(shader);

		glUniformMatrix4fv(glGetUniformLocation(shader, "viewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix));
		glUniform2fv(glGetUniformLocation(shader, "size"), 1, glm::value_ptr(size));
		glUniform1i(glGetUniformLocation(shader, "tex"), 0);

		glBindTexture(GL_TEXTURE_2D, texture);

		glBindVertexArray(VAO);
			glDrawArrays(GL_POINTS, 0, 1);
		glBindVertexArray(0);

		glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(0);
}

/**
 * Simple destructor clearing all data.
 */
Billboard::~Billboard()
{
	Shaders::DeleteShaders(shader);
	glDeleteProgram(shader);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &texture);
}
