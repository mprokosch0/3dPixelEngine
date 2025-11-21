#version 330 core

flat in int faceID;
uniform int uline;
uniform int selected;
uniform float colorPickR;
uniform float colorPickG;
uniform float colorPickB;
uniform float colorR;
uniform float colorG;
uniform float colorB;

out vec4 FragColor;

void main()
{
    float alpha = (selected == 1) ? 0.5 : 1;
    if (uline == 0)
    {
        if (colorPickB < 0 && colorPickG < 0 && colorPickR < 0)
        {
            if (colorB < 0 && colorG < 0 && colorR < 0)
            {
                if (faceID % 3 == 0)
                    FragColor = vec4(1.0, 1.0, 1.0, alpha);
                else if (faceID % 3 == 1)
                    FragColor = vec4(0.6, 0.6, 0.6, alpha);
                else
                    FragColor = vec4(0.3, 0.3, 0.3, alpha);
            }
            else
                FragColor = vec4(colorR, colorG, colorB, alpha);
        }
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
