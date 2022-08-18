cmake_minimum_required(VERSION 3.0.0)
project(type-analyzer VERSION 0.1.0)

include(CTest)
enable_testing()

set (CMAKE_CXX_STANDARD 20)

file(GLOB main_SRC "*.h" "*.cpp")

add_executable(type-analyzer ${main_SRC})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
include(FetchContent)

FetchContent_Declare(matplotplusplus
  GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
  GIT_TAG origin/master)

FetchContent_GetProperties(matplotplusplus)
if(NOT matplotplusplus_POPULATED)
    FetchContent_Populate(matplotplusplus)
    add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(type-analyzer PUBLIC matplot)
