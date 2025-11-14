#include "Shaders.hpp"

//constructors/destructors---------------------------------

Shaders::Shaders(void): _id(0){}

Shaders::Shaders(std::string vertexSrc, std::string fragmentSrc)
{
	std::string vertexDst, fragmentDst;
	oneLine(vertexDst, vertexSrc);
	if (vertexDst.empty())
		throw std::runtime_error("\033[31mvertexDst is empty\033[0m");
	oneLine(fragmentDst, fragmentSrc);
	if (fragmentDst.empty())
		throw std::runtime_error("\033[31mfragmentDst is empty\033[0m");
	_id = createShaderProgram(vertexDst, fragmentDst);
}

Shaders::~Shaders(void) {}

//Member functions-----------------------------------------

void Shaders::setMat4(const std::string &name, const float *mat4) const
{
	Opengl::glUniformMatrix4fv(Opengl::glGetUniformLocation(this->_id, name.c_str()), 1, GL_FALSE, mat4);
}

void Shaders::setInt(const std::string &name, const int nb) const
{
	Opengl::glUniform1i(Opengl::glGetUniformLocation(this->_id, name.c_str()), nb);
}

void Shaders::setFloat(const std::string &name, const float nb) const
{
	Opengl::glUniform1f(Opengl::glGetUniformLocation(this->_id, name.c_str()), nb);
}

GLuint Shaders::getId(void) const
{
	return this->_id;
}

void Shaders::use(void) const
{
	Opengl::glUseProgram(this->_id);
}

void Shaders::supr(void) const
{
	Opengl::glDeleteProgram(this->_id);
}
