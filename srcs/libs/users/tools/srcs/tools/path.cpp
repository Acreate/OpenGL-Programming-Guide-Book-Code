#include "path.h"

#include <filesystem>
#include <fstream>
#include <Windows.h>
#include "io.h"
#include "../auto_generate_files/macro/cmake_to_c_cpp_header_env.h"
DEF_CURRENT_RELATIVELY_PATH_STATIC_VALUE( __FILE__ );
/// @brief 静态函数
const std::filesystem::path cyl::tools::path::root_path = Cmake_Source_Dir;
cyl::tools::path cyl::tools::path::getCmakeSourceRelativelyPath( const std::string &file_path ) {
	return cyl::tools::path( std::filesystem::relative( file_path, cyl::tools::path::root_path ) );
}

cyl::tools::path cyl::tools::path::getWorkPath( ) {
	return cyl::tools::path( std::filesystem::current_path( ) );
}

size_t cyl::tools::path::readPathFile( std::wstring *result ) const {
	size_t readCount = 0;
	if( result == nullptr )
		return readCount;
	auto absPath = std::filesystem::absolute( currentPath );
	if( std::filesystem::exists( absPath ) && !std::filesystem::is_directory( absPath ) ) {
		std::wifstream readFile;
		readFile.open( absPath.string( ), std::ios_base::binary | std::ios_base::in );
		if( readFile.is_open( ) ) {
			std::wstring::value_type buff[ 1024 ];
			std::wstringstream ss;
			do {
				std::streamsize gcount = readFile.read( buff, 1024 ).gcount( );
				if( gcount == 0 )
					break;
				ss << std::wstring( buff, gcount );
				readCount += gcount;
			} while( true );
			readFile.close( );
			*result = ss.str( );
		}
	}
	return readCount;
}
size_t cyl::tools::path::writePathFile( const std::wstring &content ) const {
	auto length = content.length( );
	if( length == 0 ) // 长度为 0，返回
		return 0;
	if( std::filesystem::exists( currentPath ) ) { // 存在
		if( std::filesystem::is_directory( currentPath ) ) // 但是该路径为文件夹
			return 0;
		std::wofstream writeFile;
		writeFile.open( currentPath.string( ), std::ios_base::binary | std::ios_base::out | std::ios_base::trunc );
		if( writeFile.is_open( ) ) {
			auto cPtr = content.c_str( );
			size_t before = writeFile.tellp( ); // 开始位置
			writeFile.write( cPtr, length );
			size_t endOffset = writeFile.tellp( ); // 结束位置
			writeFile.close( );
			return endOffset - before; // 返回相对位置
		}
	} else {
		auto parenPath = currentPath.parent_path( );
		if( std::filesystem::exists( parenPath ) || std::filesystem::create_directories( parenPath ) ) { // 创建成功
			std::wofstream writeFile;
			writeFile.open( currentPath.string( ), std::ios_base::binary | std::ios_base::out | std::ios_base::trunc );
			if( writeFile.is_open( ) ) {
				auto cPtr = content.c_str( );
				size_t before = writeFile.tellp( ); // 开始位置
				writeFile.write( cPtr, length );
				size_t endOffset = writeFile.tellp( ); // 结束位置
				writeFile.close( );
				return endOffset - before; // 返回相对位置
			}
		}
	}
	return 0;
}
size_t cyl::tools::path::readPathFile( std::string *result ) const {
	size_t readCount = 0;
	if( result == nullptr )
		return readCount;
	if( std::filesystem::exists( currentPath ) && !std::filesystem::is_directory( currentPath ) ) {
		std::ifstream readFile;
		readFile.open( currentPath.string( ), std::ios_base::binary | std::ios_base::in );
		if( readFile.is_open( ) ) {
			char buff[ 1024 ];
			std::stringstream ss;
			do {
				std::streamsize gcount = readFile.read( buff, 1024 ).gcount( );
				if( gcount == 0 )
					break;
				ss << std::string( buff, gcount );
				readCount += gcount;
			} while( true );
			readFile.close( );
			*result = ss.str( );
		}
	}
	return readCount;
}

