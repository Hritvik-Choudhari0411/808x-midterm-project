add_library (trackerLib
  # list of cpp source files:
  tracker.cpp
  )

# Indicate what directories should be added to the include file search
# path when using this library.
include_directories(trackerLib PUBLIC
  # list inclue directories:
  ${OpenCV_INCLUDE_DIRS}
)

target_include_directories(trackerLib PUBLIC
  # list of directories:
  .
  ${OpenCV_LIBS}
  )