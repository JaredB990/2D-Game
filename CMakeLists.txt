cmake_minimum_required(VERSION 3.16)
project(hello)

include(FetchContent)

FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	0af55ccecd98d4e5a8d1fad7de25ba429d60e863 #refs/tags/1.0.1
)

FetchContent_MakeAvailable(glm)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)

# Create your game executable target as usual
# MAKE SURE TO ADD ALL OF YOUR CPP FILES
# Normally, we would probably create a source directory, but for this
# project just put your .h and .cpp files in the current dir.
add_executable(Galaga Galaga.cpp game_objects.cpp components.cpp engine.cpp player_ship.cpp UtilityFunctions.cpp)

# Link to the actual SDL3 library.
target_link_libraries(Galaga PRIVATE SDL3_image::SDL3_image SDL3::SDL3 glm::glm )
