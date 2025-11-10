#ifndef RENDER_HPP

# define RENDER_HPP

# include "Shaders.hpp"
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
		//rotation
		static float	_angleX;
		static float	_angleY;
		static float	_angleZ;
		//translation
		static float	_tX;
		static float	_tY;
		static float	_tZ;
	
	public:
		static void		manageKeys(void);
		static void		lookAt(float *mat, float eyeX, float eyeY, float eyeZ,
                        		float centerX, float centerY, float centerZ,
                        		float upX, float upY, float upZ);
		static void		rotate_x(float *mat);
		static void		rotate_y(float *mat);
		static void		rotate_z(float *mat);
		static void		project_points(float *mat);
		static void		center_obj(float *mat);
		static void		translate_obj(float *mat);
		static void		identityMat4(float *mat);
		static void		multiply4(float *a, float *b, float *result);
		
};



#endif