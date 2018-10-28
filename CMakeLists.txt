cmake_minimum_required(VERSION 3.2)
#project name
PROJECT(wrtool)

ADD_DEFINITIONS(-DCMAKE_BUILD_TYPE=Debug)
#head file path
INCLUDE_DIRECTORIES(
include
)
#source directory
AUX_SOURCE_DIRECTORY(source/string LIB_SRCS)
#AUX_SOURCE_DIRECTORY(test TEST_SRCS)
set(TEST_SRCS test)

#set environment variable
SET(TEST_SPLIT
    ${LIB_SRCS} 
    ${TEST_SRCS}/split_test.cpp
)

SET(TEST_HASH
    ${TEST_SRCS}/consistent_hash_test.cpp
)

#set extern libraries
#SET(LIBRARIES
#libm.so
#)
#add executable file
ADD_EXECUTABLE(split_test ${TEST_SPLIT})
ADD_EXECUTABLE(consis_hash_test ${TEST_HASH})

target_compile_features(split_test PUBLIC cxx_std_11)
target_compile_features(consis_hash_test PUBLIC cxx_std_11)

#add link library
#TARGET_LINK_LIBRARIES(../bin/bin ${LIBRARIES})
