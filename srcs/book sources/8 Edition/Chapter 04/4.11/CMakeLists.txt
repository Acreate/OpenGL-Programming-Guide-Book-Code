cmake_minimum_required( VERSION 3.19 )

get_absolute_path( absFilePath ${CMAKE_CURRENT_LIST_FILE} )
string_splite( result_list ${absFilePath} ${cmake_sep_char} )
list( GET result_list -3 -2 -1 resultList )
string( JOIN " " jionResult ${resultList} )
normal_project_name( result_name "${jionResult}" )
set( prject_name ${result_name} )
message( "============ ${prject_name}" )
message( "name =" ${prject_name} )
project( ${prject_name} VERSION 0.1 LANGUAGES CXX )
message( "============ ${CURRENT_FOLDER}" )

set( cmake_definitions_env_out "${CMAKE_CURRENT_LIST_DIR}/${cmake_auto_sub_dir_name}/macro/cmake_to_c_cpp_header_env.h" )
configure_file( ${cmake_definitions_env_in} ${cmake_definitions_env_out} )

add_executable( ${PROJECT_NAME} )

set_target_win32_cmd_windows( ${PROJECT_NAME} )
set_target_bin_out_path_property( ${PROJECT_NAME} "${Project_Run_Bin_Path}" )
set_target_static_lib_out_path_property( ${PROJECT_NAME} "${Project_Run_Static_Lib_Path}" )
set_target_pdb_out_path_property( ${PROJECT_NAME} "${Project_Run_Pbd_Path}" )

set_target_link_glew3_lib( ${PROJECT_NAME} )
set_target_link_freeglut3_lib( ${PROJECT_NAME} )

set_target_link_opencv4110_lib( isLoadOpenCV ${PROJECT_NAME} )

if( NOT ${isLoadOpenCV} )
    message( "加载 opencv 失败" )
endif()

target_link_libraries( ${PROJECT_NAME} PUBLIC tools )

get_path_sources( "${CMAKE_CURRENT_LIST_DIR}/srcs/" "c" SRC_C_LIST ) # .c
get_path_sources( "${CMAKE_CURRENT_LIST_DIR}/srcs/" "cpp" SRC_CPP_LIST ) # .cpp
get_path_sources( "${CMAKE_CURRENT_LIST_DIR}/srcs/" "h" HEADER_FILE ) # .h
target_include_directories( ${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/srcs" ) # 加入头文件搜索路径

# 添加源文件
target_sources( ${PROJECT_NAME} PUBLIC ${SRC_C_LIST} ${SRC_CPP_LIST} ${HEADER_FILE} ${cmake_definitions_env_out} )

set( copy_file_target_dir "${Project_Run_Bin_Path}/${PROJECT_NAME}" )
set( copy_file_src_dir "${CMAKE_CURRENT_LIST_DIR}" )
file( COPY "${copy_file_src_dir}/resources" DESTINATION "${copy_file_target_dir}" )
