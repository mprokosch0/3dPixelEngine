#include "Render.hpp"

double lastX = WIDTH / 2, lastY = HEIGHT / 2;

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

void Render::rotate_y(float *mat)
{
    float cosA = cosf(_angleX);
    float sinA = sinf(_angleX);

    mat[0] = cosA;  mat[4] = 0; mat[8]  = sinA; mat[12] = 0;
    mat[1] = 0;     mat[5] = 1; mat[9]  = 0;     mat[13] = 0;
    mat[2] = -sinA;  mat[6] = 0; mat[10] = cosA;  mat[14] = 0;
    mat[3] = 0;     mat[7] = 0; mat[11] = 0;     mat[15] = 1;
}

void Render::rotate_x(float *mat)
{
    float cosA = cosf(_angleY);
    float sinA = sinf(_angleY);

    mat[0] = 1;  mat[4] = 0;     mat[8]  = 0;    mat[12] = 0;
    mat[1] = 0;  mat[5] = cosA;  mat[9]  = -sinA; mat[13] = 0;
    mat[2] = 0;  mat[6] = sinA; mat[10] = cosA; mat[14] = 0;
    mat[3] = 0;  mat[7] = 0;     mat[11] = 0;    mat[15] = 1;
}

void Render::rotate_z(float *mat)
{
    float cosA = cosf(_angleZ);
    float sinA = sinf(_angleZ);

    mat[0] = cosA;  mat[4] = -sinA;  mat[8]  = 0; mat[12] = 0;
    mat[1] = sinA; mat[5] = cosA;  mat[9]  = 0; mat[13] = 0;
    mat[2] = 0;     mat[6] = 0;     mat[10] = 1; mat[14] = 0;
    mat[3] = 0;     mat[7] = 0;     mat[11] = 0; mat[15] = 1;
}

void Render::project_points(float *mat)
{
    float ratio = (float)Opengl::getWidth() / (float)Opengl::getHeight();
    float fov = 90.0f * (M_PI / 180);
    float near = 0.1f;
    float far = 10000.0f;
    float t = tanf(fov / 2.0f);

    mat[0]  = 1 / (ratio * t); mat[4]  = 0;     mat[8]  = 0;                          mat[12] = 0;
    mat[1]  = 0;               mat[5]  = 1 / t; mat[9]  = 0;                          mat[13] = 0;
    mat[2]  = 0;               mat[6]  = 0;     mat[10] = -(far+near)/(far-near);     mat[14] = -(2*far*near)/(far-near);
    mat[3]  = 0;               mat[7]  = 0;     mat[11] = -1;                         mat[15] = 0;
}

void Render::project_pointsOrth(float *mat)
{
    mat[0]  = 2.0f / Opengl::getWidth();  mat[4]  = 0;                        mat[8]  = 0;  mat[12] = -1;
    mat[1]  = 0;                          mat[5]  = 2.0f / Opengl::getHeight(); mat[9]  = 0;  mat[13] = -1;
    mat[2]  = 0;                          mat[6]  = 0;                        mat[10] = -1; mat[14] = 0;
    mat[3]  = 0;                          mat[7]  = 0;                        mat[11] = 0;  mat[15] = 1;
}

void Render::identityMat4(float *mat)
{
    mat[0] = 1;  mat[4] = 0; mat[8] = 0;  mat[12] = 0;
    mat[1] = 0;  mat[5] = 1; mat[9] = 0;  mat[13] = 0;
    mat[2] = 0;  mat[6] = 0; mat[10] = 1; mat[14] = 0;
    mat[3] = 0;  mat[7] = 0; mat[11] = 0; mat[15] = 1;
}

void Render::translate_obj(float *mat)
{
    mat[0] = 1; mat[4] = 0; mat[8] = 0;   mat[12] = _tX;
    mat[1] = 0; mat[5] = 1; mat[9] = 0;   mat[13] = _tY;
    mat[2] = 0; mat[6] = 0; mat[10] = 1;  mat[14] = _tZ;
    mat[3] = 0; mat[7] = 0; mat[11] = 0;  mat[15] = 1;
}

