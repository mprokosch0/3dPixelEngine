#ifndef SHAPES_HPP

# define SHAPES_HPP

# include "Entity.hpp"

class Cube: public Entity
{
	public:
		Cube(Shaders *shader, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, bool flag);
		~Cube(void);
};

class Triangle: public Entity
{
	public:
		Triangle(Shaders *shader, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, bool flag);
		~Triangle(void);
};

class Cone: public Entity
{
	public:
		Cone(Shaders *shader, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, bool flag);
		~Cone(void);
};

class Plane: public Entity
{
	public:
		Plane(Shaders *shader, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, bool flag);
		~Plane(void);
};

class Sphere: public Entity
{
	public:
		Sphere(Shaders *shader, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, bool flag);
		~Sphere(void);
};

class Cylinder: public Entity
{
	public:
		Cylinder(Shaders *shader, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, bool flag);
		~Cylinder(void);
};

class Grid: public Entity
{
	public:
		Grid(Shaders *shader);
		~Grid(void);
		void draw();
};

class Hud: public Entity
{
	public:
		Hud(Shaders *shader, float x, float y, float lenX, float lenY);
		~Hud(void);
		void draw() const;
};

class Text: public Entity
{
	public:
		Text(Shaders *shader);
		~Text(void);
		void draw(const char * text, float x, float y) const;
};

class Gizmo
{
	private:
		static std::array<Entity, 4>	_origin;
		static std::array<float, 3>		_centersObj;
		static std::array<float, 3>		_posObj;
		static std::array<float, 3>		_rotObj;
		static std::array<float, 3>		_scaleObj;
		Gizmo(void);
		~Gizmo(void);

	public:
		static void							draw(int colorId);
		static void							setObj(const std::array<float, 3> &enter, const std::array<float, 3> &pos,
													const std::array<float, 3> &rot, const std::array<float, 3> &scale);
		static const std::array<float, 3>	&getPos(void);
		static const std::array<float, 3>	&getCenters(void);
		static const std::array<float, 3>	&getRot(void);
		static const std::array<float, 3>	&getScale(void);
		static void							genGiz();
};

#endif