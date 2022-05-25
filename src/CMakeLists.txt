file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_executable(src
  ${SOURCES}
  )

target_link_libraries(src PUBLIC sfml-graphics)

add_custom_target(copy-resources ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/resources)
# "COMMAND ${CMAKE_COMMAND} -E copy_directory" triggers a generation error with Visual Studio
# So we need to do  the following solution
file(GLOB RESOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/resources/*.*)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources
                   DEPENDS ${CMAKE_SOURCE_DIR}/resources
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/resources
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           ${RESOURCES}
                           ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_dependencies(src copy-resources)