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
		std::array<float, 3>	_pos;
		std::array<float, 3>	_rot;
		std::array<float, 3>	_scale;

	public:
		Mesh(const std::vector<float> &vertices, const std::vector<GLuint> &indices, const std::vector<GLuint> &indicesLine);
		Mesh(const std::vector<float> &vertices, const std::vector<GLuint> &indices);
		Mesh &operator=(Mesh const &rhs);
		Mesh operator+(Mesh const &rhs) const;
		Mesh(Mesh const &rhs);
		Mesh(void);
		~Mesh(void);
		void						draw(const Shaders &shader, int flag) const;
		std::vector<float>			getVertices() const;
		void						newVbo(std::vector<float> &vertices) const;
		void						setCenters(float x, float y, float z);
		const std::array<float, 3>	&getCenters(void) const;
		void						setPos(float x, float y, float z);
		void						setRot(float x, float y, float z);
		void						setScale(float x, float y, float z);
		const std::array<float, 3>	&getPos(void) const;
		const std::array<float, 3>	&getRot(void) const;
		const std::array<float, 3>	&getScale(void) const;
		GLuint						getVao(void) const;
		GLuint						getVbo(void) const;
		GLuint						getEbo(void) const;
};


#endif