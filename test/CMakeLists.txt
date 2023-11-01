# Any C++ source files needed to build this target (cpp-test).
add_executable(tracker-test
  # list of source cpp files:
  main.cpp
  test.cpp
  )

# Any include directories needed to build this target.
# Note: we do not need to specify the include directories for the
# dependent libraries, they are automatically included.
include_directories(tracker-test
  # list inclue directories:
  ${CMAKE_SOURCE_DIR}/include
  ${OpenCV_INCLUDE_DIRS}
)

target_include_directories(tracker-test PUBLIC
  # list inclue directories:
  ${CMAKE_SOURCE_DIR}/include
)
# Any dependent libraires needed to build this target.
target_link_libraries(tracker-test PUBLIC
  # list of libraries:
  gtest
  ${OpenCV_LIBS}
  trackerLib
  )

# Enable CMake’s test runner to discover the tests included in the
# binary, using the GoogleTest CMake module.
gtest_discover_tests(tracker-test)
