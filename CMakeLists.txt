cmake_minimum_required(VERSION 3.25)
project(Enlightenment)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -Werror")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Configuring for Linux platform")
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        message(STATUS "Targeting 64-bit Linux")

        find_package(PkgConfig REQUIRED)
        pkg_check_modules(GTK REQUIRED gtk+-3.0)

        include_directories(${GTK_INCLUDE_DIRS})
        link_directories(${GTK_LIBRARY_DIRS})
        add_definitions(${GTK_CFLAGS_OTHER})

        set(LINUX_X64_LIBS ${GTK_LIBRARIES})
    endif()
endif()

add_executable(Enlightenment
        zclient/main.c
        zclient/app/core.h
        zclient/app/window.h
        zclient/app/event.h
        zclient/app/linux-x64/window.c
)

target_include_directories(Enlightenment PRIVATE zclient)

if(LINUX_X64_LIBS)
    target_link_libraries(Enlightenment ${LINUX_X64_LIBS})
endif()