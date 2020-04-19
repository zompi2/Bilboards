/**
 * Vertex shader used to draw a billboard.
 * (c) 2015 Damian Nowakowski
 */

#version 150

in vec3 inPosition;
out vec4 inoutPosition;

void main()
{
	// Just pass the position to the geometry shader.
	inoutPosition = vec4(inPosition,1);
}