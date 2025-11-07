#ifndef RENDER_HPP

# define RENDER_HPP

# include "Opengl.hpp"
# include <cmath>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# ifndef M_PI_2
#  define M_PI_2 1.57079632679489661923
#endif

class Render
{
	private:
		Render(void);
		~Render();
		static void mouseCalculs(double posX, double posY);

	private:
		static GLuint	_vao;
		static GLuint	_vbo;
		static GLuint	_ebo;
		//rotation
		static float	_angleX;
		static float	_angleY;
		static float	_angleZ;
		//center
		static float	_centerX;
		static float	_centerY;
		static float	_centerZ;
		//translation
		static float	_tX;
		static float	_tY;
		static float	_tZ;
	
	public:
		static void		initBuffers(std::vector<float> points, std::vector<int> faces);
		static void		bindMatrices(void);
		static GLuint	getVao(void);
		static GLuint	getVbo(void);
		static GLuint	getEbo(void);
		static void		manageKeys(void);
};



#endif