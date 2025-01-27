#include "stringTools.h"
#include <cwctype>
#include <codecvt>
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
//
//size_t cyl::tools::stringTools::converString( const std::string &conver_str, std::wstring &result_str ) {
//	std::wstring_convert< std::codecvt_utf8< wchar_t > > myconv;
//	result_str = myconv.from_bytes( conver_str );
//	return conver_str.size( );
//}
//size_t cyl::tools::stringTools::converString( const std::string &conver_str, std::wstring &result_str, const std::locale &locale ) {
//	std::vector< std::wstring::value_type > buff( conver_str.size( ) );
//	std::use_facet< std::ctype< std::wstring::value_type > >( locale ).widen( conver_str.data( ), conver_str.data( ) + conver_str.size( ), buff.data( ) );
//	result_str = std::wstring( buff.data( ), buff.size( ) );
//	return conver_str.size( );
//}
//size_t cyl::tools::stringTools::converString( const std::wstring &conver_str, std::string &result_str ) {
//	std::wstring_convert< std::codecvt_utf8< wchar_t > > myconv;
//	result_str = myconv.to_bytes( conver_str );
//	return conver_str.size( );
//}
//size_t cyl::tools::stringTools::converString( const std::wstring &conver_str, std::string &result_str, const std::locale &locale ) {
//	std::vector< std::string::value_type > buff( conver_str.size( ) );
//	std::use_facet< std::ctype< std::wstring::value_type > >( locale ).narrow( conver_str.data( ), conver_str.data( ) + conver_str.size( ), '?', buff.data( ) );
//	result_str = std::string( buff.data( ), buff.size( ) );
//	return conver_str.size( );
//}
size_t cyl::tools::stringTools::converString( const ToolsString &wstr, std::string *result ) {
	std::string strLocale = setlocale( LC_ALL, "" );
	const wchar_t *wchSrc = wstr.c_str( );
	size_t nDestSize = wcstombs( NULL, wchSrc, 0 ) + 1;
	char *chDest = new char[ nDestSize ];
	memset( chDest, 0, nDestSize );
	wcstombs( chDest, wchSrc, nDestSize );
	*result = chDest;
	delete[] chDest;
	setlocale( LC_ALL, strLocale.c_str( ) );
	return nDestSize;
}
size_t cyl::tools::stringTools::converString( const std::string &mbs, cyl::tools::ToolsString *result ) {
	std::string strLocale = setlocale( LC_ALL, "" );
	const char *chSrc = mbs.c_str( );
	size_t nDestSize = mbstowcs( NULL, chSrc, 0 ) + 1;
	wchar_t *wchDest = new wchar_t[ nDestSize ];
	wmemset( wchDest, 0, nDestSize );
	mbstowcs( wchDest, chSrc, nDestSize );
	*result = wchDest;
	delete[ ] wchDest;
	setlocale( LC_ALL, strLocale.c_str( ) );
	return nDestSize;
}
cyl::tools::ToolsString cyl::tools::stringTools::toUpper( const ToolsString &conver_tools_string ) {
	auto strPtr = conver_tools_string.c_str( );
	auto len = conver_tools_string.length( );
	std::vector< ToolsString::value_type > data( len );
	auto index = 0;
	auto dataPtr = data.data( );
	for( ; index < len; ++index )
		dataPtr[ index ] = std::towupper( strPtr[ index ] );
	return ToolsString( dataPtr, index );
}
cyl::tools::ToolsString cyl::tools::stringTools::toLower( const ToolsString &conver_tools_string ) {
	auto strPtr = conver_tools_string.c_str( );
	auto len = conver_tools_string.length( );
	std::vector< ToolsString::value_type > data( len );
	auto index = 0;
	auto dataPtr = data.data( );
	for( ; index < len; ++index )
		dataPtr[ index ] = std::towlower( strPtr[ index ] );
	return ToolsString( dataPtr, index );
}
cyl::tools::ToolsString cyl::tools::stringTools::removeAllSpaceChar( const ToolsString &conver_tools_string ) {
	auto strPtr = conver_tools_string.c_str( );
	auto len = conver_tools_string.length( );
	std::vector< ToolsString::value_type > data( len );
	auto index = 0, dataIndex = 0;
	auto dataPtr = data.data( );
	for( ; index < len; ++index )
		if( isSpace( strPtr[ index ] ) )
			dataPtr[ dataIndex++ ] = strPtr[ index ];
	return ToolsString( dataPtr, dataIndex );
}
bool cyl::tools::stringTools::isSpace( const ToolsString::value_type &check_char ) {
	if( std::iswblank( check_char ) || std::isspace( check_char ) || std::iswcntrl( check_char ) || !std::isprint( check_char ) )
		return true;
	return false;
}
cyl::tools::ToolsString cyl::tools::stringTools::replaceSubString( const CharValueType *org_str, const size_t org_str_len, const CharValueType *replace_src_str, const size_t replace_src_str_len, const CharValueType *replace_target_str, const size_t replace_target_str_len, size_t replace_count ) {
	if( replace_count == 0 )
		return org_str;
	std::wstringstream ss; // 流字符串对象
	if( org_str_len > 0 && replace_src_str_len > 0 ) { // 需要原始字符串与匹配长度都大于 0
		size_t buffLen = 1024; // 缓冲大小
		CharValueType *buff = new CharValueType[ buffLen ]; // 缓冲
		size_t buffIndex = 0; // 缓冲下标
		size_t orgStrIndex = 0; // 原始字符串访问下标
		while( orgStrIndex < org_str_len ) { // 遍历
			CharValueType refChar = org_str[ orgStrIndex ];
			if( refChar == replace_src_str[ 0 ] ) {
				size_t replaceStrIndex = 1; // 匹配字符串长度下标
				if( replaceStrIndex < replace_src_str_len )
					for( size_t cloneOrgStrIndex = orgStrIndex + 1; replaceStrIndex < replace_src_str_len && cloneOrgStrIndex < org_str_len; ++replaceStrIndex, ++cloneOrgStrIndex )
						if( org_str[ cloneOrgStrIndex ] != replace_src_str[ replaceStrIndex ] )
							break;
				if( replaceStrIndex == replace_src_str_len ) {
					if( buffIndex > 0 ) {
						ss << std::wstring( buff, buffIndex ); // 追加到字符串
						buffIndex = 0;
					}
					if( replace_target_str_len )
						ss << replace_target_str; // 追加到字符串
					orgStrIndex += replace_src_str_len; // 追加下标
					replace_count -= 1;
					if( replace_count == 0 ) { // 次数足够则跳出循环
						if( orgStrIndex < org_str_len ) // 处理未处理字符串
							ss << org_str + orgStrIndex;
						break;
					}
					continue;
				}
			}
			buff[ buffIndex ] = refChar;
			buffIndex += 1;
			if( buffIndex == buffLen ) {
				ss << std::wstring( buff, buffIndex ); // 追加到字符串
				buffIndex = 0;
			}
			++orgStrIndex;
		}
		if( buffIndex != 0 )
			ss << std::wstring( buff, buffIndex ); // 追加到字符串
		delete[] buff;
	}

	return ss.str( );
}
cyl::tools::ToolsString cyl::tools::stringTools::replaceSubString( const CharValueType *org_str, const size_t org_str_len, const CharValueType *replace_src_str, const size_t replace_src_str_len, const CharValueType *replace_target_str, const size_t replace_target_str_len ) {
	std::wstringstream ss; // 流字符串对象
	if( org_str_len > 0 && replace_src_str_len > 0 ) { // 需要原始字符串与匹配长度都大于 0
		size_t buffLen = 1024; // 缓冲大小
		CharValueType *buff = new CharValueType[ buffLen ]; // 缓冲
		size_t buffIndex = 0; // 缓冲下标
		size_t orgStrIndex = 0; // 原始字符串访问下标
		while( orgStrIndex < org_str_len ) { // 遍历
			CharValueType refChar = org_str[ orgStrIndex ];
			if( refChar == replace_src_str[ 0 ] ) {
				size_t replaceStrIndex = 1; // 匹配字符串长度下标
				if( replaceStrIndex < replace_src_str_len )
					for( size_t cloneOrgStrIndex = orgStrIndex + 1; replaceStrIndex < replace_src_str_len && cloneOrgStrIndex < org_str_len; ++replaceStrIndex, ++cloneOrgStrIndex )
						if( org_str[ cloneOrgStrIndex ] != replace_src_str[ replaceStrIndex ] )
							break;
				if( replaceStrIndex == replace_src_str_len ) {
					if( buffIndex > 0 ) {
						ss << std::wstring( buff, buffIndex ); // 追加到字符串
						buffIndex = 0;
					}
					if( replace_target_str_len )
						ss << replace_target_str; // 追加到字符串
					orgStrIndex += replace_src_str_len; // 追加下标
					continue;
				}

			}
			buff[ buffIndex ] = refChar;
			buffIndex += 1;
			if( buffIndex == buffLen ) {
				ss << std::wstring( buff, buffIndex ); // 追加到字符串
				buffIndex = 0;
			}
			++orgStrIndex;
		}
		if( buffIndex != 0 )
			ss << std::wstring( buff, buffIndex ); // 追加到字符串
		delete[] buff;
	}

	return ss.str( );
}
cyl::tools::ToolsString cyl::tools::stringTools::replaceSubStringOnLast( ToolsString org_str, ToolsString replace_src_str, ToolsString replace_target_str, size_t replace_count ) {
	std::reverse( org_str.begin( ), org_str.end( ) ); // 重新逆转
	std::reverse( replace_src_str.begin( ), replace_src_str.end( ) ); // 重新逆转
	std::reverse( replace_target_str.begin( ), replace_target_str.end( ) ); // 重新逆转
	// 替换完毕的字符串
	auto replaceWString = replaceSubString( org_str.c_str( ), org_str.length( ), replace_src_str.c_str( ), replace_src_str.length( ), replace_target_str.c_str( ), replace_target_str.length( ), replace_count );
	std::reverse( replaceWString.begin( ), replaceWString.end( ) ); // 重新逆转
	return replaceWString; // 返回逆转后的字符串
}
