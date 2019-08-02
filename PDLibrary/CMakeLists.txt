add_library(libpdl STATIC MODULE SHARED
    PDCore.h

    ### Algorithm
    # Algorithm/
    

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
        COMMENT "Copy include files into ${CMAKE_SOURCE_DIR}/include directory."
        COMMAND echo y|rmdir /s \"${CMAKE_SOURCE_DIR}\\include\\pdl\"
        COMMAND mkdir \"${CMAKE_SOURCE_DIR}\\include\\pdl\"
        COMMAND xcopy /Y \"${CMAKE_SOURCE_DIR}\\PDLibrary\\*.h" "${CMAKE_SOURCE_DIR}\\include\\pdl\\*.h\" /e /h /k /q
        COMMAND xcopy /Y \"${CMAKE_SOURCE_DIR}\\PDLibrary\\*.hpp" "${CMAKE_SOURCE_DIR}\\include\\pdl\\*.hpp\" /e /h /k /q
        COMMAND echo mkdir \"${CMAKE_SOURCE_DIR}\\bin\"
        COMMAND xcopy /Y \"${CMAKE_SOURCE_DIR}\\build\\PDLibrary\\*.dll\" \"${CMAKE_SOURCE_DIR}\\bin\\*.dll\"
    )
elseif(APPLE)
elseif(UNIX)
    if(${CMAKE_SYSTEM} MATCHES Linux)
    endif()
else()
    if(ANDROID OR IOS)
        message(FATAL_ERROR "No implementation for the platform")
    endif()
endif()