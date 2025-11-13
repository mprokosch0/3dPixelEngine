#ifndef MESH_HPP

# define MESH_HPP

# include "Shaders.hpp"
# include <array>

class Shaders;

class Mesh
{
	private:
		GLuint					_vao;
		GLuint					_vaoLine;
		GLuint					_vbo;
		//GLuint					_vboUvs;
		GLuint					_ebo;
		GLuint					_eboLine;
		GLsizei					_indexCount;
		GLsizei					_indexCountLine;
		std::array<float, 3>	_centers;

	public:
		Mesh(const std::vector<float> &vertices, const std::vector<GLuint> &indices, const std::vector<GLuint> &indicesLine);
		Mesh &operator=(Mesh const &rhs);
		Mesh(Mesh const &rhs);
		Mesh(void);
		~Mesh(void);
		void						draw(const Shaders &shader) const;
		const std::array<float, 3>	&getCenters(void) const;
		GLuint						getVao() const;
};


#endif