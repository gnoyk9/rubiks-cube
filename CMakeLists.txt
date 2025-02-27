cmake_minimum_required(VERSION 3.10)
project(RubiksCube)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define source and header directories
set(SRC_DIR "src")
set(INCLUDE_DIR "include")

set(SFML_STATIC_LIBRARIES TRUE)

# Add the executable
add_executable(RubiksCube
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/Cube.cpp
)

set(SFML_DIR "/opt/SFML/lib64/cmake/SFML")
find_package(SFML 3.1 COMPONENTS Graphics Window System REQUIRED)
# Link SFML static libraries by specifying their full paths
target_link_libraries(RubiksCube PRIVATE SFML::Graphics SFML::Window SFML::System)
#target_link_libraries(RubiksCube 
#    /opt/SFML/lib64/libsfml-graphics-s.a
#    /opt/SFML/lib64/libsfml-window-s.a
#    /opt/SFML/lib64/libsfml-system-s.a
#)

#target_link_libraries(RubiksCube sfml-graphics-s.a sfml-window-s.a sfml-system-s.a)

# Include the headers
target_include_directories(RubiksCube PRIVATE ${INCLUDE_DIR})

# Set output directory
set_target_properties(RubiksCube PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin")