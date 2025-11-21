#version 330 core

flat in int faceID;
uniform float colorPickR;
uniform float colorPickG;
uniform float colorPickB;
uniform float colorR;
uniform float colorG;
uniform float colorB;

out vec4 FragColor;

void main()
{
    if (colorPickB < 0 && colorPickG < 0 && colorPickR < 0)
    {
        if (colorB < 0 && colorG < 0 && colorR < 0)
            FragColor = vec4(0.3, 0.3, 0.3, 0.7);
        else
            FragColor = vec4(colorR, colorG, colorB, 0.7);
    }
    else
        FragColor = vec4(colorPickR, colorPickG, colorPickB, 1);
}
