#ifndef ENTITY_HPP

# define ENTITY_HPP

# include "Mesh.hpp"
# include "Render.hpp"

class Entity
{
	private:
		static std::vector<Entity *>	_objs;

	protected:
		Shaders					*_shader;
		Mesh					_mesh;
		int						_colorId;
		bool					_selected;
		bool					_isGizmo;
		std::array<float, 3>	_color;

	protected:
		void		rotate_x(float *mat) const;
		void		rotate_y(float *mat) const;
		void		rotate_z(float *mat) const;
		void		scale(float *mat) const;


	public:
		Entity(void);
		Entity(Shaders *shader, Mesh mesh, int flag);
		Entity &operator=(Entity const &rhs);
		Entity	operator+(Entity const &rhs) const;
		~Entity();
		void								setUniformColor(int flag);
		void								setGizmo(bool flag);
		void								addBack(void);
		int									getColorId() const;
		Shaders								*getShader() const;
		bool								getSelected() const;
		const Mesh							&getMesh() const;
		void								setSelected(bool select);
		void								setColors(float r, float g, float b);
		const std::array<float, 3>			&getColors(void) const;
		static const std::vector<Entity *>	&cstGetObjs();
		static std::vector<Entity *>			&getObjs();
		static void							deselectAll();
		void								setPos(float x, float y, float z);
		void								setRot(float x, float y, float z);
		void								setScale(float x, float y, float z);
		void								draw(int colorId) const;
};


#endif