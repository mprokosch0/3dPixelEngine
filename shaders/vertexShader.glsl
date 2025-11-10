#version 330 core
layout(location=0) in vec3 aPos;

uniform mat4 rotX;
uniform mat4 rotY;
uniform mat4 rotZ;
uniform mat4 wRotX;
uniform mat4 wRotY;
uniform mat4 wRotZ;
uniform mat4 scale;
uniform mat4 projection;
uniform mat4 camera;
uniform mat4 translate;

flat out int faceID;
out vec2 TexCoords;

void main()
{
	mat4 model = wRotX * wRotY * wRotZ * translate * rotX * rotY * rotZ * scale;
	gl_Position = projection * camera * model * vec4(aPos, 1.0);

	faceID = gl_VertexID / 3;
}