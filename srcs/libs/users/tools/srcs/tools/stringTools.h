#ifndef STRINGTOOLS_H_H_HEAD__FILE__
#define STRINGTOOLS_H_H_HEAD__FILE__
#pragma once

#include <codecvt>

#include "toolsNamespace.h"
namespace cyl::tools::stringTools {
	//TOOLS_EXPORT  size_t converString( const std::string &conver_str, std::wstring &result_str );
	//TOOLS_EXPORT size_t converString( const std::string &conver_str, std::wstring &result_str, const std::locale &locale );
	//TOOLS_EXPORT size_t converString( const std::wstring &conver_str, std::string &result_str );

	//TOOLS_EXPORT size_t converString( const std::wstring &conver_str, std::string &result_str, const std::locale &locale );
	/// @brief 宽字符串转多字节字符串
	/// @param wstr 宽字符串
	/// @param result
	/// @return 多字节字符串
	TOOLS_EXPORT size_t converString( const ToolsString &wstr, std::string *result );

	/// @brief 多字节转宽字符
	/// @param mbs 多字节字符串
	/// @param result
	/// @return 宽字符串
	TOOLS_EXPORT size_t converString( const std::string &mbs, std::wstring *result );
	/// @brief 字符串转大写
	/// @param conver_tools_string 转换的字符串
	TOOLS_EXPORT ToolsString toUpper( const ToolsString &conver_tools_string );
	/// @brief 字符串转小写
	/// @param conver_tools_string 转换的字符串
	TOOLS_EXPORT ToolsString toLower( const ToolsString &conver_tools_string );
	/// @brief 移除字符串全部空格
	/// @param conver_tools_string 移除的字符串
	TOOLS_EXPORT ToolsString removeAllSpaceChar( const ToolsString &conver_tools_string );
	/// @brief 判断是否为空字符
	/// @param check_char 校验字符
	/// @return 空字符返回 true
	TOOLS_EXPORT bool isSpace( const ToolsString::value_type &check_char );
	/// @brief 使用替换生成一个新的字符串
	/// @param org_str 原始字符串
	/// @param org_str_len 原始字符串长度
	/// @param replace_src_str 原始字符串当中被替换的字符串
	/// @param replace_src_str_len 匹配字符串的长度
	/// @param replace_target_str 匹配到替换字符串后填充的字符串
	/// @param replace_target_str_len 匹配替换的字符串长度
	/// @param replace_count 替换次数
	/// @return 新的字符串
	TOOLS_EXPORT std::wstring replaceSubString( const CharValueType *org_str, size_t org_str_len, const CharValueType *replace_src_str, size_t replace_src_str_len, const CharValueType *replace_target_str, size_t replace_target_str_len, size_t replace_count );

	/// @brief 使用替换生成一个新的字符串
	/// @param org_str 原始字符串
	/// @param org_str_len 原始字符串长度
	/// @param replace_src_str 原始字符串当中被替换的字符串
	/// @param replace_src_str_len 匹配字符串的长度
	/// @param replace_target_str 匹配到替换字符串后填充的字符串
	/// @param replace_target_str_len 匹配替换的字符串长度
	/// @return 新的字符串
	TOOLS_EXPORT std::wstring replaceSubString( const CharValueType *org_str, size_t org_str_len, const CharValueType *replace_src_str, size_t replace_src_str_len, const CharValueType *replace_target_str, size_t replace_target_str_len );

	/// @brief 使用替换生成一个新的字符串
	/// @param org_str 原始字符串
	/// @param replace_src_str 原始字符串当中被替换的字符串
	/// @param replace_target_str 匹配到替换字符串后填充的字符串
	/// @return 新的字符串
	TOOLS_EXPORT inline ToolsString replaceSubString( const CharValueType *org_str, const CharValueType *replace_src_str, const CharValueType *replace_target_str ) {
		return replaceSubString( org_str, std::wcslen( org_str ), replace_src_str, std::wcslen( replace_src_str ), replace_target_str, std::wcslen( replace_target_str ) );
	}
	/// @brief 使用替换生成一个新的字符串
	/// @param org_str 原始字符串
	/// @param replace_src_str 原始字符串当中被替换的字符串
	/// @param replace_target_str 匹配到替换字符串后填充的字符串
	/// @return 新的字符串
	TOOLS_EXPORT inline ToolsString replaceSubString( const ToolsString &org_str, const ToolsString &replace_src_str, const ToolsString &replace_target_str ) {
		return replaceSubString( org_str.c_str( ), org_str.length( ), replace_src_str.c_str( ), replace_src_str.length( ), replace_target_str.c_str( ), replace_target_str.length( ) );
	}

