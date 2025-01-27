#ifndef MATHEMATICS_H_H_HEAD__FILE__
#define MATHEMATICS_H_H_HEAD__FILE__
#pragma once
#include "mathNameSpaces.h"
#include <glm/glm.hpp>
class TOOLS_EXPORT cyl::math::Mathematics {

public:
	/// @brief 返回一个平移矩阵
	/// @param x 平移 x
	/// @param y 平移 y
	/// @param z 平移 z
	/// @return 平移矩阵
	static glm::mat4 buildTranslate( float x, float y, float z ) {
		return glm::mat4(
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			x, y, z, 1.0 );
	}
	/// @brief 构建 x 轴旋转矩阵
	/// @param rad 旋转弧度
	/// @return x 轴旋转 rad 弧度的矩阵
	static glm::mat4 buildRotateX( float rad ) {
		return glm::mat4(
			1.0, 0.0, 0.0, 0.0,
			0.0, cos( rad ), sin( rad ), 0.0,
			0.0, -sin( rad ), cos( rad ), 0.0,
			0.0, 0.0, 0.0, 1.0 );
	}

	/// @brief 构建 y 轴旋转矩阵
	/// @param rad 旋转弧度
	/// @return y 轴旋转 rad 弧度的矩阵
	static glm::mat4 buildRotateY( float rad ) {
		return glm::mat4(
			cos( rad ), 0.0, -sin( rad ), 0.0,
			0.0, 1.0, 0.0, 0.0,
			sin( rad ), 0.0, cos( rad ), 0.0,
			0.0, 0.0, 0.0, 1.0 );
	}
	/// @brief 构建 z 轴旋转矩阵
	/// @param rad 旋转弧度
	/// @return z 轴旋转 rad 弧度的矩阵
	static glm::mat4 buildRotateZ( float rad ) {
		return glm::mat4(
			cos( rad ), sin( rad ), 0.0, 0.0,
			-sin( rad ), cos( rad ), 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0 );
	}
	/// @brief 构建缩放矩阵
	/// @param x x 缩放
	/// @param y y 缩放
	/// @param z z 缩放
	/// @return 缩放矩阵
	static glm::mat4 buildScale( float x, float y, float z ) {
		return glm::mat4(
			x, 0.0, 0.0, 0.0,
			0.0, y, 0.0, 0.0,
			0.0, 0.0, z, 0.0,
			0.0, 0.0, 0.0, 1.0 );
	}
	static float FLOAT_PRECISION_EPSILON( ) {
		return 1.0e-6f;
	}

	static bool FuzzyIsZero( float f ) {
		return std::abs( f ) < FLOAT_PRECISION_EPSILON( );
	}

	/**
	* @brief 一维线性映射函数，将[a,b]中的点x，映射到[a1,b1]中的点x1
	*
	**/
	static float LinearMap( float x, float a, float b, float a1, float b1 );
	/**
	* @brief  					窗口坐标转化为世界坐标
	* @brief screenPoint		窗口坐标点
	* @brief viewportRange 	视口范围。 各个值依次为：左上-右下
	* @brief modelViewMatrix 	模型视图矩阵
	* @brief projectMatrix 	投影矩阵
	* @brief pPointDepth   	屏幕点的深度，如果不指定(为nullptr),从深度缓冲区中读取深度值
	* @return 					世界坐标系
	* @note 注意：得到的世界坐标系在使用前要除以齐次坐标值w，
	*		 如果w是0，则不应使用此点。
	* @code
	*  // sample
	*  ...
	*  auto&& worldPoint = Screen2World(...);
	*  if( !FuzzyIsZero( worldPoint.w ) )
	*  {
	*	 	glm::vec3 world3D(worldPoint);
	*      world3D /= worldPoint;
	*      /// using world3D
	*	}
	*	else
	*	{
	*		// error handler
	*	}
	*/
	static glm::vec4 Screen2World( const glm::ivec2 &screenPoint, const glm::vec4 &viewportRange, const glm::mat4 &modelMatrix, const glm::mat4 &projectMatrix, const float *pPointDepth = nullptr );
	/**
	* @brief 世界坐标系转换为屏幕坐标系
	* @brief worldPoint		世界坐标的点坐标点
	* @brief viewportRange 	视口范围。 各个值依次为：左上-右下
	* @brief modelViewMatrix 	模型视图矩阵
	* @brief projectMatrix 	投影矩阵
	* @brief pPointDepth   	屏幕点的深度，如果不指定(为nullptr),从深度缓冲区中读取深度值
	* @return 					窗口坐标点 
	* @note 返回的窗口坐标带深度值，如果仅适用2D窗口像素坐标点，仅适用它的x,y维即可
	*/
	static glm::vec3 World2Screen( const glm::vec3 &worldPoint, const glm::vec4 &viewportRange, const glm::mat4 &modelViewMatrix, const glm::mat4 &projectMatrix );

};

#endif // MATHEMATICS_H_H_HEAD__FILE__
