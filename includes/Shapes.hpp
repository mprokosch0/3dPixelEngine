#ifndef SHAPES_HPP

# define SHAPES_HPP

# include "Entity.hpp"

class Cube: public Entity
{
	public:
		Cube(Shaders *shader, float _pos[3], float _rot[3], float _scale[3]);
		~Cube(void);
};

class Triangle: public Entity
{
	public:
		Triangle(Shaders *shader, float _pos[3], float _rot[3], float _scale[3]);
		~Triangle(void);
};

class Plane: public Entity
{
	public:
		Plane(Shaders *shader, float _pos[3], float _rot[3], float _scale[3]);
		~Plane(void);
};

class Sphere: public Entity
{
	public:
		Sphere(Shaders *shader, float _pos[3], float _rot[3], float _scale[3]);
		~Sphere(void);
};

class Cylinder: public Entity
{
	public:
		Cylinder(Shaders *shader, float _pos[3], float _rot[3], float _scale[3]);
		~Cylinder(void);
};

class Grid: public Entity
{
	public:
		Grid(Shaders *shader);
		~Grid(void);
		void draw() const;
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

#endif