#include "Mesh.hpp"
#include <cmath>

Mesh &Mesh::operator=(Mesh const &rhs)
{
	if (this == &rhs)
		return *this;
	this->_vertices = rhs._vertices;
	this->_indices = rhs._indices;
	this->_indicesLine = rhs._indicesLine;
	this->_centers = rhs._centers;
	this->_indexCount = rhs._indexCount;
	this->_indexCountLine = rhs._indexCountLine;
	this->_pos = rhs._pos;
	this->_rot = rhs._rot;
	this->_scale = rhs._scale;

	Opengl::glDeleteVertexArrays(1, &_vao);
	Opengl::glDeleteVertexArrays(1, &_vaoLine);
	Opengl::glDeleteBuffers(1, &_vbo);
	Opengl::glDeleteBuffers(1, &_ebo);
	Opengl::glDeleteBuffers(1, &_eboLine);

	Opengl::glGenVertexArrays(1, &_vao);
	Opengl::glGenVertexArrays(1, &_vaoLine);
	Opengl::glGenBuffers(1, &_vbo);
	Opengl::glGenBuffers(1, &_ebo);
	Opengl::glGenBuffers(1, &_eboLine);

	Opengl::glBindVertexArray(_vao);

	// buffer des sommets
	Opengl::glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	Opengl::glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);
	Opengl::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	Opengl::glEnableVertexAttribArray(0);

	//buffer des indices (faces)
	Opengl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	Opengl::glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint), _indices.data(), GL_STATIC_DRAW);

	Opengl::glBindVertexArray(_vaoLine);

	// buffer des sommets
	Opengl::glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	Opengl::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	Opengl::glEnableVertexAttribArray(0);

	//buffer des indices (faces)
	Opengl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboLine);
	Opengl::glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicesLine.size() * sizeof(GLuint), _indicesLine.data(), GL_STATIC_DRAW);

	Opengl::glBindVertexArray(0);
	Opengl::glBindBuffer(GL_ARRAY_BUFFER, 0);
	Opengl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return *this;
}

Mesh Mesh::operator+(Mesh const &rhs) const
{
    Mesh res;

    std::vector<float> vert = this->_vertices, vert2 = rhs._vertices;

	float cx = cosf(this->_rot[0]);
	float sx = sinf(this->_rot[0]);
	float cy = cosf(this->_rot[1]);
	float sy = sinf(this->_rot[1]);
	float cz = cosf(this->_rot[2]);
	float sz = sinf(this->_rot[2]);

	for (size_t i = 0; i < vert.size(); i+=3)
	{
		vert[i] *= this->_scale[0];
		vert[i + 1] *= this->_scale[1];
		vert[i + 2] *= this->_scale[2];

		//x
		
		float y1 = vert[i + 1] * cx - vert[i + 2] * sx;
		float z1 = vert[i + 1] * sx + vert[i + 2] * cx;
		vert[i + 1] = y1;
		vert[i + 2] = z1;

		//Y
		float x1 = vert[i] * cy + vert[i + 2] * sy;
		z1 = -vert[i] * sy + vert[i + 2] * cy;
		vert[i] = x1;
		vert[i + 2] = z1;

		//Z
		x1 = vert[i] * cz - vert[i + 1] * sz;
		y1 = vert[i] * sz + vert[i + 1] * cz;
		vert[i] = x1;
		vert[i + 1] = y1;

		vert[i] += this->_pos[0];
		vert[i + 1] += this->_pos[1];
		vert[i + 2] += this->_pos[2];
	}
	cx = cosf(rhs._rot[0]);
    sx = sinf(rhs._rot[0]);
    cy = cosf(rhs._rot[1]);
    sy = sinf(rhs._rot[1]);
    cz = cosf(rhs._rot[2]);
    sz = sinf(rhs._rot[2]);

	for (size_t i = 0; i < vert2.size(); i+=3)
	{
		vert2[i] *= rhs._scale[0];
		vert2[i + 1] *= rhs._scale[1];
		vert2[i + 2] *= rhs._scale[2];

		float y1 = vert2[i + 1] * cx - vert2[i + 2] * sx;
		float z1 = vert2[i + 1] * sx + vert2[i + 2] * cx;
		vert2[i + 1] = y1;
		vert2[i + 2] = z1;

		//Y
		float x1 = vert2[i] * cy + vert2[i + 2] * sy;
		z1 = -vert2[i] * sy + vert2[i + 2] * cy;
		vert2[i] = x1;
		vert2[i + 2] = z1;

		//Z
		x1 = vert2[i] * cz - vert2[i + 1] * sz;
		y1 = vert2[i] * sz + vert2[i + 1] * cz;
		vert2[i] = x1;
		vert2[i + 1] = y1;

		vert2[i] += rhs._pos[0];
		vert2[i + 1] += rhs._pos[1];
		vert2[i + 2] += rhs._pos[2];
	}
    vert.insert(vert.end(), vert2.begin(), vert2.end());

    GLuint vertexCountThis = this->_vertices.size() / 3; // 3 floats par vertex
    std::vector<GLuint> indices = this->_indices;
    for (auto idx : rhs._indices)
        indices.push_back(idx + vertexCountThis);

    std::vector<GLuint> indicesLine = this->_indicesLine;
    for (auto idx : rhs._indicesLine)
        indicesLine.push_back(idx + vertexCountThis);

    res = Mesh(vert, indices, indicesLine);

    res._centers[0] = (this->_centers[0] + rhs._centers[0]) / 2.0f;
    res._centers[1] = (this->_centers[1] + rhs._centers[1]) / 2.0f;
    res._centers[2] = (this->_centers[2] + rhs._centers[2]) / 2.0f;

    return res;
}


