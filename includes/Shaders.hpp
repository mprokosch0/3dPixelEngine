#ifndef SHADERS_HPP

#define SHADERS_HPP

#include "Opengl.hpp"

class Shaders
{
	private:
		GLuint	_id;

	public:
		Shaders(void);
		Shaders(std::string vertexSrc, std::string fragmentSrc);
		~Shaders(void);
		GLuint	getId(void) const;
		void	use(void) const;
		void	supr(void) const;
		void	setMat4(const std::string &name, const float *mat4) const;
};

GLuint	createShaderProgram(std::string &vertexSrc, std::string &fragmentSrc);
void	oneLine(std::string &dest, std::string file);

#endif