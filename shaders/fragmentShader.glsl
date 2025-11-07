#version 330 core

flat in int faceID;

out vec3 FragColor;

void main()
{
    if (faceID % 3 == 0)
        FragColor = vec3(1.0, 1.0, 1.0);
    else if (faceID % 3 == 1)
        FragColor = vec3(0.6, 0.6, 0.6);
    else
        FragColor = vec3(0.3, 0.3, 0.3);
}
