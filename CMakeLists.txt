cmake_minimum_required(VERSION 3.15)
project(DoodleParody LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_GetProperties(SFML)
if(NOT SFML_POPULATED)
  FetchContent_Populate(SFML)
  add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.hpp)

add_executable(DoodleParody ${SOURCE_FILES})
target_link_libraries(DoodleParody PRIVATE sfml-graphics)
target_compile_features(DoodleParody PRIVATE cxx_std_17)
target_include_directories(DoodleParody PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

install(TARGETS DoodleParody DESTINATION .)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/bin/res DESTINATION .)