//constructors/destructors---------------------------------

Mesh::Mesh(void): _vao(0), _vaoLine(0), _vbo(0), _ebo(0), _eboLine(0), _indexCount(0), _indexCountLine(0)
{
	_pos[0] = _pos[1] = _pos[2] = 0;
	_scale[0] = _scale[1] = _scale[2] = 1;
	_rot[0] = _rot[1] = _rot[2] = 0;
}

Mesh::Mesh(const std::vector<float> &vertices, const std::vector<GLuint> &indices)
{
	Opengl::glGenVertexArrays(1, &_vao);
	Opengl::glGenBuffers(1, &_vbo);
	Opengl::glGenBuffers(1, &_ebo);

	Opengl::glBindVertexArray(_vao);

	// buffer des sommets
	Opengl::glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	Opengl::glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
	Opengl::glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	Opengl::glEnableVertexAttribArray(0);

	//buffer des indices (faces)
	Opengl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	Opengl::glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_DYNAMIC_DRAW);

	Opengl::glBindVertexArray(0);
	Opengl::glBindBuffer(GL_ARRAY_BUFFER, 0);

	this->_indexCount = 0;
	this->_indexCountLine = 0;
	this->_centers[0] = this->_centers[1] = this->_centers[2] = 0;
	size_t vertexCount = vertices.size() / 2;
	for (size_t i = 0; i < vertices.size(); i += 2)
	{
		this->_centers[0] += vertices[i + 0];
		this->_centers[1] += vertices[i + 1];
	}
	this->_centers[0] /= vertexCount;
	this->_centers[1] /= vertexCount;
	this->_centers[1] = 0;
	this->_vertices = vertices;
	_pos[0] = _pos[1] = _pos[2] = 0;
	_scale[0] = _scale[1] = _scale[2] = 1;
	_rot[0] = _rot[1] = _rot[2] = 0;
	this->_indices = {};
	this->_indicesLine = {};
}