size_t cyl::tools::path::readPathFile( std::vector< uint8_t > *result ) const {
	size_t readCount = 0;
	if( result == nullptr )
		return readCount;
	if( std::filesystem::exists( currentPath ) && !std::filesystem::is_directory( currentPath ) ) {
		std::ifstream readFile;
		readFile.open( currentPath.string( ), std::ios_base::binary | std::ios_base::in );
		if( readFile.is_open( ) ) {
			char buff[ 1024 ];
			std::vector< std::vector< uint8_t > > binVectors; // 二级容器
			size_t index = 0;
			uint8_t *dataPtr = nullptr;
			do {
				std::streamsize gcount = readFile.read( buff, 1024 ).gcount( );
				if( gcount == 0 )
					break;
				readCount += gcount;
				std::vector< uint8_t > binVector( gcount ); // 一级容器
				dataPtr = binVector.data( );
				for( index = 0; index < gcount; ++index )
					dataPtr[ index ] = buff[ index ];
				binVectors.emplace_back( binVector );
			} while( true );
			index = 0;
			result->clear( );
			result->resize( readCount );
			dataPtr = result->data( );
			for( auto &saveData : binVectors )
				for( auto &saveDataUnity : saveData )
					dataPtr[ index++ ] = saveDataUnity;
			readFile.close( );
		}
	}
	return readCount;
}
size_t cyl::tools::path::writePathFile( const std::vector< uint8_t > &content ) const {
	auto length = content.size( );
	if( length == 0 ) // 长度为 0，返回
		return 0;
	if( std::filesystem::exists( currentPath ) ) { // 存在
		if( std::filesystem::is_directory( currentPath ) ) // 但是该路径为文件夹
			return 0;
		std::ofstream writeFile;
		writeFile.open( currentPath.string( ), std::ios_base::binary | std::ios_base::out | std::ios_base::trunc );
		if( writeFile.is_open( ) ) {
			auto cPtr = ( const char * ) content.data( );
			size_t before = writeFile.tellp( ); // 开始位置
			writeFile.write( cPtr, length );
			size_t endOffset = writeFile.tellp( ); // 结束位置
			writeFile.close( );
			return endOffset - before; // 返回相对位置
		}
	} else {
		auto parenPath = currentPath.parent_path( );
		if( std::filesystem::exists( parenPath ) || std::filesystem::create_directories( parenPath ) ) { // 创建成功
			std::ofstream writeFile;
			writeFile.open( currentPath.string( ), std::ios_base::binary | std::ios_base::out | std::ios_base::trunc );
			if( writeFile.is_open( ) ) {
				auto cPtr = ( const char * ) content.data( );
				size_t before = writeFile.tellp( ); // 开始位置
				writeFile.write( cPtr, length );
				size_t endOffset = writeFile.tellp( ); // 结束位置
				writeFile.close( );
				return endOffset - before; // 返回相对位置
			}
		}
	}
	return 0;
}
size_t cyl::tools::path::writePathFile( const std::vector< int8_t > &content ) const {
	auto length = content.size( );
	if( length == 0 ) // 长度为 0，返回
		return 0;
	if( std::filesystem::exists( currentPath ) ) { // 存在
		if( std::filesystem::is_directory( currentPath ) ) // 但是该路径为文件夹
			return 0;
		std::ofstream writeFile;
		writeFile.open( currentPath.string( ), std::ios_base::binary | std::ios_base::out | std::ios_base::trunc );
		if( writeFile.is_open( ) ) {
			auto cPtr = ( const char * ) content.data( );
			size_t before = writeFile.tellp( ); // 开始位置
			writeFile.write( cPtr, length );
			size_t endOffset = writeFile.tellp( ); // 结束位置
			writeFile.close( );
			return endOffset - before; // 返回相对位置
		}
	} else {
		auto parenPath = currentPath.parent_path( );
		if( std::filesystem::exists( parenPath ) || std::filesystem::create_directories( parenPath ) ) { // 创建成功
			std::ofstream writeFile;
			writeFile.open( currentPath.string( ), std::ios_base::binary | std::ios_base::out | std::ios_base::trunc );
			if( writeFile.is_open( ) ) {
				auto cPtr = ( const char * ) content.data( );
				size_t before = writeFile.tellp( ); // 开始位置
				writeFile.write( cPtr, length );
				size_t endOffset = writeFile.tellp( ); // 结束位置
				writeFile.close( );
				return endOffset - before; // 返回相对位置
			}
		}
	}
	return 0;
}

