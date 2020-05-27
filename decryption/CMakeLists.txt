cmake_minimum_required(VERSION 2.8)
PROJECT(decryption)
set( CMAKE_CXX_FLAGS "-std=c++11" )

MESSAGE(STATUS "Project: SERVER")
MESSAGE( STATUS "${PROJECT_SOURCE_DIR}")
include_directories(
${PROJECT_SOURCE_DIR}/include
)

set(SRC ${PROJECT_SOURCE_DIR}/src/caesar_cipher.cpp ${PROJECT_SOURCE_DIR}/src/des_cipher.cpp ${PROJECT_SOURCE_DIR}/src/des_text_cipher.cpp ${PROJECT_SOURCE_DIR}/src/main.cpp ${PROJECT_SOURCE_DIR}/src/play_fair.cpp ${PROJECT_SOURCE_DIR}/src/rc4_cipher.cpp ${PROJECT_SOURCE_DIR}/src/rsa_cipher.cpp)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(LIB_NAME decryption_lib)
add_library(${LIB_NAME} STATIC ${SRC})
MESSAGE( STATUS "${SRC}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${LIB_NAME})
