#include "Shapes.hpp"

std::vector<Entity *>	Entity::_objs;

Entity &Entity::operator=(Entity const &rhs)
{
	if (this == &rhs)
		return *this;
	this->_mesh = rhs._mesh;
	this->_shader = rhs._shader;
	this->_colorId = rhs._colorId;
	this->_selected = rhs._selected;
	this->_color = rhs._color;
	this->_isGizmo = rhs._isGizmo;
	return *this;
}

Entity Entity::operator+(Entity const &rhs) const
{
	Entity res(_shader, _mesh + rhs._mesh, 1);
    res._selected = false;
	res._color[0] = (this->_color[0] + rhs._color[0] / 2);
	res._color[1] = (this->_color[1] + rhs._color[1] / 2);
	res._color[2] = (this->_color[2] + rhs._color[2] / 2);
    return res;
}

//constructors/destructors---------------------------------

Entity::Entity(void)
{
	static int i = 0;

	_colorId = i++;
	this->_shader = nullptr;
	this->_color = {-1, -1, -1};
	this->_isGizmo = false;
	_selected = false;
}

Entity::Entity(Shaders *shader, Mesh mesh, int flag)
{
	static int i = 16777215;

	_colorId = i--;
	_selected = false;
	this->_isGizmo = false;
	this->_shader = shader;
	this->_mesh = mesh;
	this->_color = {-1, -1, -1};
	if (!flag)
		_objs.push_back(this);
}

Entity::~Entity(void) {}

//Member functions-----------------------------------------

void	Entity::setGizmo(bool flag)
{
	this->_isGizmo = flag;
}

void	Entity::setColors(float r, float g, float b)
{
	this->_color[0] = r;
	this->_color[1] = g;
	this->_color[2] = b;
}

const Mesh &Entity::getMesh() const
{
	return this->_mesh;
}

const std::array<float, 3> &Entity::getColors(void) const
{
	return this->_color;
}

void	Entity::addBack()
{
	_objs.push_back(this);
}

int		Entity::getColorId() const
{
	return this->_colorId;
}

Shaders	*Entity::getShader() const
{
	return this->_shader;
}

bool	Entity::getSelected() const
{
	return this->_selected;
}

void	Entity::setSelected(bool select)
{
	this->_selected = select;
}

std::vector<Entity *> &Entity::getObjs(void)
{
	return _objs;
}

const std::vector<Entity *> &Entity::cstGetObjs(void)
{
	return _objs;
}

void	Entity::deselectAll()
{
	for (Entity *obj : _objs)
		obj->_selected = false;
}

void	Entity::scale(float *mat) const
{
	std::array<float, 3> _scale = this->_mesh.getScale();
	float scaleX = _scale[0], scaleY= _scale[1], scaleZ = _scale[2];

	mat[0]  = scaleX;		mat[1]  = 0;			mat[2]  = 0;			mat[3]  = 0;
	mat[4]  = 0;			mat[5]  = scaleY;		mat[6]  = 0;			mat[7]  = 0;
	mat[8]  = 0;			mat[9]  = 0;			mat[10] = scaleZ;		mat[11] = 0;
	mat[12] = 0;			mat[13] = 0;			mat[14] = 0;			mat[15] = 1;
}

void	Entity::rotate_y(float *mat) const
{
	float angle = this->_mesh.getRot()[1];
	if (this->_isGizmo)
		angle = Gizmo::getRot()[1];
	float cosA = cosf(angle);
	float sinA = sinf(angle);

	mat[0]  = cosA; mat[1]  = 0; mat[2]  = -sinA; mat[3]  = 0;
	mat[4]  = 0;    mat[5]  = 1; mat[6]  = 0;     mat[7]  = 0;
	mat[8]  = sinA; mat[9]  = 0; mat[10] = cosA;  mat[11] = 0;
	mat[12] = 0;    mat[13] = 0; mat[14] = 0;     mat[15] = 1;
}

void	Entity::rotate_x(float *mat) const
{
	float angle = this->_mesh.getRot()[0];
	if (this->_isGizmo)
		angle = Gizmo::getRot()[0];
	float cosA = cosf(angle);
	float sinA = sinf(angle);

	mat[0]  = 1; mat[1]  = 0;    mat[2]  = 0;	  mat[3]  = 0;
	mat[4]  = 0; mat[5]  = cosA; mat[6]  = -sinA; mat[7]  = 0;
	mat[8]  = 0; mat[9]  = sinA; mat[10] = cosA;  mat[11] = 0;
	mat[12] = 0; mat[13] = 0;	 mat[14] = 0;     mat[15] = 1;
}

