#include "Opengl.hpp"

GLFWwindow					*Opengl::_window = NULL;
CREATESHADERPROC            Opengl::glCreateShader = nullptr;            // Creates a new shader object (vertex, fragment, etc.)
SHADERSOURCEPROC            Opengl::glShaderSource = nullptr;            // Sets the source code of a shader
COMPILESHADERPROC           Opengl::glCompileShader = nullptr;           // Compiles a shader object
CREATEPROGRAMPROC           Opengl::glCreateProgram = nullptr;           // Creates a new program object to link multiple shaders
ATTACHSHADERPROC            Opengl::glAttachShader = nullptr;            // Attaches a shader to a program object
LINKPROGRAMPROC             Opengl::glLinkProgram = nullptr;             // Links all attached shaders into a complete GPU program
USEPROGRAMPROC              Opengl::glUseProgram = nullptr;              // Sets the current active shader program
GENVERTEXARRAYSPROC         Opengl::glGenVertexArrays = nullptr;         // Generates one or more Vertex Array Objects (VAOs)
BINDVERTEXARRAYPROC         Opengl::glBindVertexArray = nullptr;         // Binds a VAO to the current OpenGL context
GENBUFFERSPROC              Opengl::glGenBuffers = nullptr;              // Generates one or more buffer object names (VBOs, EBOs, etc.)
BINDBUFFERPROC              Opengl::glBindBuffer = nullptr;              // Binds a buffer object to a specific target (GL_ARRAY_BUFFER, etc.)
BUFFERDATAPROC              Opengl::glBufferData = nullptr;              // Creates and initializes a buffer object's data store
VERTEXATTRIBPOINTERPROC     Opengl::glVertexAttribPointer = nullptr;     // Defines an array of generic vertex attribute data
ENABLEVERTEXATTRIBARRAYPROC Opengl::glEnableVertexAttribArray = nullptr; // Enables a generic vertex attribute array
GETSHADERIVPROC             Opengl::glGetShaderiv = nullptr;             // Retrieves a parameter from a shader object (e.g. compile status)
GETSHADERINFOLOGPROC        Opengl::glGetShaderInfoLog = nullptr;        // Returns the information log for a shader object (e.g. errors)
GETPROGRAMIVPROC            Opengl::glGetProgramiv = nullptr;            // Retrieves a parameter from a program object (e.g. link status)
GETPROGRAMINFOLOGPROC       Opengl::glGetProgramInfoLog = nullptr;       // Returns the information log for a program object (e.g. linking errors)
DELETESHADERPROC            Opengl::glDeleteShader = nullptr;            // Deletes a shader object
GETUNIFORMLOCATIONPROC      Opengl::glGetUniformLocation = nullptr;      // Gets the location of a uniform variable in a shader program
UNIFORMMATRIX4FVPROC        Opengl::glUniformMatrix4fv = nullptr;        // Sets the value of a mat4 uniform variable
UNIFORMLIPROC               Opengl::glUniform1i = nullptr;               // Sets the value of an int uniform variable
UNIFORMLFPROC               Opengl::glUniform1f = nullptr;               // Sets the value of an float uniform variable
GENERATEMIPMAPPROC          Opengl::glGenerateMipmap = nullptr;          // Generates mipmaps for the currently bound texture
DELETEBUFFERSPROC           Opengl::glDeleteBuffers = nullptr;           // Deletes one or more buffer objects
DELETEVERTEXARRAYSPROC      Opengl::glDeleteVertexArrays = nullptr;      // Deletes one or more Vertex Array Objects
DELETEPROGRAMPROC           Opengl::glDeleteProgram = nullptr;           // Deletes a program object
BUFFERSUBDATA               Opengl::glBufferSubData = nullptr;           // Replace a buffer by another one
BINDFRAMEBUFFER             Opengl::glBindFramebuffer = nullptr;         // Link a framebuffer
GENFRAMEBUFFERS             Opengl::glGenFramebuffers = nullptr;
FRAMEBUFFERTEXTURE2D        Opengl::glFramebufferTexture2D = nullptr;
GENRENDERBUFFERS            Opengl::glGenRenderbuffers = nullptr;
BINDRENDERBUFFER            Opengl::glBindRenderbuffer = nullptr;
RENDERBUFFERSTORAGE         Opengl::glRenderbufferStorage = nullptr;
FRAMEBUFFERRENDERBUFFER     Opengl::glFramebufferRenderbuffer = nullptr;
CHECKFRAMEBUFFERSTATUS      Opengl::glCheckFramebufferStatus = nullptr;

//constructors/destructors---------------------------------

Opengl::Opengl(void) {}

Opengl::~Opengl(void) {}

//Member functions-----------------------------------------

GLFWwindow *Opengl::getWindow(void)
{
	return _window;
}

