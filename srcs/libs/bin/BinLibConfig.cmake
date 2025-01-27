cmake_minimum_required( VERSION 3.19 )

# ## 配置指定目标的 soil2
function( set_target_link_glm_lib target_obj )
    target_include_directories( ${target_obj} PUBLIC "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/glm-1.0.1-light" )
endfunction()

# ## 配置指定目标的 soil2
function( set_target_link_soil2_lib target_obj )
    target_include_directories( ${target_obj} PUBLIC "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/SOIL2-1.3.0/src/" )
    target_link_libraries( ${target_obj} PUBLIC
        $<$<CONFIG:Release>:"${CMAKE_CURRENT_FUNCTION_LIST_DIR}/SOIL2-1.3.0//lib/windows/soil2">
        $<$<CONFIG:Debug>:"${CMAKE_CURRENT_FUNCTION_LIST_DIR}/SOIL2-1.3.0//lib/windows/soil2-debug"> )
endfunction()

# ## 配置指定目标的 glew3
function( set_target_link_glew3_lib target_obj )
    target_link_libraries( ${target_obj} PUBLIC
        "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/glew-2.2.0/lib/Release/x64/glew32.lib"
        "opengl32.lib" )
    target_include_directories( ${target_obj} PUBLIC
        "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/glew-2.2.0/include" )

    if( WIN32 )
        get_target_property( run_path ${target_obj} RUNTIME_OUTPUT_DIRECTORY )
        get_target_property( name ${target_obj} ARCHIVE_OUTPUT_NAME )
        message( "\t\t发现动态库目标路径 : " ${run_path} )
        set( dll_base_name "glew32.dll" )
        set( glew32_dll_file_path "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/glew-2.2.0/bin/Release/x64/${dll_base_name}" )
        execute_process( COMMAND ${CMAKE_COMMAND} -E make_directory ${run_path} )
        file( COPY_FILE "${glew32_dll_file_path}" "${run_path}/${dll_base_name}" )
    endif()
endfunction()

# ## 配置指定目标的 glfw3
function( set_target_link_glfw3_lib target_obj )
    target_include_directories( ${target_obj} PUBLIC
        "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/glfw-3.4.bin.WIN64/include" )
    target_link_libraries( ${target_obj} PUBLIC
        "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/glfw-3.4.bin.WIN64/lib-vc2022/glfw3.lib"
        "opengl32.lib" )
endfunction()

# ## 配置指定目标的 glut3
function( set_target_link_freeglut3_lib target_obj )
    set( root_path "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/freeglut-3.6.0/x64" )

    set( lib_base_name "freeglutd.lib" )
    target_link_libraries( ${target_obj} PUBLIC
            "${root_path}/lib/${lib_base_name}" )

    target_include_directories( ${target_obj} PUBLIC
        "${root_path}/include" )

    if( WIN32 )
        get_target_property( run_path ${target_obj} RUNTIME_OUTPUT_DIRECTORY )
        get_target_property( name ${target_obj} ARCHIVE_OUTPUT_NAME )
        message( "\t\t发现动态库目标路径 : " ${run_path} )
        set( dll_base_name "freeglutd.dll" )
        set( freeglut3_dll_file_path "${root_path}/bin/${dll_base_name}" )
        execute_process( COMMAND ${CMAKE_COMMAND} -E make_directory ${run_path} )
        file( COPY_FILE "${freeglut3_dll_file_path}" "${run_path}/${dll_base_name}" )
    endif()
endfunction()
