#include <GL/glew.h>
#include "math.h"
#include "../tools/path.h"
#include "../tools/io.h"
#include "../auto_generate_files/macro/cmake_to_c_cpp_header_env.h"

DEF_CURRENT_PROJECT_NAME( );
DEF_CURRENT_RELATIVELY_PATH_STATIC_VALUE( __FILE__ );
float cyl::math::Mathematics::LinearMap( float x, float a, float b, float a1, float b1 ) {
	auto srcDelt( b - a );
	if( FuzzyIsZero( srcDelt ) ) {
		Printer_Error_Info( "值不能为 0" );
		return a1;
	}
	return ( b1 - a1 ) / srcDelt * ( x - a ) + a1;
}
glm::vec4 cyl::math::Mathematics::Screen2World( const glm::ivec2 &screenPoint, const glm::vec4 &viewportRange, const glm::mat4 &modelMatrix, const glm::mat4 &projectMatrix, const float *pPointDepth ) {
	GLfloat pointDepth( 0.0f );
	if( nullptr != pPointDepth )
		pointDepth = *pPointDepth;
	else
		// 获取深度缓冲区中x,y的数值
		glReadPixels( screenPoint.x, screenPoint.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &pointDepth );

#if defined(USING_GLM_ALGORITHM)
	/// 直接使用glm的"逆投影"
	return glm::vec4( glm::unProject(glm::vec3(screenPoint,pointDepth),modelMatrix,projectMatrix,viewportRange);
#else
	float linearMap = LinearMap( screenPoint.x, viewportRange.x, viewportRange.z, -1.0f, 1.0f );
	float map = LinearMap( screenPoint.y, viewportRange.y, viewportRange.w, 1.0f, -1.0f );
	// 转换为标准设备坐标系
	glm::vec4 devicePoint( linearMap, map, pointDepth, 1 );

	// 按照opengl管线工作方式，转换到世界坐标系
	auto inverse = glm::inverse( projectMatrix * modelMatrix );
	return inverse * devicePoint;
#endif

}
glm::vec3 cyl::math::Mathematics::World2Screen( const glm::vec3 &worldPoint, const glm::vec4 &viewportRange, const glm::mat4 &modelViewMatrix, const glm::mat4 &projectMatrix ) {
#if defined(USING_GLM_ALGORITHM)
	/// 直接使用glm的"投影"
	return glm::project( worldPoint, modelViewMatrix, projectMatrix, viewportRange );
#else
	/// 将世界坐标转换为设备坐标
	const auto &resultPoint = projectMatrix * modelViewMatrix * glm::vec4( worldPoint, 1.0f );
	if( FuzzyIsZero( resultPoint.w ) ) {
		Printer_Error_Info( "值不能为 0" );
		/// 其他错误处理
		return glm::vec3( );
	}
	glm::vec3 returnPoint( resultPoint );
	returnPoint /= resultPoint.w;
	returnPoint.x = LinearMap( returnPoint.x, -1.0f, 1.0f, viewportRange.x, viewportRange.z );
	returnPoint.y = LinearMap( returnPoint.y, 1.0f, -1.0f, viewportRange.y, viewportRange.w );
	return returnPoint;
#endif

}