void	Entity::rotate_z(float *mat) const
{
	float angle = this->_mesh.getRot()[2];
	if (this->_isGizmo)
		angle = Gizmo::getRot()[2];
	float cosA = cosf(angle);
	float sinA = sinf(angle);

	mat[0]  = cosA;	mat[1]  = -sinA; mat[2]  = 0;	mat[3]  = 0;
	mat[4]  = sinA;	mat[5]  = cosA;  mat[6]  = 0;	mat[7]  = 0;
	mat[8]  = 0;	mat[9]  = 0;	 mat[10] = 1;	mat[11] = 0;
	mat[12] = 0;	mat[13] = 0;	 mat[14] = 0;	mat[15] = 1;
}

void	Entity::setPos(float x, float y, float z)
{
	this->_mesh.setPos(x, y, z);
}

void	Entity::setRot(float x, float y, float z)
{
	this->_mesh.setRot(x, y, z);
}

void	Entity::setScale(float x, float y, float z)
{
	this->_mesh.setScale(x, y, z);
}

void Entity::setUniformColor(int flag)
{
	float r = -1;
	float g = -1;
	float b = -1;

	int a;
	a = 0;
	if (flag)
	{
    	r = (this->_colorId & 0xFF) / 255.0f;
    	g = ((this->_colorId >> 8) & 0xFF) / 255.0f;
    	b = ((this->_colorId >> 16) & 0xFF) / 255.0f;
	}
	this->_shader->use();
    this->_shader->setFloat("colorPickR", r);
	this->_shader->setFloat("colorPickG", g);
	this->_shader->setFloat("colorPickB", b);
	this->_shader->setFloat("colorR", this->_color[0]);
	this->_shader->setFloat("colorG", this->_color[1]);
	this->_shader->setFloat("colorB", this->_color[2]);
}


void Entity::draw(int colorId) const
{
    float rotX[16], rotY[16], rotZ[16];
    float worldRotX[16], worldRotY[16], worldRotZ[16];
    float translate[16], wTranslate[16], scale[16];
	float temp[16], temp2[16], locModel[16], wModel[16];;
    float projection[16], camera[16];
	float toCenter[16], backToCenter[16];

    this->_shader->use();

	std::array<float, 3> _pos = this->_mesh.getPos();

	Render::identityMat4(toCenter);
	if (!this->_isGizmo)
	{
		toCenter[12] = -this->_mesh.getCenters()[0] - _pos[0];
		toCenter[13] = -this->_mesh.getCenters()[1] - _pos[1];
		toCenter[14] = -this->_mesh.getCenters()[2] - _pos[2];
	}
	Render::identityMat4(backToCenter);
	if (!this->_isGizmo)
	{
		backToCenter[12] = this->_mesh.getCenters()[0] + _pos[0];
		backToCenter[13] = this->_mesh.getCenters()[1] + _pos[1];
		backToCenter[14] = this->_mesh.getCenters()[2] + _pos[2];
	}


    Render::translate_obj(wTranslate);
	Render::identityMat4(translate);
    translate[12] += _pos[0];
    translate[13] += _pos[1];
    translate[14] += _pos[2];
	if (this->_isGizmo)
	{
		translate[12] = Gizmo::getPos()[0];
		translate[13] = Gizmo::getPos()[1];
		translate[14] = Gizmo::getPos()[2];
	}

	this->rotate_x(rotX);
	this->rotate_y(rotY);
	this->rotate_z(rotZ);
	
	this->scale(scale);
    Render::rotate_x(worldRotX);
    Render::rotate_y(worldRotY);
    Render::rotate_z(worldRotZ);

    Render::project_points(projection);
    Render::lookAt(camera, 0, 0, 0, 0, 0, -1, 0, 1, 0);

	if (!this->_isGizmo)
	{
		Render::multiply4(rotY, rotX, temp);
		Render::multiply4(rotZ, temp, temp2);
		Render::multiply4(toCenter, temp2, temp);
		Render::multiply4(temp, scale, temp2);
		Render::multiply4(temp2, backToCenter, temp);
		Render::multiply4(translate, temp, locModel);
	}
	else
	{
		Render::multiply4(rotY, rotX, temp);
		Render::multiply4(rotZ, temp, temp2);
		Render::multiply4(temp2, scale, temp);
		Render::multiply4(temp, translate, locModel);
	}
	Render::multiply4(worldRotY, worldRotX, temp);
	Render::multiply4(worldRotZ, temp, temp2);
	Render::multiply4(wTranslate, temp2, wModel);

	this->_shader->setMat4("locModel", locModel);
	this->_shader->setMat4("wModel", wModel);
    this->_shader->setMat4("projection", projection);
    this->_shader->setMat4("camera", camera);
	this->_shader->setInt("uline", 0);
	this->_shader->setInt("selected", this->getSelected());
	if (this->_selected)
	{
		colorId = 2;
	}
    this->_mesh.draw(*this->_shader, colorId);
}