Mesh::Mesh(const std::vector<float> &vertices, const std::vector<GLuint> &indices, const std::vector<GLuint> &indicesLine)
{
	Opengl::glGenVertexArrays(1, &_vao);
	Opengl::glGenVertexArrays(1, &_vaoLine);
	Opengl::glGenBuffers(1, &_vbo);
	Opengl::glGenBuffers(1, &_ebo);
	Opengl::glGenBuffers(1, &_eboLine);

	Opengl::glBindVertexArray(_vao);

	// buffer des sommets
	Opengl::glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	Opengl::glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	Opengl::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	Opengl::glEnableVertexAttribArray(0);

	//buffer des indices (faces)
	Opengl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	Opengl::glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	Opengl::glBindVertexArray(_vaoLine);

	// buffer des sommets
	Opengl::glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	Opengl::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	Opengl::glEnableVertexAttribArray(0);

	//buffer des indices (faces)
	Opengl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboLine);
	Opengl::glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLine.size() * sizeof(GLuint), indicesLine.data(), GL_STATIC_DRAW);

	Opengl::glBindVertexArray(0);
	Opengl::glBindBuffer(GL_ARRAY_BUFFER, 0);
	Opengl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	this->_indexCount = indices.size();
	this->_indexCountLine = indicesLine.size();
	this->_centers[0] = this->_centers[1] = this->_centers[2] = 0;
	size_t vertexCount = vertices.size() / 3;
	for (size_t i = 0; i < vertices.size(); i += 3)
	{
		this->_centers[0] += vertices[i + 0];
		this->_centers[1] += vertices[i + 1];
		this->_centers[2] += vertices[i + 2];
	}
	this->_centers[0] /= vertexCount;
	this->_centers[1] /= vertexCount;
	this->_centers[2] /= vertexCount;
	_pos[0] = _pos[1] = _pos[2] = 0;
	_scale[0] = _scale[1] = _scale[2] = 1;
	_rot[0] = _rot[1] = _rot[2] = 0;
	this->_vertices = vertices;
	this->_indices = indices;
	this->_indicesLine = indicesLine;
}

Mesh::Mesh(Mesh const &rhs)
{
	*this = rhs;
}


Mesh::~Mesh(void) {}

//Member functions-----------------------------------------

void	Mesh::setPos(float x, float y, float z)
{
	this->_pos[0] = x;
	this->_pos[1] = y;
	this->_pos[2] = z;
}

void	Mesh::setRot(float x, float y, float z)
{
	this->_rot[0] = x;
	this->_rot[1] = y;
	this->_rot[2] = z;
}

void	Mesh::setScale(float x, float y, float z)
{
	this->_scale[0] = x;
	this->_scale[1] = y;
	this->_scale[2] = z;
}

void	Mesh::setCenters(float x, float y, float z)
{
	this->_centers[0] = x;
	this->_centers[1] = y;
	this->_centers[2] = z;
}

void Mesh::draw(const Shaders &shader, int flag) const
{
	Opengl::glBindVertexArray(this->_vao);
	glDrawElements(GL_TRIANGLES, this->_indexCount, GL_UNSIGNED_INT, 0);
	if (flag)
	{
		shader.setInt("uline", flag);
		Opengl::glBindVertexArray(this->_vaoLine);
		glDrawElements(GL_LINES, this->_indexCountLine, GL_UNSIGNED_INT, 0);
	}
}

const std::array<float, 3> &Mesh::getPos(void) const
{
	return this->_pos;
}

const std::array<float, 3> &Mesh::getRot(void) const
{
	return this->_rot;
}

const std::array<float, 3> &Mesh::getScale(void) const
{
	return this->_scale;
}

const std::array<float, 3> &Mesh::getCenters(void) const
{
	return this->_centers;
}

void	Mesh::newVbo(std::vector<float> &vertices) const
{
	Opengl::glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
	Opengl::glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * vertices.size(), vertices.data());
}

std::vector<float> Mesh::getVertices() const
{
	return this->_vertices;
}

GLuint Mesh::getVao() const
{
	return this->_vao;
}

GLuint Mesh::getVbo() const
{
	return this->_vbo;
}

GLuint Mesh::getEbo() const
{
	return this->_ebo;
}