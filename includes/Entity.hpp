#ifndef ENTITY_HPP

# define ENTITY_HPP

# include "Mesh.hpp"
# include "Render.hpp"

class Entity
{
	private:
		Shaders	*_shader;
		Mesh	*_mesh;
		float	_pos[3];
		float	_rot[3];
		float	_scale[3];

	private:
		void		rotate_x(float *mat) const;
		void		rotate_y(float *mat) const;
		void		rotate_z(float *mat) const;
		void		scale(float *mat) const;


	public:
		Entity(Shaders *shader, Mesh *mesh);
		~Entity();
		void	setPos(float x, float y, float z);
		void	setRot(float x, float y, float z);
		void	setScale(float x, float y, float z);
		void	draw(void) const;
};


#endif