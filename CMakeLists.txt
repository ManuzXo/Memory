cmake_minimum_required(VERSION 3.13)
project(Memory C)

set(CMAKE_C_STANDARD 11)

# Detect architecture
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_DIR "x64")
else()
    set(ARCH_DIR "x86")
endif()
message(STATUS "Detected architecture: ${ARCH_DIR}")

# Detect OS and set lib folder accordingly
if(WIN32)
    set(LIB_OS_DIR "win")
elseif(UNIX)
    set(LIB_OS_DIR "linux")
else()
    message(FATAL_ERROR "Unsupported operating system")
endif()
message(STATUS "Detected OS folder: ${LIB_OS_DIR}")

# Set include and lib directories
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib/${LIB_OS_DIR}/${ARCH_DIR}")

include_directories("${INCLUDE_DIR}")
link_directories("${LIB_DIR}")

# Source files
file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.c")

add_executable(memory ${SRC_FILES})

# Link libraries
if(WIN32)
    target_link_libraries(memory PRIVATE raylib winmm)
elseif(UNIX)
    target_link_libraries(memory PRIVATE raylib m dl pthread)
endif()

# Output directory setup
get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

if(IS_MULTI_CONFIG)
    set_target_properties(memory PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG       "${CMAKE_SOURCE_DIR}/bin/Debug"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE     "${CMAKE_SOURCE_DIR}/bin/Release"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin/RelWithDebInfo"
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL  "${CMAKE_SOURCE_DIR}/bin/MinSizeRel"
    )
else()
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
    endif()

    set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
    set_target_properties(memory PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
    )
endif()

# Messages
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Include dir: ${INCLUDE_DIR}")
message(STATUS "Library dir: ${LIB_DIR}")
