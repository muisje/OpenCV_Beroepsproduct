cmake_minimum_required(VERSION 2.8)
project( Beroepsproduct )
set(CMAKE_CXX_CPPCHECK "cppcheck")

file(GLOB SOURCES
        include/*.h
        src/*.cpp
)
find_package( OpenCV 3.2.0  REQUIRED )
find_package( Threads  REQUIRED )
add_executable( Beroepsproduct main.cpp ${SOURCES} )
target_link_libraries( Beroepsproduct ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})
if ( CMAKE_COMPILER_IS_GNUCC )
    target_compile_options(Beroepsproduct PRIVATE "-Wall")
    target_compile_options(Beroepsproduct PRIVATE "-Wextra")
    target_compile_options(Beroepsproduct PRIVATE "-Wconversion")
endif()
if ( MSVC )
    target_compile_options(Beroepsproduct PRIVATE "/W4")
endif()
