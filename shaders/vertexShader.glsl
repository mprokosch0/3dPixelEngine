#version 330 core
layout(location=0) in vec3 aPos;

uniform mat4 locModel;
uniform mat4 wModel;
uniform mat4 projection;
uniform mat4 camera;

flat out int faceID;
out vec2 TexCoords;

void main()
{
	mat4 model = wModel * locModel;
	gl_Position = projection * camera * model * vec4(aPos, 1.0);

	faceID = gl_VertexID / 3;
}