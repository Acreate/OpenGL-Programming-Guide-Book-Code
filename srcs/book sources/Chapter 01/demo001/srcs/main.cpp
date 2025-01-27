#include <GL/glew.h>
#include <gl/freeglut.h>
#include <tools/io.h>
#include <tools/path.h>
#include "../auto_generate_files/macro/cmake_to_c_cpp_header_env.h"
DEF_CURRENT_RELATIVELY_PATH_STATIC_VALUE( __FILE__ );
DEF_CURRENT_PROJECT_NAME( );
#define BUFFER_OFFSET(x)  ((const void*) (x))
#include <iostream>
using namespace std;

#include "stdio.h"
#include "LoadShaders.h"
#include "vmath.h"

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[ NumVAOs ];
GLuint Buffers[ NumBuffers ];

const GLuint NumVertices = 6;

GLuint program;

void init( ) {
	/// 生成 vao 索引
	glGenVertexArrays( NumVAOs, VAOs );
	/// 在索引下生成内容
	glBindVertexArray( VAOs[ Triangles ] );

	GLfloat vertices[ NumVertices ][ 2 ] = {
			{-0.9f, -0.9f}, {0.85f, -0.90f}, {-0.90f, 0.85f},
			{0.90f, -0.85f}, {0.90f, 0.90f}, {-0.85f, 0.90f}
		};
	// 生成 vbo 索引
	glGenBuffers( NumBuffers, Buffers );
	/// 使用索引生成内容
	/// 当索引下不存在内容时，会重新生成一段内容
	/// target 指定生成内容位置
	/// buffer 指定索引
	/// 生成内容为当前配置项
	glBindBuffer( GL_ARRAY_BUFFER, Buffers[ ArrayBuffer ] );
	/// 在内容上放置数据
	/// 在放置数据之前，需要内容生效，即调用 glBindBuffer 配置对应的内容位置
	/// target 指定内容位置
	/// size 指定大小
	/// data 存放的内存数据-用户数据
	/// usage 数据模式
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

	auto vfile = project_name + "/resources/triangles.vert";
	auto ffile = project_name + "/resources/triangles.frag";
	ShaderInfo shaders[ ] = {
			{GL_VERTEX_SHADER, vfile.c_str( )},
			{GL_FRAGMENT_SHADER, ffile.c_str( )},
			{GL_NONE, NULL}
		};

	program = LoadShaders( shaders ); // 加载着色器脚本，并且生成着色器
	glUseProgram( program ); // 引用着色器

	GLuint pos = glGetAttribLocation( program, "vPosition" ); // 获取 layout 数据通道下标
	glVertexAttribPointer( pos, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET( 0 ) ); // 设定 layout 通道数据样式
	glEnableVertexAttribArray( pos ); // 激活 layout 通道

	glClearColor( 0, 0, 0, 0 );
	
	// 删除过后，即时使用 glBindVertexArray 生成数据也会失败
	//	glDeleteVertexArrays( NumVAOs, VAOs ); 
	// 删除过后，即使使用 glBindBuffer 与 glBufferData 配置数据缓存也会失败，并且导致异常
	//	glDeleteBuffers( NumBuffers, Buffers ); 
}

void display( void ) {
	glClear( GL_COLOR_BUFFER_BIT ); // 清理
	glBindVertexArray( VAOs[ Triangles ] ); // 设定vao
	glDrawArrays( GL_TRIANGLES, 0, 6 ); // 调用绘制  

	glFlush( ); // 立即执行
	Sleep( 30 ); //减少CPU的占用
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
