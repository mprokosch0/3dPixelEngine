#ifndef RENDER_HPP

# define RENDER_HPP

# include "Shaders.hpp"
# include "Shapes.hpp"
# include <cmath>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# ifndef M_PI_2
#  define M_PI_2 1.57079632679489661923
#endif

class Entity;

class Render
{
	private:
		Render(void);
		~Render();
		static void	moveGizmo(double &lastX, double &lastY);
		static void mouseCalculs(double posX, double posY, double &lastX, double &lastY, double sensitivity);
		static void cameraMoveAngle(GLFWwindow *window, double &lastX, double &lastY);
		static void cameraMovePos(GLFWwindow *window);

	private:
		static GLuint	_frameBuffer;
		//rotation
		static float	_angleX;
		static float	_angleY;
		static float	_angleZ;
		//translation
		static float	_tX;
		static float	_tY;
		static float	_tZ;
	
	public:
		static void		manageKeys();
		static void		mouseControls(GLFWwindow *window, int colorId);
		static void		lookAt(float *mat, float eyeX, float eyeY, float eyeZ,
                        		float centerX, float centerY, float centerZ,
                        		float upX, float upY, float upZ);
		static void		rotate_x(float *mat);
		static void		rotate_y(float *mat);
		static void		rotate_z(float *mat);
		static void		project_points(float *mat);
		static void		project_pointsOrth(float *mat);
		static void		translate_obj(float *mat);
		static void		identityMat4(float *mat);
		static bool		invertMat4(const float mat4[16], float invOut[16]);
		static void		multiply4(float *a, float *b, float *result);
		static float	getTx();
		static float	getTy();
		static float	getTz();
		static int		decodeColorId(unsigned char pixel[3]);
		static GLuint	getFrameBuffer();
		
};



#endif