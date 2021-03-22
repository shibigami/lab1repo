cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")
# Maths lib
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths" SYSTEM INTERFACE ${SFML_INCS})
## Tile loader lib
file(GLOB_RECURSE SOURCE_FILES lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/lib_tile_level_loader/" )
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)
## ECM
file(GLOB_RECURSE SOURCE_FILES lib_ecm/*.cpp lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/lib_ecm")
target_link_libraries(lib_ecm lib_maths)
# B2D - Box2D phyics library
add_subdirectory("lib/b2d/Box2D")
#include_directories("lib/b2d/Box2D/")
set(B2D_INCS "lib/b2d/Box2D/")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

#### Practical 1 ####
file(GLOB_RECURSE SOURCES practical_1/*.cpp practical_1/*.h)
add_executable(PRACTICAL_1 ${SOURCES})
target_include_directories(PRACTICAL_1 PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_1 sfml-graphics)

## Space invaders
file(GLOB_RECURSE SOURCES SpaceInvadeUs/*.cpp SpaceInvadeUs/*.h)
add_executable(SpaceInvadeUs ${SOURCES} )
target_include_directories(SpaceInvadeUs SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(SpaceInvadeUs sfml-graphics)

## Tile engine
file(GLOB_RECURSE SOURCES TileEngine/*.cpp TileEngine/*.h)
add_executable(TileEngine ${SOURCES} )
target_include_directories(TileEngine SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(TileEngine lib_tile_level_loader sfml-graphics)

## Pacman
file(GLOB_RECURSE SOURCES Pacman/*.cpp Pacman/*.h)
add_executable(Pacman ${SOURCES} )
target_include_directories(Pacman SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(Pacman sfml-graphics lib_tile_level_loader lib_ecm)

## Physics
file(GLOB_RECURSE SOURCES Physics/*.cpp Physics/*.h)
add_executable(Physics ${SOURCES} )
target_include_directories(Physics SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
target_link_libraries(Physics Box2D sfml-graphics)
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_PHYSICS)