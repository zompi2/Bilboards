#######################################
# Billboards example CMakeLists file 
# for generating project solutions.
#
# (c) 2020 Damian Nowakowski
#######################################

cmake_minimum_required(VERSION 3.0.0)
project(Billboard VERSION 1.0.0)

# It requires OpenGL
find_package(OpenGL REQUIRED)

# Search for GLFW includes and lib
set (GLFW_INCLUDE_DIR "F:/Code/Externals/GLFW/include" CACHE PATH "Libs")
set (GLFW_LIB "F:/Code/Externals/GLFW/lib/VS2015/glfw3.lib" CACHE FILEPATH "Libs")

# Search for GLEW includes and lib
set (GLEW_INCLUDE_DIR "F:/Code/Externals/GLEW/include" CACHE PATH "Libs")
set (GLEW_LIB "F:/Code/Externals/GLEW/lib/VS2015/glew32.lib" CACHE FILEPATH "Libs")

# Search for DevIL includes and lib
set (DEVIL_INCLUDE_DIR "F:/Code/Externals/DevIL/include" CACHE PATH "Libs")
set (DEVIL_LIB "F:/Code/Externals/DevIL/lib/VS2015/DevIL.lib" CACHE FILEPATH "Libs")

# Search for all sources
set (SRC_FILES Src/Main.cpp)
set (SRC_FILES ${SRC_FILES} 
    Src/Billboard.cpp
    Src/Camera.cpp 
    Src/Engine.cpp
    Src/Scene.cpp
    Src/Shaders.cpp
    Src/Window.cpp)
set (SRC_FILES ${SRC_FILES} 
    ExternalSrc/inih/ini.c 
    ExternalSrc/inih/cpp/INIReader.cpp)

# Search and setup all includes
set (INCLUDE_DIRS ExternalSrc ${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${DEVIL_INCLUDE_DIR})
include_directories (${INCLUDE_DIRS})

# Setup GLFW library
add_library (GlfwLibrary IMPORTED STATIC GLOBAL)
set_target_properties (GlfwLibrary PROPERTIES
    IMPORTED_LOCATION ${GLFW_LIB}
)

# Setup GLEW library
add_library (GlewLibrary IMPORTED STATIC GLOBAL)
set_target_properties (GlewLibrary PROPERTIES
    IMPORTED_LOCATION ${GLEW_LIB}
)

# Setup DEVIL library
add_library (DevILLibrary IMPORTED STATIC GLOBAL)
set_target_properties (DevILLibrary PROPERTIES
    IMPORTED_LOCATION ${DEVIL_LIB}
)

# Setup output path
set (EXECUTABLE_OUTPUT_PATH ../Output)

# Setup executable and link with libraries
add_executable (Billboard ${SRC_FILES})
target_link_libraries (Billboard ${OPENGL_LIBRARIES} GlewLibrary GlfwLibrary DevILLibrary)

