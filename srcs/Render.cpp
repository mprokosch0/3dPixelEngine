#include "Render.hpp"

float	Render::_angleX = 0;
float	Render::_angleY = 0;
float	Render::_angleZ = 0;
float	Render::_tX = 0;
float	Render::_tY = 0;
float	Render::_tZ = 0;
GLuint	Render::_frameBuffer = 0;

//constructors/destructors---------------------------------

Render::Render(void) {}

Render::~Render(void) {}

//Member functions-----------------------------------------

void	Render::rotate_y(float *mat)
{
	float cosA = cosf(_angleX);
	float sinA = sinf(_angleX);
	mat[0]  = cosA; mat[1]  = 0; mat[2]  = -sinA; mat[3]  = 0;
	mat[4]  = 0;    mat[5]  = 1; mat[6]  = 0;     mat[7]  = 0;
	mat[8]  = sinA; mat[9]  = 0; mat[10] = cosA;  mat[11] = 0;
	mat[12] = 0;    mat[13] = 0; mat[14] = 0;     mat[15] = 1;
}

void	Render::rotate_x(float *mat)
{
	float cosA = cosf(_angleY);
	float sinA = sinf(_angleY);
	mat[0]  = 1; mat[1]  = 0;    mat[2]  = 0;	  mat[3]  = 0;
	mat[4]  = 0; mat[5]  = cosA; mat[6]  = -sinA; mat[7]  = 0;
	mat[8]  = 0; mat[9]  = sinA; mat[10] = cosA;  mat[11] = 0;
	mat[12] = 0; mat[13] = 0;	 mat[14] = 0;     mat[15] = 1;
}

void	Render::rotate_z(float *mat)
{
	float cosA = cosf(_angleZ);
	float sinA = sinf(_angleZ);
	mat[0]  = cosA; mat[1]  = -sinA; mat[2]  = 0; mat[3]  = 0;
	mat[4]  = sinA; mat[5]  = cosA;  mat[6]  = 0; mat[7]  = 0;
	mat[8]  = 0;	mat[9]  = 0;	 mat[10] = 1;  mat[11] = 0;
	mat[12] = 0;	mat[13] = 0;	 mat[14] = 0;     mat[15] = 1;
}

void	Render::project_points(float *mat)
{
	float	ratio = (float)Opengl::getWidth() / (float)Opengl::getHeight();
	float	fov = 90.0f * (M_PI / 180);
	float	near = 0.1f;
	float	far = 1000.0f;
	float t = tanf(fov / 2.0f);

	mat[0]  = 1 / (ratio * t); mat[1]  = 0;		mat[2]  = 0;								mat[3]  = 0;
	mat[4]  = 0;    		   mat[5]  = 1 / t;	mat[6]  = 0;								mat[7]  = 0;
	mat[8]  = 0;			   mat[9]  = 0;		mat[10] = -(far + near) / (far - near);		mat[11] = -1;
	mat[12] = 0;    		   mat[13] = 0;		mat[14] = -2 * far * near / (far - near);	mat[15] = 0;
}

void	Render::project_pointsOrth(float *mat)
{
	mat[0]  = 2.0f / Opengl::getWidth();	mat[1]  = 0;						mat[2]  = 0;	mat[3]  = 0;
	mat[4]  = 0;						mat[5]  = 2.0f / Opengl::getHeight();	mat[6]  = 0;	mat[7]  = 0;
	mat[8]  = 0;						mat[9]  = 0;						mat[10] = -1;	mat[11] = 0;
	mat[12] = -1;						mat[13] = -1;						mat[14] = 0;	mat[15] = 1;
}

void Render::identityMat4(float *mat)
{
    mat[0] = 1;  mat[1] = 0; mat[2] = 0;  mat[3] = 0;
    mat[4] = 0;  mat[5] = 1; mat[6] = 0;  mat[7] = 0;
    mat[8] = 0;  mat[9] = 0; mat[10] = 1; mat[11] = 0;
    mat[12] = 0; mat[13] = 0;mat[14] = 0; mat[15] = 1;
}

void Render::center_obj(float *mat)
{
    mat[0] = 1;  mat[1] = 0; mat[2] = 0;  mat[3] = 0;
    mat[4] = 0;  mat[5] = 1; mat[6] = 0;  mat[7] = 0;
    mat[8] = 0;  mat[9] = 0; mat[10] = 1; mat[11] = 0;
    mat[12] = 0; mat[13] = 0;mat[14] = -15; mat[15] = 1;
}

void Render::translate_obj(float *mat)
{
    mat[0] = 1; mat[1] = 0; mat[2] = 0; mat[3] = 0;
    mat[4] = 0; mat[5] = 1; mat[6] = 0; mat[7] = 0;
    mat[8] = 0; mat[9] = 0; mat[10] = 1; mat[11] = 0;
    mat[12] = _tX;
    mat[13] = _tY;
    mat[14] = _tZ;
    mat[15] = 1;
}

