#include "Opengl.hpp"

GLFWwindow					*Opengl::_window = NULL;
GLuint						Opengl::_shaderProgram = 0;
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
GENERATEMIPMAPPROC          Opengl::glGenerateMipmap = nullptr;          // Generates mipmaps for the currently bound texture
DELETEBUFFERSPROC           Opengl::glDeleteBuffers = nullptr;           // Deletes one or more buffer objects
DELETEVERTEXARRAYSPROC      Opengl::glDeleteVertexArrays = nullptr;      // Deletes one or more Vertex Array Objects
DELETEPROGRAMPROC           Opengl::glDeleteProgram = nullptr;           // Deletes a program object

//constructors/destructors---------------------------------

Opengl::Opengl(void) {}

Opengl::~Opengl(void) {}

//Member functions-----------------------------------------

GLFWwindow *Opengl::getWindow(void)
{
	return _window;
}

GLuint Opengl::getShaderProgram(void)
{
	return _shaderProgram;
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

static GLuint compileShader(std::string &source, GLenum type)
{
    GLuint shader = Opengl::glCreateShader(type);
	const char *source2 = source.c_str();
    Opengl::glShaderSource(shader, 1, &source2, NULL);
    Opengl::glCompileShader(shader);

    int success;
    char infoLog[512];
    Opengl::glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        Opengl::glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return shader;
}

static GLuint createShaderProgram(std::string &vertexSrc, std::string &fragmentSrc)
{
    GLuint vertex = compileShader(vertexSrc, GL_VERTEX_SHADER);
    GLuint fragment = compileShader(fragmentSrc, GL_FRAGMENT_SHADER);

    GLuint program = Opengl::glCreateProgram();
    Opengl::glAttachShader(program, vertex);
    Opengl::glAttachShader(program, fragment);
    Opengl::glLinkProgram(program);

    int success;
    char infoLog[512];
    Opengl::glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
        Opengl::glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    Opengl::glDeleteShader(vertex);
    Opengl::glDeleteShader(fragment);
    return program;
}

static void oneLine(std::string &dest, std::string file)
{
	std::ifstream stream(file.c_str());
	std::string		buffer;

	if (!stream.is_open())
		throw std::runtime_error("\033[31mfile couldn't be oppened\033[0m");

	while (std::getline(stream, buffer))
	{
		buffer += '\n';
		dest.append(buffer);
	}
	stream.close();
}

void Opengl::initiateShaders()
{
	std::string vertexSrc;
	std::string fragmentSrc;
	oneLine(vertexSrc, "shaders/vertexShader.glsl");
	if (vertexSrc.empty())
		throw std::runtime_error("\033[31mvertexSrc is empty\033[0m");
	oneLine(fragmentSrc, "shaders/fragmentShader.glsl");
	if (fragmentSrc.empty())
		throw std::runtime_error("\033[31mfragmentSrc is empty\033[0m");
	_shaderProgram = createShaderProgram(vertexSrc, fragmentSrc);
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
    glGenerateMipmap = (GENERATEMIPMAPPROC)glfwGetProcAddress("glGenerateMipmap");
    glDeleteBuffers = (DELETEBUFFERSPROC)glfwGetProcAddress("glDeleteBuffers");
    glDeleteVertexArrays = (DELETEVERTEXARRAYSPROC)glfwGetProcAddress("glDeleteVertexArrays");
    glDeleteProgram = (DELETEPROGRAMPROC)glfwGetProcAddress("glDeleteProgram");
    if (!glCreateShader || !glShaderSource || !glCompileShader)
	{
        std::cerr << "Erreur: certaines fonctions OpenGL modernes ne sont pas dispo.\n";
        return 0;
    }
    return 1;
}