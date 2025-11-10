#ifndef MESH_HPP

# define MESH_HPP

# include "Shaders.hpp"
# include <array>

class Mesh
{
	private:
		GLuint					_vao;
		GLuint					_vbo;
		GLuint					_ebo;
		GLsizei					_indexCount;
		std::array<float, 3>	_centers;

	public:
		Mesh(const std::vector<float> &vertices, const std::vector<int> &indices);
		~Mesh(void);
		void						draw() const;
		const std::array<float, 3>	&getCenters(void) const;
};


#endif