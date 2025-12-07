#ifndef OPENGL_HPP

# define OPENGL_HPP

# include <GLFW/glfw3.h>
# include <iostream>
# include <string>
# include <exception>
# include <fstream>
# include <vector>
# include "Vec2.hpp"
# include "Vec3.hpp"

# define WIDTH 1920
# define HEIGHT 1080

typedef GLuint	(*CREATESHADERPROC)(GLenum type);
typedef void	(*SHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar **string, const GLint *length);
typedef void	(*COMPILESHADERPROC)(GLuint shader);
typedef GLuint	(*CREATEPROGRAMPROC)(void);
typedef void	(*ATTACHSHADERPROC)(GLuint program, GLuint shader);
typedef void	(*LINKPROGRAMPROC)(GLuint program);
typedef void	(*USEPROGRAMPROC)(GLuint program);
typedef void	(*GENVERTEXARRAYSPROC)(GLsizei n, GLuint *arrays);
typedef void	(*BINDVERTEXARRAYPROC)(GLuint array);
typedef void	(*GENBUFFERSPROC)(GLsizei n, GLuint *buffers);
typedef void	(*BINDBUFFERPROC)(GLenum target, GLuint buffer);
typedef void	(*BUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
typedef void	(*VERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
typedef void	(*ENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef void	(*GETSHADERIVPROC)(GLuint shader,  GLenum pname, GLint *params);
typedef void	(*GETSHADERINFOLOGPROC)(GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog);
typedef void	(*GETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint *params);
typedef void	(*GETPROGRAMINFOLOGPROC)(GLuint program, GLsizei maxLength, GLsizei *length, GLchar *infoLog);
typedef void	(*DELETESHADERPROC)(GLuint shader);
typedef GLint	(*GETUNIFORMLOCATIONPROC)(GLuint program, const GLchar *name);
typedef void	(*UNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void	(*UNIFORMLIPROC)(GLint location, GLint v0);
typedef void	(*UNIFORMLFPROC)(GLint location, GLfloat v0);
typedef void	(*GENERATEMIPMAPPROC)(GLenum target);
typedef void	(*DELETEBUFFERSPROC)(GLsizei n, const GLuint *buffers);
typedef void	(*DELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint *arrays);
typedef void	(*DELETEPROGRAMPROC)(GLuint program);
typedef void	(*BUFFERSUBDATA)(GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
typedef void	(*BINDFRAMEBUFFER)(GLenum target, GLuint framebuffer);
typedef void	(*GENFRAMEBUFFERS)(GLsizei n, GLuint *ids);
typedef void	(*FRAMEBUFFERTEXTURE2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void	(*GENRENDERBUFFERS)(GLsizei n, GLuint *renderbuffers);
typedef void	(*BINDRENDERBUFFER)(GLenum target, GLuint renderbuffer);
typedef void	(*RENDERBUFFERSTORAGE)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void	(*FRAMEBUFFERRENDERBUFFER)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef	GLenum	(*CHECKFRAMEBUFFERSTATUS)(GLenum target);
typedef void	(*DELETERENDERBUFFERS)(GLsizei n, const GLuint *renderbuffers);
typedef void	(*DELETETEXTURES)(GLsizei n, const GLuint *textures);
typedef void	(*DELETEFRAMEBUFFERS)(GLsizei n, const GLuint *framebuffers);

# define GREEN "\033[32m"
# define RESET "\033[0m"
# define YELLOW "\033[33m"
# define RED "\033[31m"
# define BLUE "\033[34m"
# define GRAY "\033[90m"
# define PINK "\033[35m"


class Opengl
{
	private:
		Opengl(void);
		~Opengl(void);
		static int	loadGLFunctions(void);

	private:
		static GLFWwindow	*_window;
		static GLFWwindow	*_window2;
		static int			_width;
		static int			_height;


	public:
		static CREATESHADERPROC				glCreateShader;
		static SHADERSOURCEPROC				glShaderSource;
		static COMPILESHADERPROC			glCompileShader;
		static CREATEPROGRAMPROC			glCreateProgram;
		static ATTACHSHADERPROC				glAttachShader;
		static LINKPROGRAMPROC				glLinkProgram;
		static USEPROGRAMPROC				glUseProgram;
		static GENVERTEXARRAYSPROC			glGenVertexArrays;
		static BINDVERTEXARRAYPROC			glBindVertexArray;
		static GENBUFFERSPROC				glGenBuffers;
		static BINDBUFFERPROC				glBindBuffer;
		static BUFFERDATAPROC				glBufferData;
		static VERTEXATTRIBPOINTERPROC		glVertexAttribPointer;
		static ENABLEVERTEXATTRIBARRAYPROC	glEnableVertexAttribArray;
		static GETSHADERIVPROC				glGetShaderiv;
		static GETSHADERINFOLOGPROC			glGetShaderInfoLog;
		static GETPROGRAMIVPROC				glGetProgramiv;
		static GETPROGRAMINFOLOGPROC		glGetProgramInfoLog;
		static DELETESHADERPROC				glDeleteShader;
		static GETUNIFORMLOCATIONPROC		glGetUniformLocation;
		static UNIFORMMATRIX4FVPROC			glUniformMatrix4fv;
		static UNIFORMLIPROC				glUniform1i;
		static UNIFORMLFPROC				glUniform1f;
		static GENERATEMIPMAPPROC			glGenerateMipmap;
		static DELETEBUFFERSPROC			glDeleteBuffers;
		static DELETEVERTEXARRAYSPROC		glDeleteVertexArrays;
		static DELETEPROGRAMPROC			glDeleteProgram;
		static BUFFERSUBDATA				glBufferSubData;
		static BINDFRAMEBUFFER				glBindFramebuffer;
		static GENFRAMEBUFFERS				glGenFramebuffers;
		static FRAMEBUFFERTEXTURE2D			glFramebufferTexture2D;
		static GENRENDERBUFFERS				glGenRenderbuffers;
		static BINDRENDERBUFFER				glBindRenderbuffer;
		static RENDERBUFFERSTORAGE			glRenderbufferStorage;
		static FRAMEBUFFERRENDERBUFFER		glFramebufferRenderbuffer;
		static CHECKFRAMEBUFFERSTATUS		glCheckFramebufferStatus;
		static DELETERENDERBUFFERS			glDeleteRenderbuffers;
		static DELETETEXTURES				glDeleteTextures;
		static DELETEFRAMEBUFFERS			glDeleteFramebuffers;

	public:
		static GLFWwindow	*getWindow(void);
		static GLFWwindow	*getWindow2(void);
		static int			getWidth(void);
		static int			getHeight(void);
		static void			setDim(int width, int height);
		static void			initiateWindow(std::string str);
};

#endif