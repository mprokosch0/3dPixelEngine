#include "Render.hpp"

int main()
{
	try
	{
		Opengl::initiateWindow("test");
		Opengl::initiateShaders();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	std::vector<float> points({-1, -1, -1,
							   -1, 1, -1,
							    1, -1, -1,
								1, 1, -1,
							   -1, -1, 1,
							   -1, 1, 1,
							    1, -1, 1,
								1, 1, 1});
	std::vector<int> faces = {
			0, 1, 2,  2, 1, 3,
			4, 5, 6,  6, 5, 7,
			0, 1, 4,  4, 1, 5,
			2, 3, 6,  6, 3, 7,
			1, 3, 5,  5, 3, 7,
			0, 2, 4,  4, 2, 6
		};
	Render::initBuffers(points, faces);
	glfwSetInputMode(Opengl::getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glfwSetCursorPos(Opengl::getWindow(), WIDTH / 2, HEIGHT / 2);
	glfwSetInputMode(Opengl::getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	while( glfwGetKey(Opengl::getWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(Opengl::getWindow()) == 0 )
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Opengl::glUseProgram(Opengl::getShaderProgram());
		Render::manageKeys();
		Render::bindMatrices();
		Opengl::glBindVertexArray(Render::getVao());
		glDrawElements(GL_TRIANGLES, faces.size(), GL_UNSIGNED_INT, 0);
		Opengl::glBindVertexArray(0);
		glfwSwapBuffers(Opengl::getWindow());
		glfwPollEvents();
	}
	Opengl::glDeleteProgram(Opengl::getShaderProgram());
	glfwDestroyWindow(Opengl::getWindow());
	glfwTerminate();
	return (0);
}
