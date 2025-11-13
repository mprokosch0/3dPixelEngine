#include "Shapes.hpp"

int main()
{
	Shaders	base, sol, quad;
	try
	{
		Opengl::initiateWindow("test");
		base = Shaders("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
		sol = Shaders("shaders/vertexShader.glsl", "shaders/fragmentShaderPlane.glsl");
		quad = Shaders("shaders/vertexShader.glsl", "shaders/fragmentShaderGrid.glsl");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	Grid	grid(&quad);
	Entity	cube2 = Cube(&base, (float []){-10, 10, -10}, (float []){2, 0, 2}, (float []){2, 2, 2});
	Entity	tri = Triangle(&base, (float []){0, 0, 0}, (float []){0, 0, 0}, (float []){5, 5, 5});
	Entity	tr2 = Triangle(&base, (float []){0, 6, 0}, (float []){M_PI, 0, 0}, (float []){5, 5, 5});
	Entity	tr4 = Triangle(&base, (float []){-3, 3, 0}, (float []){M_PI / 2, 0, M_PI / 2}, (float []){5, 5, 5});
	Entity	tr3 = Triangle(&base, (float []){3, 3, 0}, (float []){M_PI / 2, 0, -M_PI / 2}, (float []){5, 5, 5});
	Entity	cube = Cube(&base, (float []){10, 10, 10}, (float []){0, 0, 0}, (float []){2, 2, 2});
	Entity	plane = Plane(&sol, (float []){-1, -1, -1}, (float []){0, 0, 0}, (float []){50, 1, 50});
	glfwSetInputMode(Opengl::getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	float x = 0, y = 0, z = 0;
	glfwSetCursorPos(Opengl::getWindow(), WIDTH / 2, HEIGHT / 2);
	glfwSetInputMode(Opengl::getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	while( glfwGetKey(Opengl::getWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(Opengl::getWindow()) == 0 )
	{
		if (!Menu::getEnableMouse())
		{
			cube.setRot(x, y, z);
			tri.setRot(0, y, 0);
			tr2.setRot(M_PI, y, 0);
			tr3.setRot(x, 0, -M_PI / 2);
			tr4.setRot(x, 0, M_PI / 2);
			x += 0.07;
			y += 0.07;
			z += 0.07;
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Render::manageKeys();
		tri.draw();
		tr2.draw();
		tr3.draw();
		tr4.draw();
		cube.draw();
		cube2.draw();
		if (Menu::getEnableMouse())
			grid.draw();
		plane.draw();
		Opengl::glBindVertexArray(0);
		glfwSwapBuffers(Opengl::getWindow());
		glfwPollEvents();
	}
	base.supr();
	sol.supr();
	glfwDestroyWindow(Opengl::getWindow());
	glfwTerminate();
	return (0);
}
