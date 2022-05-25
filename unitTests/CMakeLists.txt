enable_testing()
add_executable(unitTests unitTests.cpp)
target_link_libraries(unitTests gtest_main)
add_test(unitTests unitTests)
