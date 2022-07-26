cmake_minimum_required(VERSION 3.0.0)

project(ConcurrencyTests)

file(GLOB_RECURSE SOURCE Classes/*.cpp)
file(GLOB_RECURSE HEADER Classes/*.h)

add_definitions (-D__X86_X64__ FALSE)
add_definitions (-D__ARM__ FALSE)


if (CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
    set (__X86_X64__ TRUE)
elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")
	set(__ARM__ TRUE)
endif ()

message (STATUS ${CMAKE_SYSTEM_PROCESSOR})

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADER})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)