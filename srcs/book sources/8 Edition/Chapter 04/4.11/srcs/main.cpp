﻿#include <GL/glew.h>
#include <gl/freeglut.h>
#include <tools/io.h>
#include <tools/path.h>
#include "../auto_generate_files/macro/cmake_to_c_cpp_header_env.h"
#include <opencv2/opencv.hpp>
DEF_CURRENT_RELATIVELY_PATH_STATIC_VALUE( __FILE__ );
DEF_CURRENT_PROJECT_NAME( );
#define BUFFER_OFFSET(x)  ((const void*) (x))
#include <iostream>

#include "vgl.h"
#include "LoadShaders.h"
#include "vmath.h"

using namespace std;

struct Vertex {
	GLubyte color[ 4 ];
	GLfloat position[ 3 ];
};

Vertex Verts[ 9 ] = {
		{{255, 0, 0, 255}, {0.0f, 0.9f, 0.0f}},
		{{0, 255, 0, 255}, {-0.9f, -0.9f, 0.0f}},
		{{0, 0, 255, 255}, {0.9f, -0.9f, 0.0f}},

		{{255, 255, 255, 255}, {0.0f, 0.8f, -0.2f}},
		{{255, 255, 255, 255}, {-0.4f, 0.0f, -0.2f}},
		{{255, 255, 255, 255}, {0.4f, 0.0f, -0.2f}},

		{{255, 255, 255, 255}, {0.0f, 1.0f, 0.2f}},
		{{255, 255, 255, 255}, {-0.4f, 0.2f, 0.2f}},
		{{255, 255, 255, 255}, {0.4f, 0.2f, 0.2f}}
	};

GLuint Program = 0;

GLuint vert;
GLuint vbo;

GLuint RendBuf[ 3 ], FrameBuf;

void Init( ) {
	auto vShader = project_name + "/resources/Chpater04.vert";
	auto fShader = project_name + "/resources/Chapter04.frag";
	ShaderInfo si[ ] = {{GL_VERTEX_SHADER, vShader.c_str( )}, {GL_FRAGMENT_SHADER, fShader.c_str( )}, {GL_NONE, NULL}};
	Program = LoadShaders( si );

	glGenVertexArrays( 1, &vert );
	glBindVertexArray( vert );

	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof( Verts ), Verts, GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof( Vertex ), BUFFER_OFFSET( 0 ) );
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), BUFFER_OFFSET( sizeof(Verts->color) ) );
	glEnableVertexAttribArray( 1 );

	glClearColor( 0.2f, 0.1f, 0.3f, 1.0f );
	glUseProgram( Program );

	glGenRenderbuffers( 3, RendBuf ); //两个颜色附件，一个深度缓存
	glBindRenderbuffer( GL_RENDERBUFFER, RendBuf[ 0 ] );
	glRenderbufferStorage( GL_RENDERBUFFER, GL_RGBA, 200, 200 );

	glBindRenderbuffer( GL_RENDERBUFFER, RendBuf[ 1 ] );
	glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 200, 200 );

	glBindRenderbuffer( GL_RENDERBUFFER, RendBuf[ 2 ] );
	glRenderbufferStorage( GL_RENDERBUFFER, GL_RGBA, 200, 200 );

	glGenFramebuffers( 1, &FrameBuf );
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, FrameBuf );
	glFramebufferRenderbuffer( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, RendBuf[ 0 ] );
	glFramebufferRenderbuffer( GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RendBuf[ 1 ] );
	glFramebufferRenderbuffer( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_RENDERBUFFER, RendBuf[ 2 ] );
}

