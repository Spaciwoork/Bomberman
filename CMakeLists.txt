cmake_minimum_required(VERSION 3.10)
project(cpp_indie_studio)

set(CMAKE_CXX_STANDARD 17)

include_directories(includes)
include_directories(includes/IObject)
IF(WIN32)
  include_directories(includes/Windows)
ENDIF()

file(STRINGS includes.mk INCLUDE_FILES)
file(STRINGS sources.mk SOURCE_FILES)

IF(UNIX)
    add_compile_options(-W -Wall)
ENDIF()

add_executable(bomberman ${SOURCE_FILES} ${INCLUDE_FILES})

find_library(
        IRRLICHT
        Irrlicht
        PATHS
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
        /usr/lib64
)
find_library(
        IRRKLANG
        IrrKlang
        PATHS
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
        /usr/lib64
)
target_link_libraries(bomberman ${IRRLICHT} ${IRRKLANG})

install(TARGETS bomberman
        RUNTIME DESTINATION bin)
install(DIRECTORY media DESTINATION bin)
install(DIRECTORY Blocs DESTINATION bin)