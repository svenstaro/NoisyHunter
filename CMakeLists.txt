cmake_minimum_required(VERSION 2.8.0)

project(NoisyHunter)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-extras/")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

find_package(SFML REQUIRED)
find_package(Bullet REQUIRED)
find_package(Boost COMPONENTS filesystem program_options system python date_time REQUIRED)
find_package(ImageMagick COMPONENTS Magick++ REQUIRED)

add_definitions(-Wall -Wextra -pedantic)
set(CMAKE_BUILD_TYPE "Debug")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(
	"${CMAKE_SOURCE_DIR}/engine/src/"
	${Boost_INCLUDE_DIRS}
	${SFML_INCLUDE_DIRS}
	${BULLET_INCLUDE_DIRS}
	${ImageMagick_INCLUDE_DIRS}
)

add_subdirectory("${CMAKE_SOURCE_DIR}/engine/")
add_subdirectory("${CMAKE_SOURCE_DIR}/game/")
