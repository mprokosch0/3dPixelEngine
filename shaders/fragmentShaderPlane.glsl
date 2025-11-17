#version 330 core

flat in int faceID;
uniform int uline;
uniform float colorPickR;
uniform float colorPickG;
uniform float colorPickB;

out vec4 FragColor;

void main()
{
    if (uline == 0)
    {
        if (colorPickB == 0 && colorPickG == 0 && colorPickR == 0)
            FragColor = vec4(0.66, 0.2, 0.2, 0.6);
        else
            FragColor = vec4(colorPickR, colorPickG, colorPickB, 1);
    }
    else if (uline == 1)
    {
        FragColor = vec4(1, 1, 1, 1);
    }
    else
    {
        FragColor = vec4(1, 1, 0, 1);
    }
}