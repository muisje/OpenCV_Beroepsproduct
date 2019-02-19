cmake_minimum_required(VERSION 2.8)
project( Beroepsproduct )
file(GLOB SOURCES
        include/*.h
        src/*.cpp
)
find_package( OpenCV 3.2.0 REQUIRED )
add_executable( Beroepsproduct main.cpp ${SOURCES} )
target_link_libraries( Beroepsproduct ${OpenCV_LIBS} )

