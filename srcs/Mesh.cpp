#include "Mesh.hpp"

Mesh &Mesh::operator=(Mesh const &rhs)
{
	if (this == &rhs)
		return *this;
	this->_centers = rhs._centers;
	this->_ebo = rhs._ebo;
	this->_eboLine = rhs._eboLine;
	this->_indexCount = rhs._indexCount;
	this->_indexCountLine = rhs._indexCountLine;
	this->_vao = rhs._vao;
	this->_vaoLine = rhs._vaoLine;
	this->_vbo = rhs._vbo;
	return *this;
}

//constructors/destructors---------------------------------

Mesh::Mesh(void): _vao(0), _vaoLine(0), _vbo(0), _ebo(0), _eboLine(0), _indexCount(0), _indexCountLine(0){}

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

void Mesh::draw(const Shaders &shader, int flag) const
{
	Opengl::glBindVertexArray(this->_vao);
	glDrawElements(GL_TRIANGLES, this->_indexCount, GL_UNSIGNED_INT, 0);
	if (flag)
	{
		shader.setInt("uline", Menu::getEnableMouse());
		Opengl::glBindVertexArray(this->_vaoLine);
		glDrawElements(GL_LINES, this->_indexCountLine, GL_UNSIGNED_INT, 0);
	}
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