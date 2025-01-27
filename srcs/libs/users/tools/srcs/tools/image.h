#ifndef IMAGE_H_H_HEAD__FILE__
#define IMAGE_H_H_HEAD__FILE__
#pragma once
#include "./toolsNamespace.h"

class TOOLS_EXPORT cyl::tools::Image {
public:
	/// @brief 数据转换到图片 png 格式
	/// @param data_ptr 数据指针
	/// @param data_size 数据大小
	/// @param width 图片宽度
	/// @param height 图片高度
	/// @param result_vector png 的完整数据
	/// @return 处理数据大小
	static size_t converColorDataToPng( const uint8_t *data_ptr, size_t data_size, uint32_t width, uint32_t height, std::vector< uint8_t > *result_vector );
};

#endif // IMAGE_H_H_HEAD__FILE__
