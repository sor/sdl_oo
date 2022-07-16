#pragma once
#ifndef _GLEW_HPP
#define _GLEW_HPP

#include "SDL_stdinc.hpp"

#include <fstream>
#include <string>
//#include <memory>

namespace GL
{
	#define GLEW_STATIC
	#include <GL/glew.h>

	// uses current GL_ARRAY_BUFFER
	/*
	inline
	static
	void
	VertexAttribPointer(
		GLuint			index,
		GLint			size,
		GLenum			type		= GL_FLOAT,
		GLboolean		normalized	= GL_FALSE,
		GLsizei			stride		= 0,
		const GLvoid *	pointer		= nullptr )
	{
		glVertexAttribPointer( index, size, type, normalized, stride, pointer );
	}*/
	/*
	inline
	static
	void
	EnableVertexAttribArray( GLuint index )
	{
		glEnableVertexAttribArray( index );
	}*/

	class Shader
	{
		GLuint _id;

	public:
		inline
		operator GLuint() const noexcept
		{
			return _id;
		}

		inline
		Shader()
		{
			_id = 0;
		}

		inline
		~Shader()
		{
			glDeleteShader( _id ); // A value of 0 for shader will be silently ignored.
		}

		inline
		Shader &
		Create( const GLenum shaderType )
		{
			if( _id == 0 )
				_id = glCreateShader( shaderType );

			return *this;
		}
		inline
		Shader &
		SourceFile( const char * filename )
		{
			std::ifstream ifs( filename, std::ifstream::in );
			std::string shader_src;
			std::getline( ifs, shader_src, '\0' );	// HACK: might not be 100% correct

			const char * vss = shader_src.c_str();
			glShaderSource( _id, 1, &vss, nullptr );

			return *this;
		}

		inline
		Shader &
		Compile()
		{
			glCompileShader( _id );
			
			GLint status = GetIV( GL_COMPILE_STATUS );
			if( status == GL_FALSE )
				throw GetInfoLog();

			return *this;
		}

		inline
		GLint
		GetIV( GLenum pname )
		{
			GLint status;
			glGetShaderiv( _id, pname, &status );
			return status;
		}

		std::string
		GetInfoLog()
		{
			const GLint log_length = GetIV( GL_INFO_LOG_LENGTH );
			std::string ret;
			ret.resize( log_length + 1 );
			GL::glGetShaderInfoLog( _id, log_length, nullptr, &ret[0] );
			return ret;
		}
	};

	class Attrib
	{
		GLint _id;

	public:
		inline
		operator GLint() const noexcept
		{
			return _id;
		}

		inline
		Attrib()
		{
			_id = 0;
		}

		inline
		Attrib( GLint id )
		{
			_id = id;
		}
		
		inline
		Attrib &
		Enable()
		{
			glEnableVertexAttribArray( _id );
			return *this;
		}

		inline
		Attrib &
		Disable()
		{
			glDisableVertexAttribArray( _id );
			return *this;
		}
		
		// type in GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_FIXED, or GL_FLOAT 
		inline
		Attrib &
		Pointer(
			GLint			size,
			GLenum			type		= GL_FLOAT,
			GLboolean		normalized	= GL_FALSE,
			GLsizei			stride		= 0,
			const GLvoid *	pointer		= nullptr )
		{
			glVertexAttribPointer( _id, size, type, normalized, stride, pointer );
			return *this;
		}

		inline
		Attrib &
		Pointer(
			GLint		size,
			GLenum		type,
			GLboolean	normalized,
			GLsizei		stride,
			GLuint		offset )
		{
			glVertexAttribPointer( _id, size, type, normalized, stride, reinterpret_cast<GL::GLvoid*>(offset) ); // TODO: problems on 64 bit machine?
			return *this;
		}
	};

	class Program
	{
		// +++ STATIC +++
	public:
		inline
		static
		void
		UnUse()
		{
			glUseProgram( 0 );
		}
		// --- STATIC ---

	private:
		GLuint _id;

	public:
		inline
		operator GLuint() const noexcept
		{
			return _id;
		}

		inline
		Program()
		{
			_id = 0;
		}

		inline
		~Program()
		{
			if( _id )
				glDeleteProgram( _id ); // A value of 0 for program will be silently ignored. IF OpenGL is initialized... maybe it isnt? failed without the guard!
		}

		inline
		Program &
		Create()
		{
			if( _id == 0 )
				_id = glCreateProgram();

			return *this;
		}

		inline
		Program &
		AttachShader( const Shader & shader )
		{
			glAttachShader( _id, shader );
			return *this;
		}

