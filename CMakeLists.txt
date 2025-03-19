cmake_minimum_required(VERSION 3.10)

project(
	detectra-simulation
	VERSION 1.0
	LANGUAGES CXX)

set(CMAKE_CXX_STANDDARD 20)
set(CMAKE_CXX_STANDDARD_REQUIRED ON)

# for the ide
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src)

file(GLOB src
     "src/*.h"
     "src/*.cpp"
)
add_executable(${PROJECT_NAME} ${src})

find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network)
target_link_libraries(${PROJECT_NAME} SFML::Graphics SFML::Audio SFML::Network)
