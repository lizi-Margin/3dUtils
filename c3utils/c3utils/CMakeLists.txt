include_directories(external/Eigen)
add_subdirectory(external/pybind11)

# add_executable (c3utils "c3utils.cpp"   "Vector2.h" "Vector3.h" "Funcs.h" "c3utils.h" "Def.h" "PyInterface.cpp" "CInterface.cpp")
# if (CMAKE_VERSION VERSION_GREATER 3.12)
#   set_property(TARGET c3utils PROPERTY CXX_STANDARD 20)
# endif()

set(Python3_EXECUTABLE "C:/Users/33149/scoop/apps/miniconda3/24.4.0-0/envs/HDB01/python.exe")
set(Python3_INCLUDE_DIR "C:/Users/33149/scoop/apps/miniconda3/24.4.0-0/envs/HDB01/include")
set(Python3_LIBRARY "C:/Users/33149/scoop/apps/miniconda3/24.4.0-0/envs/HDB01/libs/python37.lib")
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

pybind11_add_module(py_c3utils PyInterface.cpp)
target_include_directories(py_c3utils PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_LIBRARIES})
target_link_libraries(py_c3utils PRIVATE ${Python3_LIBRARIES})

set_target_properties(py_c3utils PROPERTIES
    PREFIX ""  
    SUFFIX ".pyd"      
    LINKER_LANGUAGE CXX  
)