void	Render::lookAt(float *mat, float eyeX, float eyeY, float eyeZ,
                        float centerX, float centerY, float centerZ,
                        float upX, float upY, float upZ)
{
    float f[3] = {
        centerX - eyeX,
        centerY - eyeY,
        centerZ - eyeZ
    };
    float f_len = sqrtf(f[0]*f[0] + f[1]*f[1] + f[2]*f[2]);
    f[0] /= f_len; f[1] /= f_len; f[2] /= f_len;

    float up[3] = {upX, upY, upZ};
    float up_len = sqrtf(up[0]*up[0] + up[1]*up[1] + up[2]*up[2]);
    up[0] /= up_len; up[1] /= up_len; up[2] /= up_len;

    float s[3] = {
        f[1]*up[2] - f[2]*up[1],
        f[2]*up[0] - f[0]*up[2],
        f[0]*up[1] - f[1]*up[0]
    };
    float s_len = sqrtf(s[0]*s[0] + s[1]*s[1] + s[2]*s[2]);
    s[0] /= s_len; s[1] /= s_len; s[2] /= s_len;

    float u[3] = {
        s[1]*f[2] - s[2]*f[1],
        s[2]*f[0] - s[0]*f[2],
        s[0]*f[1] - s[1]*f[0]
    };

    mat[0] = s[0]; mat[1] = u[0]; mat[2] = -f[0]; mat[3] = 0;
    mat[4] = s[1]; mat[5] = u[1]; mat[6] = -f[1]; mat[7] = 0;
    mat[8] = s[2]; mat[9] = u[2]; mat[10] = -f[2]; mat[11] = 0;
    mat[12] = -(s[0]*eyeX + s[1]*eyeY + s[2]*eyeZ);
    mat[13] = -(u[0]*eyeX + u[1]*eyeY + u[2]*eyeZ);
    mat[14] =  (f[0]*eyeX + f[1]*eyeY + f[2]*eyeZ);
    mat[15] = 1;
}

void Render::multiply4(float *a, float *b, float *result)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result[i*4 + j] =
				a[i*4 + 0] * b[0*4 + j] +
				a[i*4 + 1] * b[1*4 + j] +
				a[i*4 + 2] * b[2*4 + j] +
				a[i*4 + 3] * b[3*4 + j];
		}
	}
}


void Render::mouseCalculs(double posX, double posY, double &lastX, double &lastY, double sentitivity)
{
	static float init = 1;

	if (init)
	{
		lastX = posX;
		lastY = posY;
		init = 0;
	}

	double offsetY = lastY - posY;
	double offsetX = posX - lastX;

	lastX = posX;
	lastY = posY;

	//sensitivity
	offsetX *= sentitivity;
	offsetY *= sentitivity;

	_angleX += offsetX;
	_angleY += offsetY;

	if (_angleY > 89 * (M_PI / 180))
		_angleY = 89 * (M_PI / 180);
	else if (_angleY < -89 * (M_PI / 180))
		_angleY = -89 * (M_PI / 180);
}

void Render::cameraMoveAngle(GLFWwindow *window, double &lastX, double &lastY)
{
	double xpos, ypos;
	static int pressed = 0;
		
	if (!Menu::getEnableMouse())
	{
		glfwGetCursorPos(window, &xpos, &ypos);
		Render::mouseCalculs(xpos, ypos, lastX, lastY, 0.001);
	}
	else
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			if (!pressed)
				glfwGetCursorPos(window, &lastX, &lastY);
			glfwGetCursorPos(window, &xpos, &ypos);
			Render::mouseCalculs(xpos, ypos, lastX, lastY, 0.003);
			pressed = 1;
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
			pressed = 0;
	}
	//camera horizontal
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
        _angleX -= 0.01;
		if (_angleY < -89 * (M_PI / 180))
			_angleY = -89 * (M_PI / 180);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
        _angleX += 0.01;
		if (_angleY > 89 * (M_PI / 180))
			_angleY = 89 * (M_PI / 180);
    }

    //camera vertical
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
       _angleY += 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
    	_angleY -= 0.01;
    }
}

void Render::cameraMovePos(GLFWwindow *window)
{
	float speed = 0.2f;

	float frontX = sin(_angleX);
    float frontZ = -cos(_angleX);

    // vecteur droit (perpendiculaire à front)
    float rightX = cos(_angleX);
    float rightZ = sin(_angleX);

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		speed *= 3;
	}

    // déplacement avant/arrière
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
        _tZ -= speed * frontZ;
		_tX -= speed * frontX;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
        _tZ += speed * frontZ;
		_tX += speed * frontX;
    }

    // déplacement latéral
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
        _tZ += speed * rightZ;
		_tX += speed * rightX;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
    	_tZ -= speed * rightZ;
		_tX -= speed * rightX;
    }

	//deplacement haut/bas
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
    	_tY += speed;
	}
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
    	_tY -= speed;
	}
}

void Render::mouseControls(GLFWwindow *window, int colorId)
{
	static int pressed = 0;
	int used = 0;
	std::vector<Entity *> objs = Entity::getObjs();

	if (!Menu::getEnableMouse())
		return ;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !pressed)
		pressed = 1;
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		pressed = 0;
	
	for (Entity *obj : objs)
	{
		if (obj->getColorId() == colorId)
		{
			if (pressed)
			{
				Entity::deselectAll();
				obj->setSelected(true);
				used = 1;
			}
		}
	}
	if (pressed && !used)
		Entity::deselectAll();
}

void Render::manageKeys()
{
    GLFWwindow *window = Opengl::getWindow();
	static double lastX, lastY;
	static int pressed = 0;

	Render::cameraMoveAngle(window, lastX, lastY);
	Render::cameraMovePos(window);
	
	//pause menu
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && !pressed)
	{
		if (Menu::getEnableMouse())
		{
			glfwGetCursorPos(window, &lastX, &lastY);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			Menu::setEnableMouse(0);
			Entity::deselectAll();
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			glfwSetCursorPos(window, Opengl::getWidth() / 2, Opengl::getHeight() / 2);
			Menu::setEnableMouse(1);
		}
		pressed = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
        pressed = 0;
}

int Render::decodeColorId(unsigned char pixel[3])
{
	return pixel[0] + (pixel[1] << 8) + (pixel[2] << 16);
}

float Render::getTx()
{
	return _tX;
}

float Render::getTy()
{
	return _tY;
}

float Render::getTz()
{
	return _tZ;
}

GLuint Render::getFrameBuffer()
{
	return _frameBuffer;
}