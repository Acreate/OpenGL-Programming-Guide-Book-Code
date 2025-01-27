#include "image.h"
size_t cyl::tools::Image::converColorDataToPng( const uint8_t *data_ptr, size_t data_size, uint32_t width, uint32_t height, std::vector< uint8_t > *result_vector ) {

	if( data_ptr == nullptr || data_size == 0 || width == 0 || height == 0 || result_vector == nullptr )
		return 0;
	
	size_t newsize = width * height * sizeof uint8_t * 4;
	// 宽度 * 高度 * 4 色
	auto pixels = new uint8_t [ newsize ];

	std::vector< uint8_t > pngHead;
	// png 文件头
	pngHead.emplace_back( 0x89 );
	pngHead.emplace_back( 0x50 );
	pngHead.emplace_back( 0x4e );
	pngHead.emplace_back( 0x47 );
	pngHead.emplace_back( 0x0d );
	pngHead.emplace_back( 0x0a );
	pngHead.emplace_back( 0x1a );
	pngHead.emplace_back( 0x0a );
	// ihdr 标识结构大小
	pngHead.emplace_back( 0x00 );
	pngHead.emplace_back( 0x00 );
	pngHead.emplace_back( 0x00 );
	pngHead.emplace_back( 0x0d );
	// ihdr 标识
	pngHead.emplace_back( 0x49 );
	pngHead.emplace_back( 0x48 );
	pngHead.emplace_back( 0x44 );
	pngHead.emplace_back( 0x52 );

	int testBeg = 0x0001;
	auto isZeroToStart = ( ( uint8_t * ) &testBeg )[ 0 ] == 0; // 是否顺字节

	// ihdr 数据 ->
	if( isZeroToStart ) {
		auto newWidthPtr = ( uint8_t * ) &width; // 保存长度
		pngHead.emplace_back( newWidthPtr[ 0 ] );
		pngHead.emplace_back( newWidthPtr[ 1 ] );
		pngHead.emplace_back( newWidthPtr[ 2 ] );
		pngHead.emplace_back( newWidthPtr[ 3 ] );
		auto newHeightPtr = ( uint8_t * ) &height; // 保存宽度
		pngHead.emplace_back( newHeightPtr[ 0 ] );
		pngHead.emplace_back( newHeightPtr[ 1 ] );
		pngHead.emplace_back( newHeightPtr[ 2 ] );
		pngHead.emplace_back( newHeightPtr[ 3 ] );
	} else {
		auto newWidthPtr = ( uint8_t * ) &width; // 保存长度
		pngHead.emplace_back( newWidthPtr[ 3 ] );
		pngHead.emplace_back( newWidthPtr[ 2 ] );
		pngHead.emplace_back( newWidthPtr[ 1 ] );
		pngHead.emplace_back( newWidthPtr[ 0 ] );
		auto newHeightPtr = ( uint8_t * ) &height; // 保存宽度
		pngHead.emplace_back( newHeightPtr[ 3 ] );
		pngHead.emplace_back( newHeightPtr[ 2 ] );
		pngHead.emplace_back( newHeightPtr[ 1 ] );
		pngHead.emplace_back( newHeightPtr[ 0 ] );
	}

	pngHead.emplace_back( 0x8 );
	pngHead.emplace_back( 0x2 );
	pngHead.emplace_back( 0x0 );
	pngHead.emplace_back( 0x0 );
	pngHead.emplace_back( 0x0 );

	std::vector< uint8_t > meg;
	size_t allSize = pngHead.size( ) + newsize + sizeof uint8_t * 4;
	result_vector->clear( );
	result_vector->resize( allSize );
	auto destPtr = result_vector->data( );
	size_t index = 0;
	auto copySourcePtr = pngHead.data( );
	for( size_t copyIndex = 0; copyIndex < pngHead.size( ); ++copyIndex, ++index )
		destPtr[ index ] = copySourcePtr[ copyIndex ];
	for( size_t copyIndex = 0; copyIndex < newsize; ++copyIndex, ++index )
		destPtr[ index ] = pixels[ copyIndex ];
	destPtr[ index++ ] = 0xae;
	destPtr[ index++ ] = 0x42;
	destPtr[ index++ ] = 0x60;
	destPtr[ index ] = 0x82;
	return allSize;
}
