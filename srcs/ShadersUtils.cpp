#include "Shaders.hpp"

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

GLuint createShaderProgram(std::string &vertexSrc, std::string &fragmentSrc)
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

void oneLine(std::string &dest, std::string file)
{
	std::ifstream	stream(file.c_str());
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