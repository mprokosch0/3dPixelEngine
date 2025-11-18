#ifndef MESH_HPP

# define MESH_HPP

# include "Shaders.hpp"
# include <array>

class Shaders;

class Mesh
{
	private:
		std::vector<float>		_vertices;
		std::vector<GLuint>		_indices;
		std::vector<GLuint>		_indicesLine;
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
		Mesh(const std::vector<float> &vertices, const std::vector<GLuint> &indices);
		Mesh &operator=(Mesh const &rhs);
		Mesh(Mesh const &rhs);
		Mesh(void);
		~Mesh(void);
		void						draw(const Shaders &shader, int flag) const;
		std::vector<float>			getVertices() const;
		void						newVbo(std::vector<float> &vertices) const;
		void						setCenters(float x, float y, float z);
		const std::array<float, 3>	&getCenters(void) const;
		GLuint						getVao() const;
		GLuint						getVbo() const;
		GLuint						getEbo() const;
};


#endif