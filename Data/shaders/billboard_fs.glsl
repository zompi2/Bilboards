/**
 * Fragment shader used to draw a billboard.
 * (c) 2015 Damian Nowakowski
 */

#version 150
 
out vec4 outColor;

in vec2 outTexCoords;
uniform sampler2D tex;

void main(void)
{
	// Pass the color from the texture
	outColor = texture(tex, outTexCoords);
}
