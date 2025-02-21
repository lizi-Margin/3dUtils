
# if(MSVC)
#      set(CMAKE_GENERATOR_TOOLSET "v120" CACHE STRING "Platform Toolset" FORCE)
#      # 确保使用静态链接的运行时库
#      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
# else()
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# endif()


include_directories(external/Eigen)
add_subdirectory(external/pybind11)

add_executable (test "test.cpp"    "vector.h" "funcs.h" "c3utils.h" "def.h" "io.h")



function(setup_pybind_proj pybind_proj_name conda_env_path conda_env_python_version)
    set(Python3_EXECUTABLE "${conda_env_path}/python.exe")
	set(Python3_INCLUDE_DIR "${conda_env_path}/include")
	set(Python3_LIBRARY "${conda_env_path}/libs/python${conda_env_python_version}.lib")
	find_package(Python3 REQUIRED   COMPONENTS Interpreter Development)

	set(pybind_proj_name_ "${pybind_proj_name}.cp${conda_env_python_version}-win_amd64")
	pybind11_add_module(${pybind_proj_name_} PyInterface.cpp)
	target_include_directories(${pybind_proj_name_} PRIVATE ${Python3_INCLUDE_DIRS})
	target_link_libraries(${pybind_proj_name_} PRIVATE ${Python3_LIBRARIES})
	
	set_target_properties(${pybind_proj_name_} PROPERTIES
		PREFIX ""  
		SUFFIX ".pyd"      
		LINKER_LANGUAGE CXX  
	)
endfunction()

setup_pybind_proj("py_c3utils" "G:/.conda/envs/hmp" "37")
setup_pybind_proj("py_c3utils" "C:/Users/hulc/scoop/apps/miniconda3/current" "312")
