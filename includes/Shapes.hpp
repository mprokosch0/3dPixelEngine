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

class Grid: public Entity
{
	public:
		Grid(Shaders *shader);
		~Grid(void);
		void draw() const;
};

#endif