void Opengl::initiateWindow(std::string str)
{
	if(!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW\n" << std::endl;
		getchar();
		throw std::exception();
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(WIDTH, HEIGHT, str.c_str(), NULL, NULL);
	if(_window == NULL)
	{
		std::cerr << "Failed to open GLFW window.\n" << std::endl;
		getchar();
		glfwTerminate();
		throw std::exception();
	}
	glfwMakeContextCurrent(_window);
	if (!loadGLFunctions())
	{
		getchar();
		glfwTerminate();
		throw std::exception();
	}
}

int Opengl::loadGLFunctions()
{
    glCreateShader = (CREATESHADERPROC)glfwGetProcAddress("glCreateShader");
    glShaderSource = (SHADERSOURCEPROC)glfwGetProcAddress("glShaderSource");
    glCompileShader = (COMPILESHADERPROC)glfwGetProcAddress("glCompileShader");
    glCreateProgram = (CREATEPROGRAMPROC)glfwGetProcAddress("glCreateProgram");
    glAttachShader = (ATTACHSHADERPROC)glfwGetProcAddress("glAttachShader");
    glLinkProgram = (LINKPROGRAMPROC)glfwGetProcAddress("glLinkProgram");
    glUseProgram = (USEPROGRAMPROC)glfwGetProcAddress("glUseProgram");
    glGenVertexArrays = (GENVERTEXARRAYSPROC)glfwGetProcAddress("glGenVertexArrays");
    glBindVertexArray = (BINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
    glGenBuffers = (GENBUFFERSPROC)glfwGetProcAddress("glGenBuffers");
    glBindBuffer = (BINDBUFFERPROC)glfwGetProcAddress("glBindBuffer");
    glBufferData = (BUFFERDATAPROC)glfwGetProcAddress("glBufferData");
    glVertexAttribPointer = (VERTEXATTRIBPOINTERPROC)glfwGetProcAddress("glVertexAttribPointer");
    glEnableVertexAttribArray = (ENABLEVERTEXATTRIBARRAYPROC)glfwGetProcAddress("glEnableVertexAttribArray");
    glGetShaderiv = (GETSHADERIVPROC)glfwGetProcAddress("glGetShaderiv");
    glGetShaderInfoLog = (GETSHADERINFOLOGPROC)glfwGetProcAddress("glGetShaderInfoLog");
    glGetProgramiv = (GETPROGRAMIVPROC)glfwGetProcAddress("glGetProgramiv");
    glGetProgramInfoLog = (GETPROGRAMINFOLOGPROC)glfwGetProcAddress("glGetProgramInfoLog");
    glDeleteShader = (DELETESHADERPROC)glfwGetProcAddress("glDeleteShader");
    glGetUniformLocation = (GETUNIFORMLOCATIONPROC)glfwGetProcAddress("glGetUniformLocation");
    glUniformMatrix4fv = (UNIFORMMATRIX4FVPROC)glfwGetProcAddress("glUniformMatrix4fv");
    glUniform1i = (UNIFORMLIPROC)glfwGetProcAddress("glUniform1i");
    glUniform1f = (UNIFORMLFPROC)glfwGetProcAddress("glUniform1f");
    glGenerateMipmap = (GENERATEMIPMAPPROC)glfwGetProcAddress("glGenerateMipmap");
    glDeleteBuffers = (DELETEBUFFERSPROC)glfwGetProcAddress("glDeleteBuffers");
    glDeleteVertexArrays = (DELETEVERTEXARRAYSPROC)glfwGetProcAddress("glDeleteVertexArrays");
    glDeleteProgram = (DELETEPROGRAMPROC)glfwGetProcAddress("glDeleteProgram");
    glBufferSubData = (BUFFERSUBDATA)glfwGetProcAddress("glBufferSubData");
    glBindFramebuffer = (BINDFRAMEBUFFER)glfwGetProcAddress("glBindFramebuffer");
    glGenFramebuffers = (GENFRAMEBUFFERS)glfwGetProcAddress("glGenFramebuffers");
    glFramebufferTexture2D = (FRAMEBUFFERTEXTURE2D)glfwGetProcAddress("glFramebufferTexture2D");
    glGenRenderbuffers = (GENRENDERBUFFERS)glfwGetProcAddress("glGenRenderbuffers");
    glBindRenderbuffer = (BINDRENDERBUFFER)glfwGetProcAddress("glBindRenderbuffer");
    glRenderbufferStorage = (RENDERBUFFERSTORAGE)glfwGetProcAddress("glRenderbufferStorage");
    glFramebufferRenderbuffer = (FRAMEBUFFERRENDERBUFFER)glfwGetProcAddress("glFramebufferRenderbuffer");
    glCheckFramebufferStatus = (CHECKFRAMEBUFFERSTATUS)glfwGetProcAddress("glCheckFramebufferStatus");
    if (!glCreateShader || !glShaderSource || !glCompileShader)
	{
        std::cerr << "Erreur: certaines fonctions OpenGL modernes ne sont pas dispo.\n";
        return 0;
    }
    return 1;
}