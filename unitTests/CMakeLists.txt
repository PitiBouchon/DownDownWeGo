enable_testing()
file(GLOB SOURCES CONFIGURE_DEPENDS unitTests.cpp ../src/*.h ../src/rigidbody.cpp ../src/camera.cpp ../src/Tile/*.h ../src/Tile/*.cpp)

add_executable(unitTests ${SOURCES} unitTests.cpp)
target_link_libraries(unitTests gtest_main fmt box2d sfml-graphics sfml-audio tmxlite)
add_test(unitTests unitTests)
