#ifndef PATH_H_H_HEAD__FILE__
#define PATH_H_H_HEAD__FILE__
#pragma once

#include <filesystem>
#include <string>
#include "toolsNamespace.h"
#include <memory>
#include <vector>
class TOOLS_EXPORT cyl::tools::path {
public:
	/// @brief 根路径
	static const std::filesystem::path root_path;
	/**
	* @brief 获取给予项目根路径的路径
	* @param file_path 绝对路径
	* @return 相对路径
	*/
	static path getCmakeSourceRelativelyPath( const std::string &file_path );

	/// @brief 获取工作路径
	/// @return 当前工作路径
	static cyl::tools::path getWorkPath( );
private:
	/// @brief 对象当前路径
	std::filesystem::path currentPath;
public:
	/// @brief 根据路径创建一个对象
	/// @param current_path 路径
	path( const std::filesystem::path &current_path )
		: currentPath( current_path ) { }
	/// @brief 根据路径创建一个对象
	/// @param current_path 路径
	path( const std::string &current_path )
		: currentPath( current_path ) { }
	/// @brief 创建一个对象，对象为当前工作路径
	path( ) {
	}
public:
	/// @brief 获取路径标准库（std::filesystem::path）对象
	/// @return 标准库对象
	std::filesystem::path getCurrentPath( ) const { return currentPath; }
	/// @brief 重设路径
	/// @param current_path 新路径
	void setCurrentPath( const std::filesystem::path &current_path ) { currentPath = current_path; }
	void setCurrentPath( const std::string &current_path ) { currentPath = current_path; }
	void setCurrentPath( const std::wstring &current_path ) { currentPath = current_path; }
	std::string string( ) const {
		return currentPath.string( );
	}
	operator std::string( ) const {
		return currentPath.string( );
	}
	/// @brief 获取父级目录
	/// @return 父级目录
	path getParent( ) const {

		return currentPath.parent_path( );
	}
	/// @brief 返回根级目录
	/// @return 根级目录
	path getRoot( ) const {
		return currentPath.root_path( );
	}

	/// @brief 从路径当中读取文件内容
	/// @param result 返回内容
	/// @return 文件内容长度，0 表示失败，或者不存在
	size_t readPathFile( std::wstring *result ) const;
	/// @brief 向文件写入内容
	/// @param content 文件内容
	/// @return 写入个数
	size_t writePathFile( const std::wstring &content ) const;
	/// @brief 从路径当中读取文件内容
	/// @param result 返回内容
	/// @return 文件内容长度，0 表示失败，或者不存在
	size_t readPathFile( std::string *result ) const;
	/// @brief 向文件写入内容
	/// @param content 文件内容
	/// @return 写入个数
	size_t writePathFile( const std::string &content ) const;

	/// @brief 从路径当中读取文件内容-二进制实现
	/// @param result 返回内容
	/// @return 文件内容长度，0 表示失败，或者不存在
	size_t readPathFile( std::vector< uint8_t > *result ) const;
	/// @brief 向文件写入内容-二进制实现
	/// @param content 文件内容
	/// @return 写入个数
	size_t writePathFile( const std::vector< uint8_t > &content ) const;
	/// @brief 向文件写入内容-二进制实现
	/// @param content 文件内容
	/// @return 写入个数
	size_t writePathFile( const std::vector< int8_t > &content ) const;
	/// @brief 获取绝对路径
	/// @return 绝对路径
	cyl::tools::path getAbsPath( ) const;

	/// @brief 创建目录
	/// @return 成功返回 true
	bool createPathDir( ) const;
	/// @brief 创建文件
	/// @return 成功返回 true
	bool createPathFile( ) const;
	/// @brief 检查路径是否存在
	/// @return 存在返回 true
	bool isExists( ) const;
	/// @brief 检查路径是否为文件
	/// @return 文件返回 true
	bool isFile( ) const;
	/// @brief 检查路径是否为文件夹
	/// @return 文件夹返回 true
	bool isDir( ) const;
	/// @brief 删除路径下所有的文件/文件夹
	/// @return 删除路径个数
	size_t removeAll( ) const;
	/// @brief 删除路径，只删除该路径单一文件或目录
	/// @return 成功返回 true
	bool removeThisOne( ) const;
	/// @brief 获取当前执行程序文件路径
	/// @return 返回当前执行程序文件路径
	cyl::tools::path getRunFilePath( ) const;
	/// @brief 获取路径的信息，返回该目录与文件的路径列表-不进入子目录
	/// @param file_vector 文件路径存储容器
	/// @param dir_vector 目录路径存储容器
	/// @return  文件夹与文件的数量
	size_t getPathDirAndFile( std::vector< std::string > *file_vector, std::vector< std::string > *dir_vector ) const;
	/// @brief 获取路径的信息，返回该目录与文件的路径列表-进入子目录
	/// @param file_vector 文件路径存储容器
	/// @param dir_vector 目录路径存储容器
	/// @return  文件夹与文件的数量
	size_t getPathDirAndFileRecursive( std::vector< std::string > *file_vector, std::vector< std::string > *dir_vector ) const;
	/// @brief 获取路径的信息，返回该目录与文件的路径列表
	/// @param file_vector 文件路径存储容器
	/// @param dir_vector 目录路径存储容器
	/// @param is_cd_in_dir 是否进入子目录
	/// @return  文件夹与文件的数量
	size_t getPathDirAndFile( std::vector< std::string > *file_vector, std::vector< std::string > *dir_vector, bool is_cd_in_dir ) {
		if( is_cd_in_dir )
			return getPathDirAndFileRecursive( file_vector, dir_vector );
		return getPathDirAndFile( file_vector, dir_vector );
	}

	/// @brief 获取当前工作路径的信息，返回该目录与文件的路径列表
	/// @param file_vector 文件路径存储容器
	/// @param dir_vector 目录路径存储容器
	/// @param is_cd_in_dir 是否进入子目录
	/// @return  文件夹与文件的数量
	size_t getPathDirAndFile( std::vector< std::string > *file_vector, std::vector< std::string > *dir_vector, bool is_cd_in_dir ) const;
};

/**
 * @brief 定义 current_relatively_path 静态变量，激活 Printer_Error_Info、Printer_Normal_Info 的使用
 * @param FILE 当前文件路径，一般使用 __FILE__ 当作参数
 */
# define DEF_CURRENT_RELATIVELY_PATH_STATIC_VALUE( FILE   )\
	const static cyl::tools::path current_relatively_path = cyl::tools::path::getCmakeSourceRelativelyPath(FILE)
/**
 * @brief 定义当前项目名称宏
 */
# define DEF_CURRENT_PROJECT_NAME(   ) const static std::string project_name = Cmake_Project_Name
#endif // PATH_H_H_HEAD__FILE__