size_t cyl::tools::path::writePathFile( const std::string &content ) const {
	auto length = content.length( );
	if( length == 0 ) // 长度为 0，返回
		return 0;
	if( std::filesystem::exists( currentPath ) ) { // 存在
		if( std::filesystem::is_directory( currentPath ) ) // 但是该路径为文件夹
			return 0;
		std::ofstream writeFile;
		writeFile.open( currentPath.string( ), std::ios_base::binary | std::ios_base::out | std::ios_base::trunc );
		if( writeFile.is_open( ) ) {
			auto cPtr = content.c_str( );
			size_t before = writeFile.tellp( ); // 开始位置
			writeFile.write( cPtr, length );
			size_t endOffset = writeFile.tellp( ); // 结束位置
			writeFile.close( );
			return endOffset - before; // 返回相对位置
		}
	} else {
		auto parenPath = currentPath.parent_path( );
		if( std::filesystem::exists( parenPath ) || std::filesystem::create_directories( parenPath ) ) { // 创建成功
			std::ofstream writeFile;
			writeFile.open( currentPath.string( ), std::ios_base::binary | std::ios_base::out | std::ios_base::trunc );
			if( writeFile.is_open( ) ) {
				auto cPtr = content.c_str( );
				size_t before = writeFile.tellp( ); // 开始位置
				writeFile.write( cPtr, length );
				size_t endOffset = writeFile.tellp( ); // 结束位置
				writeFile.close( );
				return endOffset - before; // 返回相对位置
			}
		}
	}
	return 0;
}

cyl::tools::path cyl::tools::path::getAbsPath( ) const {
	return cyl::tools::path( std::filesystem::absolute( currentPath ) );
}
bool cyl::tools::path::createPathDir( ) const {
	return std::filesystem::create_directories( currentPath );
}
bool cyl::tools::path::createPathFile( ) const {
	try {
		auto parent = getParent( );
		if( !parent.isExists( ) )
			parent.createPathDir( );
		std::ofstream ofstream;
		ofstream.open( getAbsPath( ).currentPath, std::ofstream::binary | std::ios_base::out | std::ios_base::trunc );
		if( ofstream.is_open( ) )
			ofstream.write( "", 0 );

		return true;
	} catch( const std::exception &exception ) {
		Printer_Error_Info( exception.what( ) );
		return false;
	}

}
bool cyl::tools::path::isExists( ) const {
	return std::filesystem::exists( currentPath );
}
bool cyl::tools::path::isFile( ) const {
	if( std::filesystem::exists( currentPath ) )
		return !std::filesystem::is_directory( currentPath );
	return false;
}
bool cyl::tools::path::isDir( ) const {
	if( std::filesystem::exists( currentPath ) )
		return std::filesystem::is_directory( currentPath );
	return false;
}
size_t cyl::tools::path::removeAll( ) const {
	return std::filesystem::remove_all( currentPath );
}
bool cyl::tools::path::removeThisOne( ) const {
	std::filesystem::path removePath( currentPath );
	try {
		return std::filesystem::remove( removePath );
	} catch( ... ) {
		Printer_Error_Info( "未能删除文件 [ " + std::filesystem::absolute( removePath ).string( ) + " ]" );
		return false;
	}

}
cyl::tools::path cyl::tools::path::getRunFilePath( ) const {
	char szPath[ 1024 * 4 ] = { };
	GetModuleFileName( nullptr, szPath, sizeof( szPath ) - 1 );
	std::string resultPath( szPath );
	return cyl::tools::path( resultPath );
}

size_t cyl::tools::path::getPathDirAndFile( std::vector< std::string > *file_vector, std::vector< std::string > *dir_vector ) const {
	if( std::filesystem::exists( currentPath ) && std::filesystem::is_directory( currentPath ) ) {
		std::filesystem::directory_iterator directoryIterator( currentPath );
		std::filesystem::directory_iterator endIterator;
		while( directoryIterator != endIterator ) {
			auto absPath = std::filesystem::absolute( directoryIterator->path( ) ).string( );
			if( directoryIterator->is_directory( ) )
				dir_vector->emplace_back( absPath );
			else
				file_vector->emplace_back( absPath );
			++directoryIterator;
		}
	}
	return file_vector->size( ) + dir_vector->size( );
}
size_t cyl::tools::path::getPathDirAndFileRecursive( std::vector< std::string > *file_vector, std::vector< std::string > *dir_vector ) const {
	if( std::filesystem::exists( currentPath ) && std::filesystem::is_directory( currentPath ) ) {
		using directory_iterator = std::filesystem::recursive_directory_iterator;
		directory_iterator directoryIterator( currentPath );
		directory_iterator endIterator;
		while( directoryIterator != endIterator ) {
			auto absPath = std::filesystem::absolute( directoryIterator->path( ) ).string( );
			if( directoryIterator->is_directory( ) )
				dir_vector->emplace_back( absPath );
			else
				file_vector->emplace_back( absPath );
			++directoryIterator;
		}
	}
	return file_vector->size( ) + dir_vector->size( );
}
size_t cyl::tools::path::getPathDirAndFile( std::vector< std::string > *file_vector, std::vector< std::string > *dir_vector, bool is_cd_in_dir ) const {
	if( is_cd_in_dir )
		return getPathDirAndFileRecursive( file_vector, dir_vector );
	return getPathDirAndFile( file_vector, dir_vector );
}
