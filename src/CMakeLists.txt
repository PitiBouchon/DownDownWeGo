file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_executable(src
  ${SOURCES}
  )

target_link_libraries(src PUBLIC sfml-graphics)
