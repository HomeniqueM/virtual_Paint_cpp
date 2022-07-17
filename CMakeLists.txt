
cmake_minimum_required(VERSION 3.12)
project( vitualpaint.out )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
file(GLOB VITUAL_PAINT_SRC CONFIGURE_DEPENDS src/*.cpp )
add_executable( vitualpaint.out ${VITUAL_PAINT_SRC} )
target_link_libraries( vitualpaint.out ${OpenCV_LIBS} )
