/**
 * Geometry shader used to draw a billboard from a single point.
 * (c) 2015 Damian Nowakowski
 */

#version 150

layout( points ) in;
layout( triangle_strip, max_vertices = 4 ) out;

uniform mat4 viewProjectionMatrix;
uniform vec2 size;

in vec4 inoutPosition[1];

out vec2 outTexCoords;

void main()
{
	// Calculate the screen position of the marker using ViewProjection matrix
	vec4 center = viewProjectionMatrix*inoutPosition[0];	

	// Get the half length of the edge of the billboard so it can be drawn
	// from the center.
	vec2 dir = size * 0.5;

	/// Emit all 4 vertices of the square billboard.
	/// They will always be in front of the camera because they will be set
	/// based on the transformed center and just drawn in front of the camera.
	/// Also set the texture uv coordinates to draw the whole texture on it.

	// [ ][x]
	// [ ][ ]
	gl_Position = vec4( center.x+dir.x, center.y+dir.y, center.z, center.w );
	outTexCoords = vec2(1,0);
	EmitVertex();
	
	// [x][ ]
	// [ ][ ]
	gl_Position = vec4( center.x-dir.x, center.y+dir.y, center.z, center.w );
	outTexCoords = vec2(0,0);
	EmitVertex();
	
	// [ ][ ]
	// [ ][x]
	gl_Position = vec4( center.x+dir.x, center.y-dir.y, center.z, center.w );
	outTexCoords = vec2(1,1);
	EmitVertex();
	
	// [ ][ ]
	// [x][ ]
	gl_Position = vec4( center.x-dir.x, center.y-dir.y, center.z, center.w );
	outTexCoords = vec2(0,1);
	EmitVertex();

	/// Finally emit the whole square.
	EndPrimitive();
}
