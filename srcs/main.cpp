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
	Opengl::glDeleteRenderbuffers(1, &pickingDepth);
	Opengl::glDeleteTextures(1, &pickingTexture);
	return pickingFBO;
}

static void	keyGestion(float &x, float &y, float &z)
{
	(void)x, (void)y, (void)z;
	// std::vector<Entity *> objs = Entity::getObjs();
	// // if (!Menu::getEnableMouse())
	// // {
	// 	objs[4]->setRot(z, 0, 0);
	// 	//x += 0.07;
	// 	//y += 0.07;
	// 	z += 0.007;
	// //}
	Render::manageKeys();
}

static void drawNormal(GLuint buffer, Grid &grid, int pickedColor)
{
	std::vector<Entity *> objs = Entity::getObjs();
	Opengl::glBindFramebuffer(GL_FRAMEBUFFER, buffer);
	glViewport(0, 0, Opengl::getWidth(), Opengl::getHeight());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (Menu::getEnableMouse())
		grid.draw();
	for (Entity *obj : objs)
	{
		if (Menu::getEnableMouse() && obj->getSelected())
		{
			Gizmo::setObj(obj);
			Gizmo::draw(pickedColor);
		}
		obj->setUniformColor(0);
		if (pickedColor == obj->getColorId() && Menu::getEnableMouse() && !obj->getSelected())
			obj->draw(1);
		else if (pickedColor == obj->getColorId() && Menu::getEnableMouse() && obj->getSelected())
			obj->draw(2);
		else
			obj->draw(0);
	}
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
		if (Menu::getEnableMouse() && obj->getSelected())
			Gizmo::drawPickColor();
	}
	Opengl::glBindVertexArray(0);
}

static void manageHud(Hud &hud, Text &text)
{
	const std::vector<Entity *> &objs = Entity::getObjs();
	(void)hud, (void)text;
	for (const Entity *obj : objs)
	{
		if (obj->getSelected())
		{
			hud.draw();
			return ;
		}
	}
}

static void	drawScene(Grid &grid, Hud &hud, Text &text, GLuint frameBuffer)
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
		manageHud(hud, text);
}

int main()
{
	Shaders	base, sol, quad, hudS, textS, line;
	int	width, height;
	try
	{
		Opengl::initiateWindow("engine");
		base = Shaders("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
		base.addBack();
		sol = Shaders("shaders/vertexShader.glsl", "shaders/fragmentShaderPlane.glsl");
		sol.addBack();
		quad = Shaders("shaders/vertexShader.glsl", "shaders/fragmentShaderGrid.glsl");
		quad.addBack();
		hudS = Shaders("shaders/vertexShaderHud.glsl", "shaders/fragmentShaderHud.glsl");
		hudS.addBack();
		textS = Shaders("shaders/vertexShaderHud.glsl", "shaders/fragmentShaderText.glsl");
		textS.addBack();
		line = Shaders("shaders/vertexShaderLine.glsl", "shaders/fragmentShaderText.glsl");
		line.addBack();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	Grid	grid(&quad);
	Text	text(&textS);
	Gizmo::genGiz();
	Hud		hud(&hudS, 0, 0, 500, Opengl::getHeight());
	Entity obj, obj2, obj3, obj4, obj5;
	obj = Plane(&sol, 0, -1, 0, 0, 0, 0, 50, 1, 100);
	obj.addBack();
	obj2 = Cone(&base, -10, 5, -10, 0, 0, 0, 10, 10, 10);
	obj2.addBack();
	obj3 = Cube(&base, 0, 10, 0, M_PI_4, 0, 0, 2, 2, 2);
	obj3.addBack();
	obj4 = Cube(&base, 10, 5, -10, 0, M_PI / 2, 0, 5, 5, 5);
	obj4.addBack();
	obj5 = Cube(&base, 10, 5, 10, 0, 0, 0, 8, 8, 8);
	obj5.addBack();
	glfwSetInputMode(Opengl::getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
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
		drawScene(grid, hud, text, frameBuffer);
		glfwSwapBuffers(Opengl::getWindow());
		glfwPollEvents();
	}

	base.supr();
	sol.supr();
	Opengl::glDeleteFramebuffers(1, &frameBuffer);
	glfwDestroyWindow(Opengl::getWindow());
	glfwDestroyWindow(Opengl::getWindow2());
	glfwTerminate();
	return (0);
}
