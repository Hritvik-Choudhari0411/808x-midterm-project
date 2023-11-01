# Any C++ source files needed to build this target (shell-app).
add_executable(tracker
  # list of source cpp files:
  main.cpp
)

# Any include directories needed to build this target.
# Note: we do not need to specify the include directories for the
# dependent libraries, they are automatically included.

include_directories(tracker
  # list inclue directories:
  ${CMAKE_SOURCE_DIR}/include
  ${OpenCV_INCLUDE_DIRS}
)



target_include_directories(tracker PUBLIC
  # list inclue directories:
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(tracker 
  ${OpenCV_LIBS}
  trackerLib
)
