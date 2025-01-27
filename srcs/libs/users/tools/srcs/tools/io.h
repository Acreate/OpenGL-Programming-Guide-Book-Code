#ifndef IO_H_H_HEAD__FILE__
#define IO_H_H_HEAD__FILE__
#pragma once
#include "toolsNamespace.h"
#include <string>
namespace cyl::tools::io {
	/**
	* @brief 发出错误信息
	* @param error_info 错误信息
	* @param error_file 错误文件
	* @param error_call_function_name 调用函数名称
	* @param file_line 错误行
	* @return 格式化完成的异常信息
	*/
	TOOLS_EXPORT std::string error_print_to_std_errorio( const std::string &error_info, const std::string &error_file, const std::string &error_call_function_name, const size_t file_line );
	/**
	* @brief 输出一个信息
	* @param out_info 信息内容
	* @param out_file 信息输出文件
	* @param out_call_function_name 调用函数名称
	* @param file_line 输出行
	* @return 格式化完成的信息
	*/
	TOOLS_EXPORT std::string out_print_to_std_outio( const std::string &out_info, const std::string &out_file, const std::string &out_call_function_name, const size_t file_line );
};
#include "path.h"

/**
 * @brief 输出标准信息
 * @param Msg 信息
 */
#define Printer_Normal_Info( Msg  ) cyl::tools::io::out_print_to_std_outio(std::string("") +Msg, current_relatively_path, __FUNCTION__, __LINE__)

/**
 * @brief 输出一个异常信息
 * @param Msg 异常信息
 */
#define Printer_Error_Info( Msg  ) cyl::tools::io::error_print_to_std_errorio( std::string("") + Msg, current_relatively_path, __FUNCTION__, __LINE__)

#endif // IO_H_H_HEAD__FILE__
