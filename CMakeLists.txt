cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)

include(FetchContent)
project(DownDownWeGo VERSION 1.0.0 LANGUAGES CXX)

if(WIN32)
  # SonarLint support for CMake requires the following flag to be set on.
  #(see https://community.sonarsource.com/t/sonarlint-for-visual-studio-v4-38-support-cmake-projects/50127)
  set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

set (BUILD_SHARED_LIBS FALSE)

if(APPLE)
  find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
  include_directories(${SFML_INCLUDE_DIRS})
else()
  # Linux or Windows
  FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
  )

  FetchContent_MakeAvailable(sfml)
endif()

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
