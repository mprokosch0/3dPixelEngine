#version 330 core

flat in int faceID;
uniform int uline;
out vec4 FragColor;

void main()
{
    if (uline == 0)
    {
        FragColor = vec4(0.66, 0.2, 0.2, 0.6);
    }
    else
    {
        FragColor = vec4(1, 1, 1, 1);
    }
}