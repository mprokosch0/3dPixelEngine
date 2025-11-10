#include "Entity.hpp"

//constructors/destructors---------------------------------

Entity::Entity(Shaders *shader, Mesh *mesh)
{
	_pos[0] = _pos[1] = _pos[2] = 0;
	_rot[0] = _rot[1] = _rot[2] = 0;
	_scale[0] = _scale[1] = _scale[2] = 1;
	this->_shader = shader;
	this->_mesh = mesh;
}

Entity::~Entity(void) {}

//Member functions-----------------------------------------

void	Entity::scale(float *mat) const
{
	mat[0]  = this->_scale[0];	mat[1]  = 0;				mat[2]  = 0;				mat[3]  = 0;
	mat[4]  = 0;				mat[5]  = this->_scale[1];	mat[6]  = 0;				mat[7]  = 0;
	mat[8]  = 0;				mat[9]  = 0;				mat[10] = this->_scale[2];  mat[11] = 0;
	mat[12] = 0;				mat[13] = 0;				mat[14] = 0;				mat[15] = 1;
}

void	Entity::rotate_y(float *mat) const
{
	float cosA = cosf(this->_rot[1]);
	float sinA = sinf(this->_rot[1]);
	mat[0]  = cosA; mat[1]  = 0; mat[2]  = -sinA; mat[3]  = 0;
	mat[4]  = 0;    mat[5]  = 1; mat[6]  = 0;     mat[7]  = 0;
	mat[8]  = sinA; mat[9]  = 0; mat[10] = cosA;  mat[11] = 0;
	mat[12] = 0;    mat[13] = 0; mat[14] = 0;     mat[15] = 1;
}

void	Entity::rotate_x(float *mat) const
{
	float cosA = cosf(this->_rot[0]);
	float sinA = sinf(this->_rot[0]);
	mat[0]  = 1; mat[1]  = 0;    mat[2]  = 0;	  mat[3]  = 0;
	mat[4]  = 0; mat[5]  = cosA; mat[6]  = -sinA; mat[7]  = 0;
	mat[8]  = 0; mat[9]  = sinA; mat[10] = cosA;  mat[11] = 0;
	mat[12] = 0; mat[13] = 0;	 mat[14] = 0;     mat[15] = 1;
}

void	Entity::rotate_z(float *mat) const
{
	float cosA = cosf(this->_rot[2]);
	float sinA = sinf(this->_rot[2]);
	mat[0]  = cosA;	mat[1]  = -sinA; mat[2]  = 0;	mat[3]  = 0;
	mat[4]  = sinA;	mat[5]  = cosA;  mat[6]  = 0;	mat[7]  = 0;
	mat[8]  = 0;	mat[9]  = 0;	 mat[10] = 1;	mat[11] = 0;
	mat[12] = 0;	mat[13] = 0;	 mat[14] = 0;	mat[15] = 1;
}

void	Entity::setPos(float x, float y, float z)
{
	this->_pos[0] = x;
	this->_pos[1] = y;
	this->_pos[2] = z;
}

void	Entity::setRot(float x, float y, float z)
{
	this->_rot[0] = x;
	this->_rot[1] = y;
	this->_rot[2] = z;
}

void	Entity::setScale(float x, float y, float z)
{
	this->_scale[0] = x;
	this->_scale[1] = y;
	this->_scale[2] = z;
}

void Entity::draw() const
{
    float rotX[16], rotY[16], rotZ[16];
    float worldRotX[16], worldRotY[16], worldRotZ[16];
    float translate[16], scale[16], temp[16], temp2[16];
    float projection[16], camera[16];
	float toCenter[16], backToCenter[16];

    this->_shader->use();

	Render::identityMat4(toCenter);
    toCenter[12] = -this->_mesh->getCenters()[0];
    toCenter[13] = -this->_mesh->getCenters()[1];
    toCenter[14] = -this->_mesh->getCenters()[2];
	Render::identityMat4(backToCenter);
    backToCenter[12] = this->_mesh->getCenters()[0];
    backToCenter[13] = this->_mesh->getCenters()[1];
    backToCenter[14] = this->_mesh->getCenters()[2];
    Render::translate_obj(translate);
    translate[12] += _pos[0];
    translate[13] += _pos[1];
    translate[14] += _pos[2];

	this->rotate_x(rotX);
	this->rotate_y(rotY);
	this->rotate_z(rotZ);
	this->scale(scale);
    Render::rotate_x(worldRotX);
    Render::rotate_y(worldRotY);
    Render::rotate_z(worldRotZ);

    Render::project_points(projection);
    Render::lookAt(camera, 0, 0, 0, 0, 0, -1, 0, 1, 0);

	Render::multiply4(translate, backToCenter, temp);
	Render::multiply4(scale, toCenter, temp2);

	this->_shader->setMat4("rotX", rotX);
	this->_shader->setMat4("rotY", rotY);
	this->_shader->setMat4("rotZ", rotZ);
	this->_shader->setMat4("wRotX", worldRotX);
	this->_shader->setMat4("wRotY", worldRotY);
	this->_shader->setMat4("wRotZ", worldRotZ);
	this->_shader->setMat4("scale", temp2);
	this->_shader->setMat4("translate", temp);
    this->_shader->setMat4("projection", projection);
    this->_shader->setMat4("camera", camera);
    this->_mesh->draw();
}
