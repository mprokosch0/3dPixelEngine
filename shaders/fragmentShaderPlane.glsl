#version 330 core

flat in int faceID;

out vec4 FragColor;

void main()
{
    FragColor = vec4(0.66, 0.2, 0.2, 0.6);
}