cmake_minimum_required(VERSION 3.22)
project(TrainSimulator)

set(CMAKE_CXX_STANDARD 23)

# Must set the path to the main.cpp, for example: scripts/main.cpp if it is inside a folder
add_executable(TrainSimulator scripts/simulator.cpp
        scripts/simulator.h
        scripts/main.cpp
        scripts/textDrawer.cpp
        scripts/textDrawer.h
        scripts/structs/vector2.cpp
        scripts/structs/dimensions.cpp
        scripts/structs/object.cpp
        scripts/objectDrawer.h
        scripts/objectDrawer.cpp
        scripts/routes/route.h
        scripts/routes/route.cpp
        scripts/routes/routeTest.h
        scripts/routes/routeTest.cpp)

# --- SDL2 SETUP ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

set(SDL2_PATH "SDL2/x86_64-w64-mingw32")
set(SDL2_TTF_PATH "SDL2/x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "SDL2/x86_64-w64-mingw32")

find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(TrainSimulator ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})