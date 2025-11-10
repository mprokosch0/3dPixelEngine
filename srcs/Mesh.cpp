#include "Mesh.hpp"

//constructors/destructors---------------------------------

Mesh::Mesh(const std::vector<float> &vertices, const std::vector<int> &indices)
{
	Opengl::glGenVertexArrays(1, &_vao);
	Opengl::glGenBuffers(1, &_vbo);
	Opengl::glGenBuffers(1, &_ebo);

	Opengl::glBindVertexArray(_vao);

	// buffer des sommets
	Opengl::glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	Opengl::glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	Opengl::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	Opengl::glEnableVertexAttribArray(0);

	//buffer des indices (faces)
	Opengl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	Opengl::glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	Opengl::glBindVertexArray(0);
	this->_indexCount = indices.size();
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
}

Mesh::~Mesh(void) {}

//Member functions-----------------------------------------

void Mesh::draw() const
{
	Opengl::glBindVertexArray(this->_vao);
	glDrawElements(GL_TRIANGLES, this->_indexCount, GL_UNSIGNED_INT, 0);
}

const std::array<float, 3> &Mesh::getCenters(void) const
{
	return this->_centers;
}