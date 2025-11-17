#include "Shapes.hpp"

GLuint initFrameBuffer()
{
	GLuint pickingFBO;
	GLuint pickingTexture;
	GLuint pickingDepth;

	int width = Opengl::getWidth();
	int height = Opengl::getHeight();

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

static void	keyGestion(float &x, float &y, float &z)
{
	std::vector<Entity *> objs = Entity::getObjs();
	if (!Menu::getEnableMouse())
	{
		objs[1]->setRot(x, y, z);
		objs[3]->setRot(0, y, 0);
		objs[4]->setRot(M_PI, y, 0);
		objs[5]->setRot(x, 0, -M_PI / 2);
		objs[6]->setRot(x, 0, M_PI / 2);
		x += 0.07;
		y += 0.07;
		z += 0.07;
	}
	Render::manageKeys();
}

static void drawNormal(GLuint buffer, Grid &grid, int pickedColor)
{
	std::vector<Entity *> objs = Entity::getObjs();
	Opengl::glBindFramebuffer(GL_FRAMEBUFFER, buffer);
	glViewport(0, 0, Opengl::getWidth(), Opengl::getHeight());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (Entity *obj : objs)
	{
		obj->setUniformColor(0);
		if (pickedColor == obj->getColorId() && Menu::getEnableMouse())
			obj->draw(1);
		else
			obj->draw(0);
	}
	if (Menu::getEnableMouse())
		grid.draw();
	Opengl::glBindVertexArray(0);
}

static void drawPickColor(GLuint buffer)
{
	std::vector<Entity *> objs = Entity::getObjs();
	Opengl::glBindFramebuffer(GL_FRAMEBUFFER, buffer);
	glViewport(0, 0, Opengl::getWidth(), Opengl::getHeight());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (Entity *obj : objs)
	{
		obj->setUniformColor(1);
		obj->draw(0);
	}
	Opengl::glBindVertexArray(0);
}

static void manageHud(Hud &hud)
{
	const std::vector<Entity *> &objs = Entity::getObjs();
	for (const Entity *obj : objs)
	{
		if (obj->getSelected())
		{
			hud.draw();
			return ;
		}
	}
}

static void	drawScene(Grid &grid, Hud &hud, GLuint frameBuffer)
{
	static float x = 0, y = 0, z = 0;
	double xpos, ypos;
	unsigned char pixel[3];

	keyGestion(x, y, z);
	drawPickColor(frameBuffer);
	
	glfwGetCursorPos(Opengl::getWindow(), &xpos, &ypos);
	Opengl::glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glReadPixels(xpos, Opengl::getHeight() - ypos - 1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel);
	Opengl::glBindFramebuffer(GL_FRAMEBUFFER, 0);

	int pickedID = Render::decodeColorId(pixel);
	Render::mouseControls(Opengl::getWindow(), pickedID);
	drawNormal(0, grid, pickedID);
	if (Menu::getEnableMouse())
		manageHud(hud);
}

int main()
{
	Shaders	base, sol, quad, hudS;
	int	width, height;
	try
	{
		Opengl::initiateWindow("engine");
		base = Shaders("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
		sol = Shaders("shaders/vertexShader.glsl", "shaders/fragmentShaderPlane.glsl");
		quad = Shaders("shaders/vertexShader.glsl", "shaders/fragmentShaderGrid.glsl");
		hudS = Shaders("shaders/vertexShaderHud.glsl", "shaders/fragmentShaderHud.glsl");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	Grid	grid(&quad);
	Hud		hud(&hudS, 0, 0, 500, Opengl::getHeight());
	Plane(&sol, (float []){-1, -1, -1}, (float []){0, 0, 0}, (float []){50, 1, 50});
	Cube(&base, (float []){10, 10, 10}, (float []){0, 0, 0}, (float []){2, 2, 2});
	Cube(&base, (float []){-10, 10, -10}, (float []){2, 0, 2}, (float []){2, 2, 2});
	Triangle(&base, (float []){0, 0, 0}, (float []){0, 0, 0}, (float []){5, 5, 5});
	Triangle(&base, (float []){0, 6, 0}, (float []){M_PI, 0, 0}, (float []){5, 5, 5});
	Triangle(&base, (float []){3, 3, 0}, (float []){M_PI / 2, 0, -M_PI / 2}, (float []){5, 5, 5});
	Triangle(&base, (float []){-3, 3, 0}, (float []){M_PI / 2, 0, M_PI / 2}, (float []){5, 5, 5});
	glfwSetInputMode(Opengl::getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetCursorPos(Opengl::getWindow(), Opengl::getWidth() / 2, Opengl::getHeight() / 2);
	glfwSetInputMode(Opengl::getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	GLuint	frameBuffer = initFrameBuffer();

	while( glfwGetKey(Opengl::getWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(Opengl::getWindow()) == 0 )
	{
		glEnable(GL_DEPTH_TEST);
		glfwGetWindowSize(Opengl::getWindow(), &width, &height);
		Opengl::setDim(width, height);
		drawScene(grid, hud, frameBuffer);
		glfwSwapBuffers(Opengl::getWindow());
		glfwPollEvents();
	}

	base.supr();
	sol.supr();
	glfwDestroyWindow(Opengl::getWindow());
	glfwTerminate();
	return (0);
}
