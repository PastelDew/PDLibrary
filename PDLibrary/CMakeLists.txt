add_library(libpdl STATIC MODULE SHARED
    PDCore.h

    ### Core
    Core/Random.h
    Core/Random.cpp

    ### Collection
    Collection/ArrayList.h
    Collection/ArrayList.hpp
    
    Collection/HTNode.h
    Collection/HTNode.hpp
    
    Collection/LinkedList.h
    Collection/LinkedList.hpp

    Collection/Serializable.h
    
    Collection/Serialize.h
    Collection/Serialize.cpp


    ### Debug
    Debug/Debug.h
    Debug/Exception.h

    ### Memory
    Memory/MemoryPool.h
    Memory/MemoryPool.hpp
    Memory/MemoryPool.cpp

    Memory/Ptr.h
    Memory/Ptr.hpp

    Memory/RefCount.h
    Memory/RefCount.cpp

    ### libs
    libs/WELL/WELL512a.h
    libs/WELL/WELL512a.cpp
    libs/WELL/WELL1024a.h
    libs/WELL/WELL1024a.cpp
    libs/WELL/WELL19937a.h
    libs/WELL/WELL19937a.cpp
    libs/WELL/WELL44497a.h
    libs/WELL/WELL44497a.cpp
)

if(WIN32)
    ADD_CUSTOM_COMMAND(
        TARGET libpdl
        PRE_BUILD
        COMMENT "### Remove include files in ${CMAKE_SOURCE_DIR}/include directory. ###"
        COMMAND echo \"${CMAKE_SOURCE_DIR}\\include\\pdl\"
        COMMAND if exist \"${CMAKE_SOURCE_DIR}\\include\\pdl\" (echo y|rmdir /s \"${CMAKE_SOURCE_DIR}\\include\\pdl\") else (echo \"Skip rmdir\")
        COMMAND echo \"\#\#\# -remove- phase finished \#\#\#\"
    )
    ADD_CUSTOM_COMMAND(
        TARGET libpdl
        POST_BUILD
        COMMENT "### Copy include files into ${CMAKE_SOURCE_DIR}/include directory. ###"
        COMMAND mkdir \"${CMAKE_SOURCE_DIR}\\include\\pdl\"
        COMMAND xcopy /Y \"${CMAKE_SOURCE_DIR}\\PDLibrary\\*.h\" \"${CMAKE_SOURCE_DIR}\\include\\pdl\\*.h\" /e /h /k /q
        COMMAND xcopy /Y \"${CMAKE_SOURCE_DIR}\\PDLibrary\\*.hpp\" \"${CMAKE_SOURCE_DIR}\\include\\pdl\\*.hpp\" /e /h /k /q
        COMMAND echo mkdir \"${CMAKE_SOURCE_DIR}\\bin\"
        COMMAND xcopy /Y \"${CMAKE_SOURCE_DIR}\\build\\PDLibrary\\*.dll\" \"${CMAKE_SOURCE_DIR}\\bin\\*.dll\"
        COMMAND xcopy /Y \"${CMAKE_SOURCE_DIR}\\build\\PDLibrary\\*.lib\" \"${CMAKE_SOURCE_DIR}\\bin\\*.lib\"
        COMMAND echo \"\#\#\# -include- phase finished \#\#\#\"
    )
elseif(APPLE)
elseif(UNIX)
    if(${CMAKE_SYSTEM} MATCHES Linux)
        ADD_CUSTOM_COMMAND(
            TARGET libpdl
            POST_BUILD
            COMMENT "### Copy include files into ${CMAKE_SOURCE_DIR}/include directory. ###"
            COMMAND echo rm \"${CMAKE_SOURCE_DIR}/include/pdl\" -r
            COMMAND mkdir \"${CMAKE_SOURCE_DIR}/include/pdl\" -p
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/PDLibrary/
            COMMAND find . -type f -name \"*.h\" | cpio -pdm \"${CMAKE_SOURCE_DIR}/include/pdl/\"
            COMMAND find . -type f -name \"*.hpp\" | cpio -pdm \"${CMAKE_SOURCE_DIR}/include/pdl/\"
            COMMAND echo \"\#\#\# -include- phase finished \#\#\#\"
        )
        ADD_CUSTOM_COMMAND(
            TARGET libpdl
            POST_BUILD
            COMMENT "### Copy binary files into ${CMAKE_SOURCE_DIR}/bin directory. ###"
            COMMAND mkdir \"${CMAKE_SOURCE_DIR}/bin\" -p
            COMMAND find . -type f -name \"*.so\" -exec cp \"${CMAKE_SOURCE_DIR}/bin/\" {} "\;"
            COMMAND echo \"\#\#\# -bin- phase finished \#\#\#\"
        )
    endif()
else()
    if(ANDROID OR IOS)
        message(FATAL_ERROR "No implementation for the platform")
    endif()
endif()