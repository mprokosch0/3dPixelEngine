#version 330 core

flat in int faceID;
uniform float colorPickR;
uniform float colorPickG;
uniform float colorPickB;

out vec4 FragColor;

void main()
{
    if (colorPickB == 0 && colorPickG == 0 && colorPickR == 0)
        FragColor = vec4(0.5, 0.5, 0.5, 0.6);
    else
        FragColor = vec4(colorPickR, colorPickG, colorPickB, 1);
}
