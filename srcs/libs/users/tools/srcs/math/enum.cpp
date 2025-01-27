#include "enum.h"
#include <cstdint>

size_t cyl::mathNameSpaces::getVecTypeSize( VEC_TYPE vec_type ) {
	switch( vec_type ) {
		case VEC_TYPE::UINT8 :
		case VEC_TYPE::INT8 :
			return sizeof( uint8_t );
		case VEC_TYPE::UINT16 :
		case VEC_TYPE::INT16 :
			return sizeof( uint16_t );
		case VEC_TYPE::UINT32 :
		case VEC_TYPE::INT32 :
			return sizeof( uint32_t );
		case VEC_TYPE::UINT64 :
		case VEC_TYPE::INT64 :
			return sizeof( uint64_t );
		case VEC_TYPE::FLOAT :
			return sizeof( float );
		case VEC_TYPE::DOUBLE :
			return sizeof( double );
	}
	return 0;
}