		inline
		Program &
		DetachShader( const Shader & shader )
		{
			glDetachShader( _id, shader );
			return *this;
		}

		inline
		Program &
		BindFragDataLocation( GLuint colorNumber, const char * name )
		{
			glBindFragDataLocation( _id, colorNumber, name );
			return *this;
		}

		inline
		Program &
		Link()
		{
			glLinkProgram( _id );

			GLint status = GetIV( GL_LINK_STATUS );

			if( status == GL_FALSE )
			{
				throw GetInfoLog();
			}

			return *this;
		}
		
		inline
		Program &
		Use()
		{
			glUseProgram( _id );
			return *this;
		}
		
		inline
		Attrib
		GetAttrib( const GLchar *name )
		{
			return Attrib( glGetAttribLocation( _id, name ) );
		}

		inline
		GLint
		GetIV( GLenum pname )
		{
			GLint status;
			glGetProgramiv( _id, pname, &status );
			return status;
		}

		std::string
		GetInfoLog()
		{
			const GLint log_length = GetIV( GL_INFO_LOG_LENGTH );
			std::string ret;
			ret.resize( log_length + 1 );
			GL::glGetProgramInfoLog( _id, log_length, nullptr, &ret[0] );
			return ret;
		}
	};

	class VertexArray
	{
		GLuint _id;

	public:
		inline
		static
		void
		UnBind()
		{
			glBindVertexArray( 0 );
		}

		inline
		VertexArray()
		{
			_id = 0;
		}

		inline
		VertexArray &
		Gen()
		{
			if( _id == 0 )
				glGenVertexArrays( 1, &_id );

			return *this;
		}

		inline
		operator GLuint() const noexcept
		{
			return _id;
		}

		inline
		VertexArray &
		Bind()
		{
			glBindVertexArray( _id );
			return *this;
		}
	};

	enum class BufferTarget : GLenum
	{
		ARRAY			= GL_ARRAY_BUFFER,
		ELEMENT_ARRAY	= GL_ELEMENT_ARRAY_BUFFER
	};

	template <BufferTarget Target>
	class Buffer
	{
		/*
		GL_BUFFER_SIZE			integer	0				jede positive Zahl
		GL_BUFFER_USAGE			enum	GL_STATIC_DRAW	GL_STREAM_DRAW,  GL_STREAM_READ,  GL_STREAM_COPY,
														GL_STATIC_DRAW,  GL_STATIC_READ,  GL_STATIC_COPY,
														GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, GL_DYNAMIC_COPY
		GL_BUFFER_ACCESS		enum	GL_READ_WRITE	GL_READ_ONLY, GL_WRITE_ONLY, GL_READ_WRITE
		GL_BUFFER_MAPPED		boolean	FALSE			TRUE, FALSE
		GL_BUFFER_MAP_POINTER	void*	nullptr			address
		*/

		// +++ STATIC +++
	public:
		inline
		static
		void
		UnBind()
		{
			glBindBuffer( static_cast<GLenum>( Target ), 0 );
		}
		// --- STATIC ---

	private:
		GLuint _id;

	public:
		inline
		operator GLuint() const noexcept
		{
			return _id;
		}

		inline
		Buffer()
		{
			_id = 0;
		}

		inline
		Buffer &
		Gen()
		{
			if( _id == 0 )
				glGenBuffers( 1, &_id );

			return *this;
		}

		inline
		Buffer &
		Bind()
		{
			glBindBuffer( static_cast<GLenum>( Target ), _id );
			return *this;
		}
		
		inline
		Buffer &
		Alloc( GLsizeiptr size, GLenum usage )
		{
			glBufferData( static_cast<GLenum>( Target ), size, nullptr, usage );
			return *this;
		}

		inline
		Buffer &
		Data( GLsizeiptr size, const GLvoid* data, GLenum usage )
		{
			glBufferData( static_cast<GLenum>( Target ), size, data, usage );
			return *this;
		}

		inline
		Buffer &
		SubData( GLintptr offset, GLsizeiptr size, const GLvoid* data )
		{
			glBufferSubData( static_cast<GLenum>( Target ), offset, size, data );
			return *this;
		}
	};

	using ArrayBuffer = Buffer<BufferTarget::ARRAY>;
	using IndexBuffer = Buffer<BufferTarget::ELEMENT_ARRAY>;
}

namespace GLEW
{
	inline
	static void Init( const bool experimental = false )
	{
		GL::glewExperimental = experimental;
		GL::glewInit();
	}
}

#endif
