add_executable(test_exe
    main.cpp


    ### Test Sources
    #include/TestArrayList.h
    #TestSources/TestBase.h
    #TestSources/TestIncludes.h
    #TestSources/TestLinkedList.h
    #TestSources/TestMemoryPool.h
)

target_link_libraries(test_exe
    PRIVATE
        libpdl
)


if(WIN32)
    ADD_CUSTOM_COMMAND(
        TARGET test_exe
        POST_BUILD
        COMMAND echo mkdir \"${CMAKE_SOURCE_DIR}\\bin\"
        COMMAND echo F|xcopy /Y \"${CMAKE_SOURCE_DIR}\\build\\test\\test_exe.exe\" \"${CMAKE_SOURCE_DIR}\\bin\\test.exe\"
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