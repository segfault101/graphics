#version 400 core

// page 40, 45

layout( location = 0 ) in vec4 vPosition;


void main()
{
	gl_Position = vPosition;

}