void Render::lookAt(float *mat,
                    float eyeX, float eyeY, float eyeZ,
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

    mat[0] = s[0];  mat[4] = s[1];  mat[8] = s[2];      mat[12] = -(s[0]*eyeX + s[1]*eyeY + s[2]*eyeZ);
    mat[1] = u[0];  mat[5] = u[1];  mat[9] = u[2];      mat[13] = -(u[0]*eyeX + u[1]*eyeY + u[2]*eyeZ);
    mat[2] = -f[0]; mat[6] = -f[1]; mat[10] = -f[2];    mat[14] =  (f[0]*eyeX + f[1]*eyeY + f[2]*eyeZ);
    mat[3] = 0;     mat[7] = 0;     mat[11] = 0;        mat[15] = 1;
}

void Render::multiply4Correct(float *a, float *b, float *result)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            result[i + j*4] =
                a[i + 0*4] * b[0 + j*4] +
                a[i + 1*4] * b[1 + j*4] +
                a[i + 2*4] * b[2 + j*4] +
                a[i + 3*4] * b[3 + j*4];
        }
    }
}

void Render::multiply4(float *a, float *b, float *result)
{
	for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            result[i + j*4] =
                a[0 + j*4] * b[i + 0*4] +
                a[1 + j*4] * b[i + 1*4] +
                a[2 + j*4] * b[i + 2*4] +
                a[3 + j*4] * b[i + 3*4];
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
	_angleY -= offsetY;

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

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
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
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
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
    static bool pressed = false;
    static bool gizmoLocked = false;

    std::vector<Entity *> &objs = Entity::getObjs();
    std::array<Entity, 4> &gizmo = Gizmo::getGizmo();

    if (!Menu::getEnableMouse())
        return;

    bool mouseDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

    if (mouseDown && !pressed)
        pressed = true;
    else if (!mouseDown && pressed)
    {
        pressed = false;
        gizmoLocked = false;
    }

    if (gizmoLocked && pressed)
    {
		Render::moveGizmo(lastX, lastY);
        return;
    }

    int used = 0;
    std::vector<Entity *>::iterator it = objs.end();
	int it2 = 4;
    // ------------ PICKING GIZMO -------------
    for (int iter = 0; iter != 4; iter++)
    {
        if (gizmo[iter].getColorId() == colorId)
        {
            if (pressed)
            {
                Gizmo::deselectAll();
                gizmo[iter].setSelected(true);
				glfwGetCursorPos(window, &lastX, &lastY);
                used = 1;
                gizmoLocked = true;
				it2 = iter;
            }
        }
    }

    // ------------ PICKING OBJETS -------------
    if (!used)
    {
        for (auto iter = objs.begin(); iter != objs.end(); iter++)
        {
            if ((*iter)->getColorId() == colorId)
            {
                if (pressed)
                {
                    if (!(*iter)->getGizmo())
					{
                        Entity::deselectAll();
						Gizmo::deselectAll();
					}

                    (*iter)->setSelected(true);
                    it = iter;
                    used = 1;
                }
            }
        }
    }

    if (it != objs.end() && !(*it)->getGizmo() && (*it)->getSelected() && (it + 1) != objs.end())
    {
        Entity *tmp = *it;
        objs.erase(it);
        objs.push_back(tmp);
    }

	if (it2 != 4 && gizmo[it2].getGizmo() && gizmo[it2].getSelected() && (it2 + 1) != 4)
    {
        Entity tmp = gizmo[it2];
		std::array<int, 4> arpos = Gizmo::getArrPos();
		int tmp2 = arpos[it2];
		arpos[it2] = arpos[3];
		arpos[3] = tmp2;
		Gizmo::setArrPos(arpos);
        gizmo[it2] = gizmo[3];
        gizmo[3] = tmp;
    }

    if (pressed && !used)
    {
        Entity::deselectAll();
        Gizmo::deselectAll();
    }
}
bool Render::invertMat4(const float m[16], float invOut[16])
{
    float inv[16];

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] +
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] +
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] +
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] +
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] +
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] +
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] +
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (int i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return true;
}

