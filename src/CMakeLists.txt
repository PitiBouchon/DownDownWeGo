file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp Tile/*.h Tile/*.cpp)

add_executable(src ${SOURCES} "gameManager.h" "uiManager.h" "uiManager.cpp")

target_link_libraries(src PUBLIC fmt box2d sfml-graphics sfml-audio tmxlite)

add_custom_target(copy-resources ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/resources)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources
                   DEPENDS ${CMAKE_SOURCE_DIR}/resources ${CMAKE_SOURCE_DIR}/resources/maps ${CMAKE_SOURCE_DIR}/resources/tiles
                   COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/resources
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources)

add_dependencies(src copy-resources)

target_include_directories(src PUBLIC Tile)