void Display( ) {
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, FrameBuf ); //绘制到帧缓存
	glViewport( 0, 0, 200, 200 ); //设置视口大小与帧缓存一致

	GLenum bufs[ 2 ] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1}; //设置同时绘制到两个颜色附件
	glDrawBuffers( 2, bufs );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	float Color[ ] = {0.0f, 0.0f, 0.0f, 0.0f};
	glClearBufferfv( GL_COLOR, 0, Color ); //第二个参数0，是指GL_COLOR_ATTACHMENT0颜色附件，其背景清除为红色

	glBindVertexArray( vert );

	glEnable( GL_DEPTH_TEST );
	glDrawArrays( GL_TRIANGLES, 0, 6 ); //向帧缓存中绘制

	glBindFramebuffer( GL_READ_FRAMEBUFFER, FrameBuf ); //将帧缓存设置为读取缓存
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 ); //将绘制缓存设为窗口的帧缓存
	glViewport( 0, 0, 400, 400 );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//拷贝缓存
	glReadBuffer( GL_COLOR_ATTACHMENT0 ); //设置从GL_COLOR_ATTACHMENT0读取缓存
	glBlitFramebuffer( 0, 0, 200, 200, 0, 0, 200, 200, GL_COLOR_BUFFER_BIT, GL_NEAREST );

	glReadBuffer( GL_COLOR_ATTACHMENT1 ); //设置从GL_COLOR_ATTACHMENT1读取缓存
	glBlitFramebuffer( 0, 0, 200, 200, 200, 0, 400, 200, GL_COLOR_BUFFER_BIT, GL_NEAREST );

	//在窗口帧缓存直接绘制一个三角形
	glDrawBuffer( GL_BACK );
	glDrawArrays( GL_TRIANGLES, 6, 3 );

	//读取像素测试
	static bool IsReadPixel = true;
	if( IsReadPixel ) {
		IsReadPixel = false;
		GLuint Pixels[ 50 ][ 50 ] {0};
		glReadBuffer( GL_COLOR_ATTACHMENT0 ); //设置缓存读取的附件
		glReadPixels( 150, 0, 50, 50, GL_RGBA, GL_UNSIGNED_BYTE, Pixels ); //读取GL_READ_FRAMEBUFFER像素，这个位置红色比较多 读取出来好多 ff0000ff的值
		int n = glGetError( );
		//GL_INVALID_ENUM;
		for( int i = 0; i < 50; ++i ) {
			for( int j = 0; j < 50; ++j ) {
				GLuint i1 = Pixels[ i ][ j ];
				cout << hex << i1 << "  ";
			}
			cout << endl;
		}
		cv::Mat png( 400, 400, CV_8UC4 );
		for( size_t index = 0; index < 400; ++index )
			for( size_t subIndex = 0; subIndex < 400; ++subIndex ) {
				auto &at = png.at< cv::Vec4b >( index, subIndex );
				at[ 2 ] = 0;
				at[ 1 ] = 0;
				at[ 0 ] = 0;
				at[ 3 ] = 0;
			}
#define  width   200
#define  height   200
		GLuint readPixels[ width ][ height ] {0};
		glReadBuffer( GL_COLOR_ATTACHMENT0 ); //设置缓存读取的附件
		glReadPixels( 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, readPixels );
		for( int i = 0; i < width; ++i ) {
			for( int j = 0; j < height; ++j ) {
				GLuint i1 = readPixels[ i ][ j ];
				uint8_t *p = ( uint8_t * ) &i1;
				auto &at = png.at< cv::Vec4b >( i, j );
				at[ 2 ] = p[ 0 ];
				at[ 1 ] = p[ 1 ];
				at[ 0 ] = p[ 2 ];
				at[ 3 ] = p[ 3 ];
			}
		}

		glReadBuffer( GL_COLOR_ATTACHMENT1 ); //设置缓存读取的附件
		glReadPixels( 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, readPixels );
		for( int i = 0; i < width; ++i ) {
			for( int j = 0; j < height; ++j ) {
				GLuint i1 = readPixels[ i ][ j ];
				uint8_t *p = ( uint8_t * ) &i1;
				auto &at = png.at< cv::Vec4b >( i + width, j + height );
				at[ 2 ] = p[ 0 ];
				at[ 1 ] = p[ 1 ];
				at[ 0 ] = p[ 2 ];
				at[ 3 ] = p[ 3 ];
			}
		}
		cyl::tools::path writePathObj( project_name + "/resources/" );
		writePathObj.createPathDir( );
		cv::imwrite( project_name + "/resources/write.png", png );
	}
	glutSwapBuffers( );
	Sleep( 30 );
}

int main( int argc, char *argv[ ] ) {
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_STENCIL | GLUT_DEPTH );
	glutInitWindowSize( 400, 400 );
	glutInitContextVersion( 4, 3 );
	glutInitContextProfile( GLUT_CORE_PROFILE );
	glutCreateWindow( "Test OpenGL Chapter 04" );

	if( glewInit( ) ) {
		cout << "Unable to Initialize GLEW." << endl;
		return 1;
	}
	Init( );
	glutDisplayFunc( Display );
	glutMainLoop( );

	return 0;
}
