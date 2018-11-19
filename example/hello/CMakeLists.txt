cmake_minimum_required(VERSION 3.0.0)
project(hello VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

include(FindPkgConfig)

pkg_check_modules(GLFW REQUIRED glfw3)
pkg_check_modules(GL REQUIRED gl)

include_directories(include)
add_executable(hello src/main.cpp)

target_include_directories(hello SYSTEM PUBLIC ${GLFW_INCLUDE_DIRS})
target_link_libraries(hello ${GLFW_LIBRARIES} ${GL_LIBRARIES})
