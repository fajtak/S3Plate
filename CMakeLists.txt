cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(plates)

find_package(Geant4 REQUIRED)
find_package(ROOT REQUIRED)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${ROOT_INCLUDE_DIRS})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(plates plates.cc ${sources} ${headers})
target_link_libraries(plates ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

install(TARGETS plates DESTINATION bin)