static bool	unprojectMouse(double x, double y, double z, double &rx, double &ry, double &rz)
{
	float	view[16], projection[16], unproj[16], tmp[16], w;
	std::array<double, 4> co = {x, y, z, 1};

	co[0] = (co[0] / Opengl::getWidth()) * 2.0f - 1.0f;
	co[1] = 1.0f - (co[1] / Opengl::getHeight()) * 2.0f;
	co[2] = co[2] * 2.0 - 1.0;

	Render::project_points(projection);
	Render::lookAt(view, 0, 0, 0, 0, 0, -1, 0, 1, 0);
	Render::multiply4(projection, view, tmp);

	if (!Render::invertMat4(tmp, unproj))
		return false;
	
	rx = unproj[0] * co[0] + unproj[4] * co[1] + unproj[8] * co[2] + unproj[12] * co[3];
	ry = unproj[1] * co[0] + unproj[5] * co[1] + unproj[9] * co[2] + unproj[13] * co[3];
	rz = unproj[2] * co[0] + unproj[6] * co[1] + unproj[10] * co[2] + unproj[14] * co[3];
	w = unproj[3] * co[0] + unproj[7] * co[1] + unproj[11] * co[2] + unproj[15] * co[3];
	if (w == 0)
		return false;
	rx /= w;
	ry /= w;
	rz /= w;
	return true;
}

void Render::moveGizmo(double &lastX, double &lastY)
{
    double mouseX, mouseY;
    Entity *obj = Gizmo::getObj();
    auto pos = obj->getMesh().getPos();
    auto vert = Gizmo::getGizmo()[3].getMesh().getVertices();
    std::array<double,3> axis = {0, 0, 0}, axisWorld;
    int index = Gizmo::getArrPos()[3];

    if (index-- == 0)
        return ;
    axis[index] = 1.0;
    glfwGetCursorPos(Opengl::getWindow(), &mouseX, &mouseY);

    double dx = mouseX - lastX;
    double dy = -( mouseY - lastY);

    std::array<double, 3> center = {pos[0], pos[1], -pos[2]},
                          tip = {pos[0] + vert[0], pos[1] + vert[1], -pos[2] + vert[2]};
   
    std::cout << RED "before anything: \n" RESET;
    std::cout << "center = " << center[0] << ", " << center[1] << ", " << center[2] << std::endl;
    std::cout << "tip = " << tip[0] << ", " << tip[1] << ", " << tip[2] << std::endl;
	if (Gizmo::getGizmo()[3].projectArrow(center, tip))
        return ;

    std::cout << YELLOW "before : \n" RESET;
    std::cout << "center = " << center[0] << ", " << center[1] << std::endl;
    std::cout << "tip = " << tip[0] << ", " << tip[1] << std::endl;
    center[0] = (center[0] + 1) * (Opengl::getWidth() / 2);
    center[1] = (center[1] + 1) * (Opengl::getHeight() / 2);
    tip[0] = (tip[0] + 1) * (Opengl::getWidth() / 2);
    tip[1] = (tip[1] + 1) * (Opengl::getHeight() / 2);
    std::cout << PINK "after : \n" RESET;
    std::cout << "center = " << center[0] << ", " << center[1] << std::endl;
    std::cout << "tip = " << tip[0] << ", " << tip[1] << std::endl;

    double axisScreenX = tip[0] - center[0];
    double axisScreenY = tip[1] - center[1];
    
    double len = sqrt(axisScreenX*axisScreenX + axisScreenY*axisScreenY);
    if (len < 1e-9)
        return;
    axisScreenX /= len;
    axisScreenY /= len;

    // if (fabs(dx * axisScreenY - dy * axisScreenX) > 15)
    //     return ;

    double moveAmount = (dx*axisScreenX + dy*axisScreenY) * 0.02;
    obj->turnAxis(axis, axisWorld);

    double gx = axisWorld[0], gy = axisWorld[1], gz = axisWorld[2];

    obj->setPos(pos[0] + gx*moveAmount,
                pos[1] + gy*moveAmount,
                pos[2] + gz*moveAmount);

    lastX = mouseX;
    lastY = mouseY;
}


void Render::manageKeys()
{
    GLFWwindow *window = Opengl::getWindow();
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