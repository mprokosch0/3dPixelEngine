#include "Entity.hpp"

int main()
{
	Shaders	base, sol;
	try
	{
		Opengl::initiateWindow("test");
		base = Shaders("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
		sol = Shaders("shaders/vertexShader.glsl", "shaders/fragmentShaderPlane.glsl");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	std::vector<float> points({0, -2, 0,
							   0, 2, 0,
							    5, -2, 0,
								5, 2, 0,
							   0, -2, 5,
							   0, 2, 5,
							    5, -2, 5,
								5, 2, 5});
	std::vector<float> points2({-8, -8, -8,
							   -8, 8, -8,
							    8, -8, -8,
								8, 8, -8,
							   -8, -8, 8,
							   -8, 8, 8,
							    8, -8, 8,
								8, 8, 8});
	std::vector<float> points3({-50, -1, -50,
							   50, -1, -50,
							    -50, -1, 50,
								50, -1, 50});
	std::vector<float> points4({-100, -1, -50,
							   -75, -1, -50,
							    -87, 30, -45,
								-87, -1, -37});
	std::vector<int> faces = {
			0, 1, 2,  2, 1, 3,
			4, 5, 6,  6, 5, 7,
			0, 1, 4,  4, 1, 5,
			2, 3, 6,  6, 3, 7,
			1, 3, 5,  5, 3, 7,
			0, 2, 4,  4, 2, 6
		};
	
	std::vector<int> faces2 = {
			0, 1, 2, 2, 1, 3
		};

	std::vector<int> faces3 = {
			0, 1, 2, 2, 1, 3,
			0, 1, 3, 2, 0, 3
		};
	
	Mesh mesh(points, faces);
	Mesh cube2m(points2, faces);
	Mesh planem(points3, faces2);
	Mesh t(points4, faces3);
	Entity	cube2(&base, &cube2m);
	Entity	tri(&base, &t);
	Entity	cube(&base, &mesh);
	Entity	plane(&sol, &planem);
	cube.setScale(4, 2, 3);
	cube.setPos(0, 5, 0);
	glfwSetInputMode(Opengl::getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	float x = 0, y = 0, z = 0;
	glfwSetCursorPos(Opengl::getWindow(), WIDTH / 2, HEIGHT / 2);
	glfwSetInputMode(Opengl::getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	while( glfwGetKey(Opengl::getWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(Opengl::getWindow()) == 0 )
	{
		cube.setRot(x, y, z);
		tri.setRot(x, y, z);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Render::manageKeys();
		tri.draw();
		cube.draw();
		//cube2.draw();
		plane.draw();
		Opengl::glBindVertexArray(0);
		glfwSwapBuffers(Opengl::getWindow());
		glfwPollEvents();
		x += 0.007;
		y += 0.07;
		z += 0.07;
	}
	base.supr();
	glfwDestroyWindow(Opengl::getWindow());
	glfwTerminate();
	return (0);
}
