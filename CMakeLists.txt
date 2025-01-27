cmake_minimum_required( VERSION 3.19 )

set( CMAKE_C_STANDARD 99 )
set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_C_VISIBILITY_PRESET hidden )

set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_VISIBILITY_PRESET hidden )

find_package( CmakeFuncs REQUIRED PATHS "${CMAKE_CURRENT_SOURCE_DIR}/srcs/cmakeFuncs/CmakeFuncs" )

normal_project_name( prject_name ${CMAKE_CURRENT_SOURCE_DIR}  )
message( "============ ${prject_name}" )
message( "name = " ${prject_name} )
project( ${prject_name} VERSION 0.1 LANGUAGES CXX )
message( "============ ${CURRENT_FOLDER}" )

include( GenerateExportHeader )
include( GNUInstallDirs )

set( Project_Run_Bin_Path "${CMAKE_HOME_DIRECTORY}/builder/${CMAKE_BUILD_TYPE}/${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}_${CMAKE_CXX_COMPILER_ID}_bin/" )
set( Project_Run_Pbd_Path "${CMAKE_HOME_DIRECTORY}/builder/${CMAKE_BUILD_TYPE}/${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}_${CMAKE_CXX_COMPILER_ID}_pbd/" )
set( Project_Run_Static_Lib_Path "${CMAKE_HOME_DIRECTORY}/builder/${CMAKE_BUILD_TYPE}/${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}_${CMAKE_CXX_COMPILER_ID}_lib/" )
set( Project_Install_Path "${CMAKE_HOME_DIRECTORY}/builder/install/" )

# # 根部定义的模板位置
get_temp_file_dir_path( cmake_definitions_tmp )
set( cmake_definitions_env_in "${cmake_definitions_tmp}/cmake_in/cmake_to_c_cpp_header_env.h.in" )
set( cmake_auto_sub_dir_name "auto_generate_files" )

get_path_cmake_dir_path( lib_list "${CMAKE_CURRENT_SOURCE_DIR}/srcs/libs/users" "CMakeLists.txt" )
get_path_cmake_dir_path( bin_list "${CMAKE_CURRENT_SOURCE_DIR}/srcs/book sources/" "CMakeLists.txt" )
get_path_cmake_dir_path( bin_list "${CMAKE_CURRENT_SOURCE_DIR}/srcs/test code/" "CMakeLists.txt" )

list( APPEND out_path_list ${lib_list} ${bin_list} )

set( libs_path "${CMAKE_CURRENT_SOURCE_DIR}/srcs/libs/" )

get_cmake_separator( cmake_sep_char )

filter_path_repetition( list_result out_path_list )
append_sub_directory_cmake_project_path( list_result )
