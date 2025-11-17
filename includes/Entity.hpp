#ifndef ENTITY_HPP

# define ENTITY_HPP

# include "Mesh.hpp"
# include "Render.hpp"

class Mesh;
class Shaders;

class Entity
{
	private:
		static std::vector<Entity *>	_objs;

	protected:
		Shaders	*_shader;
		Mesh	_mesh;
		int		_colorId;
		bool	_selected;
		float	_pos[3];
		float	_rot[3];
		float	_scale[3];

	protected:
		void		rotate_x(float *mat) const;
		void		rotate_y(float *mat) const;
		void		rotate_z(float *mat) const;
		void		scale(float *mat) const;


	public:
		Entity(void);
		Entity(Shaders *shader, Mesh mesh, int flag);
		Entity &operator=(Entity const &rhs);
		~Entity();
		void								setUniformColor(int flag);
		int									getColorId() const;
		bool								getSelected() const;
		void								setSelected(bool select);
		static const std::vector<Entity *>	&cstGetObjs();
		static std::vector<Entity *>			&getObjs();
		static void							deselectAll();
		void								setPos(float x, float y, float z);
		void								setRot(float x, float y, float z);
		void								setScale(float x, float y, float z);
		void								draw(int colorId) const;
};


#endif