#include "Shapes.hpp"

//CUBE--------------------------------------------------------------------------------

//constructors/destructors---------------------------------

Cube::Cube(Shaders *shader, float pos[3], float rot[3], float scale[3]): Entity(shader, 
	Mesh(std::vector<float> {
			-0.5f, -0.5f, -0.5f,
			-0.5f, 0.5f, -0.5f,
		    0.5f, -0.5f, -0.5f,
			0.5f, 0.5f, -0.5f,
			-0.5f, -0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f,
		    0.5f, -0.5f, 0.5f,
			0.5f, 0.5f, 0.5f},
	std::vector<GLuint> {
			0, 1, 2,  2, 1, 3,
			4, 5, 6,  6, 5, 7,
			0, 1, 4,  4, 1, 5,
			2, 3, 6,  6, 3, 7,
			1, 3, 5,  5, 3, 7,
			0, 2, 4,  4, 2, 6
		},
	
	std::vector<GLuint> {
		0, 1,  0, 2,  0, 4,
		1, 3,  1, 5,
		2, 3,  2, 6,
		3, 7,
		4, 5,  4, 6,
		5, 7,
		6, 7
	}))
{
	this->_pos[0] = pos[0];
	this->_pos[1] = pos[1];
	this->_pos[2] = pos[2];
	this->_scale[0] = scale[0];
	this->_scale[1] = scale[1];
	this->_scale[2] = scale[2];
	this->_rot[0] = rot[0];
	this->_rot[1] = rot[1];
	this->_rot[2] = rot[2];
}

Cube::~Cube(void) {}

//Member functions-----------------------------------------

//PLANE-------------------------------------------------------------------------------

//constructors/destructors---------------------------------

Plane::Plane(Shaders *shader, float pos[3], float rot[3], float scale[3]): Entity(shader, 
	Mesh(std::vector<float> {
			-1, 0, -1,
			1, 0, -1,
			-1, 0, 1,
			1, 0, 1},
	std::vector<GLuint> {
			0, 1, 2, 2, 1, 3
		},
	
	std::vector<GLuint> {
		0, 1,  0, 2,
		3, 1,  3, 2
	}))
{
	this->_pos[0] = pos[0];
	this->_pos[1] = pos[1];
	this->_pos[2] = pos[2];
	this->_scale[0] = scale[0];
	this->_scale[1] = scale[1];
	this->_scale[2] = scale[2];
	this->_rot[0] = rot[0];
	this->_rot[1] = rot[1];
	this->_rot[2] = rot[2];
}

Plane::~Plane(void) {}

//Member functions-----------------------------------------

//TRIANGLE----------------------------------------------------------------------------

//constructors/destructors---------------------------------

Triangle::Triangle(Shaders *shader, float pos[3], float rot[3], float scale[3]): Entity(shader, 
	Mesh(std::vector<float>{
			0.0f, -0.2722f,  0.5774f,
			-0.5f, -0.2722f, -0.2887f,
			0.5f, -0.2722f, -0.2887f,
			0.0f, 0.5443f,  0.0f
		},
	std::vector<GLuint> {
			0, 1, 2, 2, 1, 3,
			0, 1, 3, 2, 0, 3
		},
	
	std::vector<GLuint> {
		0, 1,  0, 2,  0, 3,
		1, 2,  2, 3,  1, 3
	}))
{
	this->_pos[0] = pos[0];
	this->_pos[1] = pos[1];
	this->_pos[2] = pos[2];
	this->_scale[0] = scale[0];
	this->_scale[1] = scale[1];
	this->_scale[2] = scale[2];
	this->_rot[0] = rot[0];
	this->_rot[1] = rot[1];
	this->_rot[2] = rot[2];
}

Triangle::~Triangle(void) {}

//Member functions-----------------------------------------

//GRID---------------------------------------------------------------------------------

//constructors/destructors---------------------------------

static std::vector<float> GenGrid()
{
	std::vector<float> res;
	for (int i = -100; i < 100; i+=10)
	{
		for (int j = -100; j < 100; j+=10)
		{
			res.push_back(j);
			res.push_back(-100);
			res.push_back(i);
			res.push_back(j);
			res.push_back(100);
			res.push_back(i);
		}
	}
	for (int i = -100; i < 100; i+=10)
	{
		for (int j = -100; j < 100; j+=10)
		{
			res.push_back(-100);
			res.push_back(j);
			res.push_back(i);
			res.push_back(100);
			res.push_back(j);
			res.push_back(i);
		}
	}
	for (int i = -100; i < 100; i+=10)
	{
		for (int j = -100; j < 100; j+=10)
		{
			res.push_back(i);
			res.push_back(j);
			res.push_back(-100);
			res.push_back(i);
			res.push_back(j);
			res.push_back(100);
		}
	}
	return res;
}

static std::vector<GLuint> GenIndices()
{
	std::vector<GLuint> res;
	for (int i = 0; i < 20 * 20 * 6; i+=2)
	{
		res.push_back(i);
		res.push_back(i + 1);
	}
	return res;
}

Grid::Grid(Shaders *shader): Entity(shader, 
	Mesh(GenGrid(), GenIndices(),
	
	std::vector<GLuint> {
		0, 1,  0, 2,  0, 3,
		1, 2,  2, 3,  1, 3
	}))
{}

Grid::~Grid(void) {}

//Member functions-----------------------------------------

void Grid::draw() const
{
	float rotX[16], rotY[16], rotZ[16];
    float worldRotX[16], worldRotY[16], worldRotZ[16];
    float translate[16], wTranslate[16], scale[16];
	float temp[16], temp2[16], locModel[16], wModel[16];;
    float projection[16], camera[16];
	float toCenter[16], backToCenter[16];

    this->_shader->use();

	Render::identityMat4(toCenter);
    toCenter[12] = -this->_mesh.getCenters()[0] - this->_pos[0];
    toCenter[13] = -this->_mesh.getCenters()[1] - this->_pos[1];
    toCenter[14] = -this->_mesh.getCenters()[2] - this->_pos[2];
	Render::identityMat4(backToCenter);
    backToCenter[12] = this->_mesh.getCenters()[0] + this->_pos[0];
    backToCenter[13] = this->_mesh.getCenters()[1] + this->_pos[1];
    backToCenter[14] = this->_mesh.getCenters()[2] + this->_pos[2];
    Render::translate_obj(wTranslate);
	Render::identityMat4(translate);
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

	Render::multiply4(rotY, rotX, temp);
	Render::multiply4(rotZ, temp, temp2);
	Render::multiply4(toCenter, temp2, temp);
	Render::multiply4(temp, scale, temp2);
	Render::multiply4(temp2, backToCenter, temp);
	Render::multiply4(translate, temp, locModel);

	Render::multiply4(worldRotY, worldRotX, temp);
	Render::multiply4(worldRotZ, temp, temp2);
	Render::multiply4(wTranslate, temp2, wModel);


	this->_shader->setMat4("locModel", locModel);
	this->_shader->setMat4("wModel", wModel);
    this->_shader->setMat4("projection", projection);
    this->_shader->setMat4("camera", camera);
	Opengl::glBindVertexArray(this->_mesh.getVao());
	glDrawElements(GL_LINES, 20 * 20 * 6, GL_UNSIGNED_INT, 0);
}