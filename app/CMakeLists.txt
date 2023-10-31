# Any C++ source files needed to build this target (shell-app).
add_executable(tracker
  # list of source cpp files:
  main.cpp
  detector.cpp
  humantracker.cpp
  utils.cpp
  camera.cpp
)

# Any include directories needed to build this target.
# Note: we do not need to specify the include directories for the
# dependent libraries, they are automatically included.

include_directories(tracker
  # list inclue directories:
  ${CMAKE_SOURCE_DIR}/include
  ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(tracker ${OpenCV_LIBS})
