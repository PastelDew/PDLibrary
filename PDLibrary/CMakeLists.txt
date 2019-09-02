add_library(libpdl STATIC MODULE SHARED
    PDCore.h

    ### Algorithm
    Algorithm/sort/SortBase.h

    Algorithm/sort/BubbleSort.h
    Algorithm/sort/BubbleSort.hpp
    

    ### Collection
    Collection/ArrayList.h
    Collection/ArrayList.hpp
    
    Collection/HTNode.h
    Collection/HTNode.hpp
    
    Collection/LinkedList.h
    Collection/LinkedList.hpp

    Collection/Serializable.h
    
    Collection/Serialize.cpp
    Collection/Serialize.h


    ### Debug
    Debug/Debug.h
    Debug/Exception.h

    ### Memory
    Memory/MemoryPool.cpp
    Memory/MemoryPool.h
    Memory/MemoryPool.hpp

    Memory/Ptr.h
    Memory/Ptr.hpp

    Memory/RefCount.cpp
    Memory/RefCount.h
)

if(WIN32)
    ADD_CUSTOM_COMMAND(
        TARGET libpdl
        POST_BUILD
        COMMENT "### Copy include files into ${CMAKE_SOURCE_DIR}/include directory. ###"
        COMMAND echo y|rmdir /s \"${CMAKE_SOURCE_DIR}\\include\\pdl\"
        COMMAND mkdir \"${CMAKE_SOURCE_DIR}\\include\\pdl\"
        COMMAND xcopy /Y \"${CMAKE_SOURCE_DIR}\\PDLibrary\\*.h\" \"${CMAKE_SOURCE_DIR}\\include\\pdl\\*.h\" /e /h /k /q
        COMMAND xcopy /Y \"${CMAKE_SOURCE_DIR}\\PDLibrary\\*.hpp\" \"${CMAKE_SOURCE_DIR}\\include\\pdl\\*.hpp\" /e /h /k /q
        COMMAND echo mkdir \"${CMAKE_SOURCE_DIR}\\bin\"
        COMMAND xcopy /Y \"${CMAKE_SOURCE_DIR}\\build\\PDLibrary\\*.dll\" \"${CMAKE_SOURCE_DIR}\\bin\\*.dll\"
        COMMAND echo \"### COMMAND FINISHED ###\"
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