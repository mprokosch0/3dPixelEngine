#include "Render.hpp"

GLuint	Render::_vao;
GLuint	Render::_vbo;
GLuint	Render::_ebo;
float	Render::_angleX = 0;
float	Render::_angleY = 0;
float	Render::_angleZ = 0;
float	Render::_centerX = 0;
float	Render::_centerY = 0;
float	Render::_centerZ = 0;
float	Render::_tX = 0;
float	Render::_tY = 0;
float	Render::_tZ = 0;

//constructors/destructors---------------------------------

Render::Render(void) {}

Render::~Render(void) {}

//Member functions-----------------------------------------

void	rotate_y(float *mat, float angle)
{
	float cosA = cosf(angle);
	float sinA = sinf(angle);
	mat[0]  = cosA; mat[1]  = 0; mat[2]  = -sinA; mat[3]  = 0;
	mat[4]  = 0;    mat[5]  = 1; mat[6]  = 0;     mat[7]  = 0;
	mat[8]  = sinA; mat[9]  = 0; mat[10] = cosA;  mat[11] = 0;
	mat[12] = 0;    mat[13] = 0; mat[14] = 0;     mat[15] = 1;
}

void	rotate_x(float *mat, float angle)
{
	float cosA = cosf(angle);
	float sinA = sinf(angle);
	mat[0]  = 1; mat[1]  = 0;    mat[2]  = 0;	  mat[3]  = 0;
	mat[4]  = 0; mat[5]  = cosA; mat[6]  = -sinA; mat[7]  = 0;
	mat[8]  = 0; mat[9]  = sinA; mat[10] = cosA;  mat[11] = 0;
	mat[12] = 0; mat[13] = 0;	 mat[14] = 0;     mat[15] = 1;
}

void	rotate_z(float *mat, float angle)
{
	float cosA = cosf(angle);
	float sinA = sinf(angle);
	mat[0]  = cosA; mat[1]  = -sinA; mat[2]  = 0; mat[3]  = 0;
	mat[4]  = sinA; mat[5]  = cosA;  mat[6]  = 0; mat[7]  = 0;
	mat[8]  = 0;	mat[9]  = 0;	 mat[10] = 1;  mat[11] = 0;
	mat[12] = 0;	mat[13] = 0;	 mat[14] = 0;     mat[15] = 1;
}

void	project_points(float *mat)
{
	float	ratio = (float)WIDTH / (float)HEIGHT;
	float	fov = 45.0f * (M_PI / 180);
	float	near = 0.1f;
	float	far = 100.0f;
	float t = tanf(fov / 2.0f);

	mat[0]  = 1 / (ratio * t); mat[1]  = 0;		mat[2]  = 0;								mat[3]  = 0;
	mat[4]  = 0;    		   mat[5]  = 1 / t;	mat[6]  = 0;								mat[7]  = 0;
	mat[8]  = 0;			   mat[9]  = 0;		mat[10] = -(far + near) / (far - near);		mat[11] = -1;
	mat[12] = 0;    		   mat[13] = 0;		mat[14] = -2 * far * near / (far - near);	mat[15] = 0;
}

void center_obj(float *mat)
{
    mat[0] = 1;  mat[1] = 0; mat[2] = 0;  mat[3] = 0;
    mat[4] = 0;  mat[5] = 1; mat[6] = 0;  mat[7] = 0;
    mat[8] = 0;  mat[9] = 0; mat[10] = 1; mat[11] = 0;
    mat[12] = 0; mat[13] = 0;mat[14] = -15; mat[15] = 1;
}

void translate_obj(float *mat, float tX, float tY, float tZ)
{
    mat[0] = 1; mat[1] = 0; mat[2] = 0; mat[3] = 0;
    mat[4] = 0; mat[5] = 1; mat[6] = 0; mat[7] = 0;
    mat[8] = 0; mat[9] = 0; mat[10] = 1; mat[11] = 0;
    mat[12] = tX;
    mat[13] = tY;
    mat[14] = tZ;
    mat[15] = 1;
}

void	lookAt(float *mat, float eyeX, float eyeY, float eyeZ,
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

void	Render::bindMatrices()
{
	float rotX[16];
	float rotY[16];
	float rotZ[16];
	float projection[16];
	float camera[16];
	float translate[16];
	float center[16];
	center_obj(center);
	translate_obj(translate, _tX, _tY, _tZ);
	rotate_y(rotY, _angleX);
	rotate_x(rotX, _angleY);
	rotate_z(rotZ, _angleZ);
	project_points(projection);
	lookAt(camera, 0, 0, 0,
					0, 0, -1,
					0.0f, 1.0f, 0.0f);
	GLuint modelLoc = Opengl::glGetUniformLocation(Opengl::getShaderProgram(), "rotX");
	Opengl::glUniformMatrix4fv(modelLoc, 1, GL_FALSE, rotX);
	modelLoc = Opengl::glGetUniformLocation(Opengl::getShaderProgram(), "rotY");
	Opengl::glUniformMatrix4fv(modelLoc, 1, GL_FALSE, rotY);
	modelLoc = Opengl::glGetUniformLocation(Opengl::getShaderProgram(), "rotZ");
	Opengl::glUniformMatrix4fv(modelLoc, 1, GL_FALSE, rotZ);
	modelLoc = Opengl::glGetUniformLocation(Opengl::getShaderProgram(), "center");
	Opengl::glUniformMatrix4fv(modelLoc, 1, GL_FALSE, center);
	modelLoc = Opengl::glGetUniformLocation(Opengl::getShaderProgram(), "translate");
	Opengl::glUniformMatrix4fv(modelLoc, 1, GL_FALSE, translate);
	modelLoc = Opengl::glGetUniformLocation(Opengl::getShaderProgram(), "projection");
	Opengl::glUniformMatrix4fv(modelLoc, 1, GL_FALSE, projection);
	modelLoc = Opengl::glGetUniformLocation(Opengl::getShaderProgram(), "camera");
	Opengl::glUniformMatrix4fv(modelLoc, 1, GL_FALSE, camera);
}

void	Render::initBuffers(std::vector<float> points, std::vector<int> faces)
{
	Opengl::glGenVertexArrays(1, &_vao);
	Opengl::glGenBuffers(1, &_vbo);
	Opengl::glGenBuffers(1, &_ebo);

	Opengl::glBindVertexArray(_vao);

	// buffer des sommets
	Opengl::glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	Opengl::glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);
	Opengl::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	Opengl::glEnableVertexAttribArray(0);

	//buffer des indices (faces)
	Opengl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	Opengl::glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(GLuint), faces.data(), GL_STATIC_DRAW);

	Opengl::glBindVertexArray(0);
}

void Render::mouseCalculs(double posX, double posY)
{
	static float lastX, lastY;
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
	offsetX *= 0.001;
	offsetY *= 0.001;

	_angleX += offsetX;
	_angleY += offsetY;

	if (_angleY > 89)
		_angleY = 89;
	else if (_angleY < -89)
		_angleY = -89;
}

void Render::manageKeys()
{
    GLFWwindow *window = Opengl::getWindow();
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    Render::mouseCalculs(xpos, ypos);

    float speed = 0.2f;

	float frontX = sin(_angleX);
    float frontZ = -cos(_angleX);

    // vecteur droit (perpendiculaire à front)
    float rightX = cos(_angleX);
    float rightZ = sin(_angleX);

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
}



GLuint Render::getVao(void)
{
	return _vao;
}

GLuint Render::getVbo(void)
{
	return _vbo;
}

GLuint Render::getEbo(void)
{
	return _ebo;
}