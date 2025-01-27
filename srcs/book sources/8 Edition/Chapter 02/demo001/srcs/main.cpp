#include <GL/glew.h>
#include <gl/freeglut.h>
#include <tools/io.h>
#include <tools/path.h>
#include "../auto_generate_files/macro/cmake_to_c_cpp_header_env.h"
DEF_CURRENT_RELATIVELY_PATH_STATIC_VALUE( __FILE__ );
DEF_CURRENT_PROJECT_NAME( );
#define BUFFER_OFFSET(x)  ((const void*) (x))
#include <iostream>

#include "stdio.h"
#include "LoadShaders.h"
#include "vmath.h"

#include <stddef.h>

GLuint Program;
GLuint vao;
GLuint ubo;

void init( ) {

	auto vfile = project_name + "/resources/UniformBlock.vert";
	auto ffile = project_name + "/resources/UniformBlock.frag";
	ShaderInfo shaders[ ] = {
			{GL_VERTEX_SHADER, vfile.c_str( )},
			{GL_FRAGMENT_SHADER, ffile.c_str( )},
			{GL_NONE, NULL}
		};
	Program = LoadShaders( shaders );

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
	GLuint b, n[ 3 ] {0, 1, 2};
	glGenBuffers( 1, &b );
	glBindBuffer( GL_ARRAY_BUFFER, b );
	glBufferData( GL_ARRAY_BUFFER, sizeof( n ), n, GL_STATIC_DRAW );

	GLint in = glGetAttribLocation( Program, "n" );
	glEnableVertexAttribArray( in );
	glVertexAttribIPointer( in, 1, GL_UNSIGNED_INT, 0, BUFFER_OFFSET( 0 ) );

	GLint uboSize = 0;
	ubo = glGetUniformBlockIndex( Program, "Vertice" );
	glGetActiveUniformBlockiv( Program, ubo, GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize );

	std::string msg;
	msg.append( "Bolck Index: " ).append( std::to_string( ubo ) ).append( "\n" ).append( "Bolck Size: " ).append( std::to_string( uboSize ) ).append( "\n" );
	Printer_Normal_Info( msg );

	const GLuint binding = 3;
	//glUniformBlockBinding(Program, ubo, binding);

	struct sDtata {
		GLfloat v[ 3 ][ 4 ];
		GLfloat color[ 4 ];
	} Data = { //uniform 数据
				{{-0.9f, -0.9f, 0.0f, 1.0f}, {0.9f, -0.9f, 0.0f, 1.0f}, {0.0f, 0.9f, 0.0f, 1.0f}},
				{0.2f, 0.7f, 1.0f, 1.0f}
			};

	//验证结构体sDtata，与uniform块格式是否一致。
	const char *names[ ] = {"v", "color"};
	//char *names[] = { "Named.v", "Named.color" };
	GLuint Index[ 2 ];
	GLint offset[ 2 ];
	glGetUniformIndices( Program, 2, names, Index ); // 获取多个名称下标
	glGetActiveUniformsiv( Program, 2, Index, GL_UNIFORM_OFFSET, offset ); // 获取用户变量
	if( uboSize != sizeof( Data ) || offsetof( sDtata, v ) != offset[ 0 ] || offsetof( sDtata, color ) != offset[ 1 ] ) { //offsetof可以返回结构中字段的字节偏移
		Printer_Error_Info( "Data Do not mutch.." );
	}

	glGenBuffers( 1, &b );
	glBindBuffer( GL_UNIFORM_BUFFER, b );
	glBufferData( GL_UNIFORM_BUFFER, sizeof( Data ), &Data, GL_STATIC_DRAW );
	glBindBufferBase( GL_UNIFORM_BUFFER, binding, b );

	glUseProgram( Program );
	glClearColor( 0.5f, 0.0f, 0.2f, 1.0f );
}

void display( void ) {
	glClear( GL_COLOR_BUFFER_BIT );
	glBindVertexArray( vao );
	glDrawArrays( GL_TRIANGLES, 0, 3 );

	glFlush( );
	Sleep( 30 );
}

int main( int argc, char **argv ) {
	glutInit( &argc, argv ); // 初始化
	glutInitDisplayMode( GLUT_RGBA ); // 显示模式
	glutInitWindowSize( 512, 512 ); // 窗口大小
	glutInitContextVersion( 4, 3 ); // opengl 版本
	glutInitContextProfile( GLUT_CORE_PROFILE ); // opengl 核心模式
	glutCreateWindow( project_name.c_str( ) ); // 创建窗口
	if( glewInit( ) ) { // glew 初始化
		Printer_Error_Info( "Unable to initialize GLEW.. " );
		return 1;
	}
	init( );
	glutDisplayFunc( display ); // 刷新调用函数
	glutMainLoop( ); // 事件循环
}
