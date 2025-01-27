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
#include <opencv2/opencv.hpp>
#include <stddef.h>

int main( int argc, char **argv ) {
	auto im = cv::imread( project_name + "/resources/th.jpg" );
	cv::imshow( project_name, im );
	cv::waitKey( 0 );
	cv::destroyAllWindows( );
}
