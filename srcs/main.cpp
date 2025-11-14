#include "Shapes.hpp"

GLuint initFrameBuffer()
{
	GLuint pickingFBO;
	GLuint pickingTexture;
	GLuint pickingDepth;

	int width = WIDTH;
	int height = HEIGHT;

	// 1. Créer le FBO
	Opengl::glGenFramebuffers(1, &pickingFBO);
	Opengl::glBindFramebuffer(GL_FRAMEBUFFER, pickingFBO);

	// 2. Créer la texture qui stockera les IDs (RGB)
	glGenTextures(1, &pickingTexture);
	glBindTexture(GL_TEXTURE_2D, pickingTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Attacher la texture au FBO
	Opengl::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pickingTexture, 0);

	// 3. Créer un Renderbuffer pour la profondeur
	Opengl::glGenRenderbuffers(1, &pickingDepth);
	Opengl::glBindRenderbuffer(GL_RENDERBUFFER, pickingDepth);
	Opengl::glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	Opengl::glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, pickingDepth);

	// 4. Vérifier que le FBO est complet
	if (Opengl::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("Erreur : FBO de picking non complet !\n");

	Opengl::glBindFramebuffer(GL_FRAMEBUFFER, 0); // détacher
	//Opengl::glDeleteRenderbuffers(1, &pickingDepth);
	//Opengl::glDeleteTextures(1, &pickingTexture);
	//Opengl::glDeleteFramebuffers(1, &pickingFBO);
	return pickingFBO;
}

static void drawScene(GLuint buffer, std::vector<Entity> &objs, Grid &grid, int pickedColor)
{
	Opengl::glBindFramebuffer(GL_FRAMEBUFFER, buffer);
	glViewport(0, 0, WIDTH, HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (Entity &obj : objs)
	{
		if (buffer)
			obj.setUniformColor(1);
		else
			obj.setUniformColor(0);
		obj.draw(pickedColor);
	}
	if (!buffer && Menu::getEnableMouse())
		grid.draw();
	Opengl::glBindVertexArray(0);
}

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
	std::vector<Entity> objs = {plane, cube, cube2, tri, tr2, tr3, tr4};
	glfwSetInputMode(Opengl::getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	float x = 0, y = 0, z = 0;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetCursorPos(Opengl::getWindow(), WIDTH / 2, HEIGHT / 2);
	glfwSetInputMode(Opengl::getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	GLuint	frameBuffer = initFrameBuffer();
	while( glfwGetKey(Opengl::getWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(Opengl::getWindow()) == 0 )
	{
		if (!Menu::getEnableMouse())
		{
			objs[1].setRot(x, y, z);
			objs[3].setRot(0, y, 0);
			objs[4].setRot(M_PI, y, 0);
			objs[5].setRot(x, 0, -M_PI / 2);
			objs[6].setRot(x, 0, M_PI / 2);
			x += 0.07;
			y += 0.07;
			z += 0.07;
		}
		Render::manageKeys();
		drawScene(frameBuffer, objs, grid, -1);
		double xpos, ypos;
		unsigned char pixel[3];
		glfwGetCursorPos(Opengl::getWindow(), &xpos, &ypos);
		Opengl::glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		glReadPixels(xpos, HEIGHT - ypos - 1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel);
		Opengl::glBindFramebuffer(GL_FRAMEBUFFER, 0);

		int pickedID = Render::decodeColorId(pixel);

		drawScene(0, objs, grid, pickedID);
		glfwSwapBuffers(Opengl::getWindow());
		glfwPollEvents();
	}
	base.supr();
	sol.supr();
	glfwDestroyWindow(Opengl::getWindow());
	glfwTerminate();
	return (0);
}
