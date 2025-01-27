#ifndef ENUM_H_H_HEAD__FILE__
#define ENUM_H_H_HEAD__FILE__
#pragma once
#include "../../auto_generate_files/export/Tools_export.h"

namespace cyl {
	namespace mathNameSpaces {
		/// @brief 类型
		enum class VEC_TYPE {
			NONE,
			UINT8,
			INT8,
			UINT16,
			INT16,
			UINT32,
			INT32,
			UINT64,
			INT64,
			FLOAT,
			DOUBLE,
		};

		/**
		 * @brief 获取类型的大小
		 * @param vec_type 类型
		 * @return 类型大小
		 */
		TOOLS_EXPORT size_t getVecTypeSize( VEC_TYPE vec_type );
	}
}

#endif // ENUM_H_H_HEAD__FILE__
