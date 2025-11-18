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
	}), 0)
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
	}), 0)
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
	Mesh(std::vector<float> {
			0.0f, 0.0f,  0.57735027f,
			-0.5f, 0.0f, -0.28867513f,
			0.5f, 0.0f, -0.28867513f,
			0.0f, 1.0f,  0.0f
		},
	std::vector<GLuint> {
			0, 1, 2, 2, 1, 3,
			0, 1, 3, 2, 0, 3
		},
	
	std::vector<GLuint> {
		0, 1,  0, 2,  0, 3,
		1, 2,  2, 3,  1, 3
	}), 0)
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

//HUD---------------------------------------------------------------------------------

//constructors/destructors---------------------------------

Hud::Hud(Shaders *shader, float x, float y, float lenX, float lenY): Entity(shader, 
	Mesh(std::vector<float>{
			x, y,  x, y + lenY,
			x + lenX, y,  x + lenX, y + lenY
		},
		std::vector<GLuint>{
			0, 1, 2,  1, 2, 3
		}), 1)
{}

Hud::~Hud(void) {}

void Hud::draw() const
{
    float projection[16];

	glDisable(GL_DEPTH_TEST);
    this->_shader->use();

	Render::project_pointsOrth(projection);

    this->_shader->setMat4("projection", projection);
	Opengl::glBindVertexArray(this->_mesh.getVao());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

//Member functions-----------------------------------------

//SPHERE-----------------------------------------------------------------------------

//constructors/destructors---------------------------------

struct Vertex {
    float x, y, z;
    float nx, ny, nz; // normales
    float u, v;       // coordonnées UV
};

std::vector<float> generateSphereVertices(float radius, unsigned int latSeg, unsigned int lonSeg)
{
    std::vector<float> vertices;
    for (unsigned int y = 0; y <= latSeg; ++y)
	{
        for (unsigned int x = 0; x <= lonSeg; ++x)
		{
            float u = (float)x / lonSeg;
            float v = (float)y / latSeg;
            float theta = u * 2.0f * M_PI;    // longitude
            float phi   = v * M_PI;           // latitude

            float sx = sin(phi) * cos(theta);
            float sy = cos(phi);
            float sz = sin(phi) * sin(theta);

            Vertex vert;
            vert.x = radius * sx;
            vert.y = radius * sy;
            vert.z = radius * sz;

            vert.nx = sx;  // normales
            vert.ny = sy;
            vert.nz = sz;

            vert.u = u;
            vert.v = v;

            vertices.push_back(vert.x);
			vertices.push_back(vert.y);
			vertices.push_back(vert.z);
        }
    }
	return vertices;
}

std::vector<GLuint> generateSphereIndices(unsigned int latSeg, unsigned int lonSeg)
{
	std::vector<GLuint> indices;

    for (unsigned int y = 0; y < latSeg; ++y)
	{
        for (unsigned int x = 0; x < lonSeg; ++x)
		{
            unsigned int i0 = y       * (lonSeg + 1) + x;
            unsigned int i1 = (y + 1) * (lonSeg + 1) + x;
            unsigned int i2 = (y + 1) * (lonSeg + 1) + (x + 1);
            unsigned int i3 = y       * (lonSeg + 1) + (x + 1);

            // Deux triangles par quad
            indices.push_back(i0);
            indices.push_back(i1);
            indices.push_back(i2);

            indices.push_back(i0);
            indices.push_back(i2);
            indices.push_back(i3);
        }
    }
	return indices;
}

std::vector<GLuint> generateSphereLines(unsigned int latSeg, unsigned int lonSeg)
{
	std::vector<GLuint> indices;

	for (unsigned int y = 0; y <= latSeg; ++y)
	{
        for (unsigned int x = 0; x < lonSeg; ++x)
		{
            unsigned int i0 = y * (lonSeg + 1) + x;
            unsigned int i1 = i0 + 1;
            indices.push_back(i0);
            indices.push_back(i1); // ligne de longitude
        }
    }

    for (unsigned int y = 0; y < latSeg; ++y)
	{
        for (unsigned int x = 0; x <= lonSeg; ++x)
		{
            unsigned int i0 = y * (lonSeg + 1) + x;
            unsigned int i1 = (y + 1) * (lonSeg + 1) + x;
            indices.push_back(i0);
            indices.push_back(i1); // ligne de latitude
        }
    }

	return indices;
}


Sphere::Sphere(Shaders *shader, float pos[3], float rot[3], float scale[3]): Entity(shader, 
	Mesh(generateSphereVertices(10, 32, 32), generateSphereIndices(32, 32),
			generateSphereLines(32, 32)), 0)
{
	this->_mesh.setCenters(0, 0, 0);
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

Sphere::~Sphere(void) {}


//Member functions-----------------------------------------

//CYLINDER-----------------------------------------------------------------------------

//constructors/destructors---------------------------------

std::vector<float> generateCylinderVertices(float radius, float height, unsigned int radialSeg, unsigned int heightSeg)
{
    std::vector<float> vertices;
    for (unsigned int y = 0; y <= heightSeg; ++y)
    {
        float v = (float)y / heightSeg;
        float posY = v * height - height / 2.0f; // centre sur 0

        for (unsigned int x = 0; x <= radialSeg; ++x)
        {
            float u = (float)x / radialSeg;
            float theta = u * 2.0f * M_PI;

            float sx = cos(theta);
            float sz = sin(theta);

            vertices.push_back(radius * sx);  // x
            vertices.push_back(posY);         // y
            vertices.push_back(radius * sz);  // z
        }
    }
    return vertices;
}


std::vector<GLuint> generateCylinderIndices(unsigned int radialSeg, unsigned int heightSeg)
{
	std::vector<GLuint> indices;

    for (unsigned int y = 0; y < heightSeg; ++y)
    {
        for (unsigned int x = 0; x < radialSeg; ++x)
		{
			unsigned int i0 = y       * (radialSeg + 1) + x;
            unsigned int i1 = (y + 1) * (radialSeg + 1) + x;
            unsigned int i2 = (y + 1) * (radialSeg + 1) + (x + 1);
            unsigned int i3 = y       * (radialSeg + 1) + (x + 1);

			indices.push_back(i0);
            indices.push_back(i1);
            indices.push_back(i2);

            indices.push_back(i0);
            indices.push_back(i2);
            indices.push_back(i3);
		}
	}
	return indices;
}

std::vector<GLuint> generateCylinderLines(unsigned int radialSeg, unsigned int heightSeg)
{
	std::vector<GLuint> indices;

	for (unsigned int y = 0; y <= heightSeg; ++y)
	{
        for (unsigned int x = 0; x < radialSeg; ++x)
		{
            unsigned int i0 = y * (radialSeg + 1) + x;
            unsigned int i1 = i0 + 1;
            indices.push_back(i0);
            indices.push_back(i1); // ligne de longitude
        }
    }

    for (unsigned int y = 0; y < heightSeg; ++y)
	{
        for (unsigned int x = 0; x <= radialSeg; ++x)
		{
            unsigned int i0 = y * (radialSeg + 1) + x;
            unsigned int i1 = (y + 1) * (radialSeg + 1) + x;
            indices.push_back(i0);
            indices.push_back(i1); // ligne de latitude
        }
    }

	return indices;
}


Cylinder::Cylinder(Shaders *shader, float pos[3], float rot[3], float scale[3]): Entity(shader, 
	Mesh(generateCylinderVertices(10, 10, 32, 10), generateCylinderIndices(32, 10),
			generateCylinderLines(32, 10)), 0)
{
	this->_mesh.setCenters(0, 0, 0);
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

Cylinder::~Cylinder(void) {}


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
			res.push_back(90);
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
			res.push_back(90);
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
			res.push_back(90);
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
	}), 1)
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
	Render::identityMat4(wTranslate);
	wTranslate[12] += Render::getTx() - (std::floor(Render::getTx() / 10) * 10);
    wTranslate[13] += Render::getTy() - (std::floor(Render::getTy() / 10) * 10);
    wTranslate[14] += Render::getTz() - (std::floor(Render::getTz() / 10) * 10);
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

