#include "io.h"

#include <iostream>

std::string cyl::tools::io::error_print_to_std_errorio( const std::string &error_info, const std::string &error_file, const std::string &error_call_function_name, const size_t file_line ) {
	std::string outErrorInfo = "==========\n\t错误信息 : ";
	outErrorInfo.append( error_info );
	outErrorInfo.append( "\n\t错误文件 : " );
	outErrorInfo.append( error_file );
	outErrorInfo.append( "\n\t错误函数 : " );
	outErrorInfo.append( error_call_function_name );
	outErrorInfo.append( "\n\t错误行号 : " );
	outErrorInfo.append( std::to_string( file_line ) );
	outErrorInfo.append( "\n==========" );
	std::cerr << outErrorInfo << std::endl;
	return outErrorInfo;
}
std::string cyl::tools::io::out_print_to_std_outio( const std::string &out_info, const std::string &out_file, const std::string &out_call_function_name, const size_t file_line ) {
	std::string outStdIoInfo ;
	outStdIoInfo.append( "文件->( " );
	outStdIoInfo.append( out_file );
	outStdIoInfo.append( " ), 函数调用->{ " );
	outStdIoInfo.append( out_call_function_name );
	outStdIoInfo.append( " }, 行号-* " );
	outStdIoInfo.append( std::to_string( file_line ) );
	outStdIoInfo.append( "\n\t" );
	outStdIoInfo.append( "信息->" );
	outStdIoInfo.append( out_info );
	std::cout << outStdIoInfo << std::endl;
	return outStdIoInfo;
}