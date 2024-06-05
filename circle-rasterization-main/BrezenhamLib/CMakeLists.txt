add_library(BrezenhamLib Brezenham.cpp include/Brezenham/Brezenham.hpp)

find_package(OpenCV REQUIRED)

set_property(TARGET BrezenhamLib PROPERTY CXX_STANDARD 20)
target_include_directories(BrezenhamLib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(BrezenhamLib PRIVATE opencv_core opencv_highgui)