//GRID---------------------------------------------------------------------------------

//constructors/destructors---------------------------------

Text::Text(Shaders *shader): Entity(shader, Mesh(std::vector<float>{}, std::vector<GLuint>{}), 1)
{}

Text::~Text(void) {}

//Member functions-----------------------------------------

void	Text::draw(const char * text, float x, float y) const
{
	static std::vector<GLuint> indices;
    static float buffer[99999];
	float projection[16];
	int j = 0;

	(void)text, (void)x, (void)y;
    //int num_quads = stb_easy_font_print(x, y, (char*)text, NULL, buffer, sizeof(buffer));
	// int num_vertices = num_quads * 4;
	// int num_indices = num_quads * 6;
	// // for (size_t i = 0; i < 1000; i++)
	// // {
	// // 	std::cout << "buffer[" << i << "] = " << (int)buffer[i] << std::endl;
	// // }
	
	// indices.resize(num_indices);
	// for (int i = 0; i < num_vertices; i+=4)
	// {
	// 	indices[j++] = i;
	// 	indices[j++] = i + 1;
	// 	indices[j++] = i + 2;
	// 	indices[j++] = i + 1;
	// 	indices[j++] = i + 2;
	// 	indices[j++] = i + 3;
	// }
	
	// this->_shader->use();

	// Opengl::glBindBuffer(GL_ARRAY_BUFFER, this->_mesh.getVbo());
	// Opengl::glBufferSubData(this->_mesh.getVbo(), 0, num_vertices * 2 * sizeof(float), buffer);

	// Opengl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_mesh.getEbo());
	// Opengl::glBufferSubData(this->_mesh.getEbo(), 0, num_indices * sizeof(GLuint), indices.data());

	// Render::project_pointsOrth(projection);
	// projection[13] = 1;
    // this->_shader->setMat4("projection", projection);

	// Opengl::glBindVertexArray(this->_mesh.getVao());
	// glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
}