	/// @brief 使用替换生成一个新的字符串
	/// @param org_str 原始字符串
	/// @param replace_src_str 原始字符串当中被替换的字符串
	/// @param replace_target_str 匹配到替换字符串后填充的字符串
	/// @param replace_count 替换次数
	/// @return 新的字符串
	TOOLS_EXPORT inline ToolsString replaceSubString( const CharValueType *org_str, const CharValueType *replace_src_str, const CharValueType *replace_target_str, size_t replace_count ) {
		return replaceSubString( org_str, std::wcslen( org_str ), replace_src_str, std::wcslen( replace_src_str ), replace_target_str, std::wcslen( replace_target_str ), replace_count );
	}
	/// @brief 使用替换生成一个新的字符串
	/// @param org_str 原始字符串
	/// @param replace_src_str 原始字符串当中被替换的字符串
	/// @param replace_target_str 匹配到替换字符串后填充的字符串
	/// @param replace_count 替换次数
	/// @return 新的字符串
	TOOLS_EXPORT inline ToolsString replaceSubString( const ToolsString &org_str, const ToolsString &replace_src_str, const ToolsString &replace_target_str, size_t replace_count ) {
		return replaceSubString( org_str.c_str( ), org_str.length( ), replace_src_str.c_str( ), replace_src_str.length( ), replace_target_str.c_str( ), replace_target_str.length( ), replace_count );
	}

	/// @brief 使用替换生成一个新的字符串
	/// @param org_str 原始字符串
	/// @param replace_src_str 原始字符串当中被替换的字符串
	/// @param replace_target_str 匹配到替换字符串后填充的字符串
	/// @param replace_count 替换次数
	/// @return 新的字符串
	TOOLS_EXPORT inline std::string replaceSubString( const std::string &org_str, const std::string &replace_src_str, const std::string &replace_target_str, size_t replace_count ) {
		ToolsString ortStr, replaceSrcStr, replaceTargetStr;
		std::string result;
		if( converString( org_str, &ortStr ) && converString( replace_src_str, &replaceSrcStr ) && converString( replace_target_str, &replaceTargetStr ) ) {
			ToolsString wstring = replaceSubString( ortStr.c_str( ), ortStr.length( ), replaceSrcStr.c_str( ), replaceSrcStr.length( ), replaceTargetStr.c_str( ), replaceTargetStr.length( ), replace_count );
			converString( wstring, &result );
			return result;
		}
		return result;
	}

	/// @brief 使用替换生成一个新的字符串
	/// @param org_str 原始字符串
	/// @param replace_src_str 原始字符串当中被替换的字符串
	/// @param replace_target_str 匹配到替换字符串后填充的字符串
	/// @return 新的字符串
	TOOLS_EXPORT inline std::string replaceSubString( const std::string &org_str, const std::string &replace_src_str, const std::string &replace_target_str ) {
		ToolsString ortStr, replaceSrcStr, replaceTargetStr;
		std::string result;
		if( converString( org_str, &ortStr ) && converString( replace_src_str, &replaceSrcStr ) && converString( replace_target_str, &replaceTargetStr ) ) {
			ToolsString wstring = replaceSubString( ortStr.c_str( ), ortStr.length( ), replaceSrcStr.c_str( ), replaceSrcStr.length( ), replaceTargetStr.c_str( ), replaceTargetStr.length( ) );
			converString( wstring, &result );
		}
		return result;
	}

	/// @brief 从结束开始，使用替换生成一个新的字符串
	/// @param org_str 原始字符串
	/// @param replace_src_str 原始字符串当中被替换的字符串
	/// @param replace_target_str 匹配到替换字符串后填充的字符串
	/// @param replace_count 替换次数
	/// @return 新的字符串
	TOOLS_EXPORT ToolsString replaceSubStringOnLast( ToolsString org_str, ToolsString replace_src_str, ToolsString replace_target_str, size_t replace_count );
	/// @brief 从结束开始，使用替换生成一个新的字符串
	/// @param org_str 原始字符串
	/// @param replace_src_str 原始字符串当中被替换的字符串
	/// @param replace_target_str 匹配到替换字符串后填充的字符串
	/// @param replace_count 替换次数
	/// @return 新的字符串
	TOOLS_EXPORT inline std::string replaceSubStringOnLast( const std::string &org_str, const std::string &replace_src_str, const std::string &replace_target_str, size_t replace_count ) {
		ToolsString ortStr, replaceSrcStr, replaceTargetStr;
		std::string result;
		if( converString( org_str, &ortStr ) && converString( replace_src_str, &replaceSrcStr ) && converString( replace_target_str, &replaceTargetStr ) ) {
			ToolsString wstring = replaceSubStringOnLast( ortStr, replaceSrcStr, replaceTargetStr, replace_count );
			converString( wstring, &result );
			return result;
		}
		return result;
	}
};

#endif // STRINGTOOLS_H_H_HEAD__FILE__
