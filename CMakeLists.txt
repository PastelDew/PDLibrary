cmake_minimum_required(VERSION 3.0)
project(PDLibrary
    VERSION 0.1.1
    LANGUAGES C CXX
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(PDLibrary)
add_subdirectory(Test)
add_dependencies(test_exe   libpdl)

message(STATUS "Compiler")
message(STATUS " - ID       \t: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS " - Version  \t: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS " - Path     \t: ${CMAKE_CXX_COMPILER}")

#if(MSVC)        # Microsoft Visual C++ Compiler
    # ...
#elseif(${CMAKE_CXX_COMPILER_ID} MATCHES Clang)  # Clang + AppleClang
    # ...
#elseif(${CMAKE_CXX_COMPILER_ID} MATCHES GNU)    # GNU C Compiler
    # ...
#endif()

target_compile_definitions(libpdl
    PRIVATE
        PDL_DLL_EXPORTS
)

target_include_directories(test_exe
    PRIVATE
        include
)

if(WIN32)
    if( MINGW )
        message(FATAL_ERROR "Not supported compiler")
    endif()
elseif(APPLE)
    # additional implementation for MacOS
elseif(UNIX)
    # additional implementation with Linux API
    if(${CMAKE_SYSTEM} MATCHES Linux)
        # ...
    endif()
else()
    # 지원하지 않음.
    # android.toolchain.cmake 혹은 ios.toolchain.cmake 에서 지정하는 변수들
    if(ANDROID OR IOS)
        message(FATAL_ERROR "No implementation for the platform")
    endif()
    # ...
endif()