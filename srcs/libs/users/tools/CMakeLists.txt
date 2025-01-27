cmake_minimum_required( VERSION 3.19 )

get_current_dir_name( prject_name ${CMAKE_CURRENT_SOURCE_DIR} )
message( "============ ${prject_name}" )
message( "name =" ${prject_name} )
project(
        ${prject_name}
        VERSION 0.1
        LANGUAGES CXX )
message( "============ ${CURRENT_FOLDER}" )

set( cmake_definitions_env_out "${CMAKE_CURRENT_LIST_DIR}/${cmake_auto_sub_dir_name}/macro/cmake_to_c_cpp_header_env.h" )
configure_file( ${cmake_definitions_env_in} ${cmake_definitions_env_out} )

add_library( ${PROJECT_NAME} SHARED )
set( include_path "${CMAKE_CURRENT_LIST_DIR}/srcs" )

string( REPLACE "." "_" project_name_include_dir ${PROJECT_NAME} )
set( ${project_name_include_dir}_include_dir "${include_path}" "${include_path}" PARENT_SCOPE )

set_target_bin_out_path_property( ${PROJECT_NAME} "${Project_Run_Bin_Path}" )
set_target_static_lib_out_path_property( ${PROJECT_NAME} "${Project_Run_Static_Lib_Path}" )
set_target_pdb_out_path_property( ${PROJECT_NAME} "${Project_Run_Pbd_Path}" )

string( SUBSTRING "${PROJECT_NAME}" 0 1 exportFileStartName )
string( SUBSTRING "${PROJECT_NAME}" 1 -1 exportFileName )
string( TOUPPER ${exportFileStartName} exportFileStartName )
set( exportFileName "${CMAKE_CURRENT_SOURCE_DIR}/${cmake_auto_sub_dir_name}/export/${exportFileStartName}${exportFileName}_export.h" )
generate_export_header( ${PROJECT_NAME} EXPORT_FILE_NAME ${exportFileName} )

set_target_link_glew3_lib( ${PROJECT_NAME} )
set_target_link_glfw3_lib( ${PROJECT_NAME} )
set_target_link_glm_lib( ${PROJECT_NAME} )

file( GLOB_RECURSE project_src_file "srcs/*.cpp" "srcs/*.c" "srcs/*.h" )

# 添加源文件
target_sources( ${PROJECT_NAME} PRIVATE ${project_src_file} ${cmake_definitions_env_out} ${exportFileName} ) # 添加源文件

target_include_directories( ${PROJECT_NAME} PUBLIC ${include_path} )
