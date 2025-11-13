#version 330 core

flat in int faceID;

out vec4 FragColor;

void main()
{
    FragColor = vec4(0.5, 0.5, 0.5, 0.4);
}
