cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")

project(${MAIN_PROJECT_NAME})
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

###############################################################################

# external dependencies with FetchContent
include(FetchContent)

set(FETCHCONTENT_QUIET OFF CACHE INTERNAL "Override verbose output" FORCE)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE INTERNAL "Override update strategy" FORCE)
#set(SFML_WARNINGS_AS_ERRORS OFF)

# NOTE: Also update env vars used for caching in
#     - .github/actions/configure-cmake/action.yml
#     - .github/workflows/cmake.yml

FetchContent_Declare(
        sqlite3
        URL      https://www.sqlite.org/2026/sqlite-autoconf-3510200.tar.gz
        URL_HASH SHA256=fbd89f866b1403bb66a143065440089dd76100f2238314d92274a082d4f2b7bb
)
FetchContent_GetProperties(sqlite3)
if(NOT sqlite3_POPULATED)
    FetchContent_Populate(sqlite3)
    file(REMOVE ${sqlite3_SOURCE_DIR}/VERSION)
endif()

#FetchContent_Declare(
#        SFML
#        GIT_REPOSITORY https://github.com/SFML/SFML.git
#        GIT_TAG        3.0.2
#        GIT_SHALLOW    1
#        GIT_PROGRESS   ON
#)
#FetchContent_MakeAvailable(SFML)

###############################################################################

# external dependencies with find_package

find_package(Threads REQUIRED)
#if(APPLE)
#elseif(UNIX)
#    find_package(X11)
#endif()

add_library(sqlite3 STATIC ${sqlite3_SOURCE_DIR}/sqlite3.c)
target_include_directories(sqlite3 PUBLIC ${sqlite3_SOURCE_DIR})

###############################################################################

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
add_executable(${MAIN_EXECUTABLE_NAME}
        main.cpp
        ContinutVideo.cpp
        Film.cpp
        Serial.cpp
        Exceptii.cpp
        Watchlist.cpp
        Utilizator.cpp
        PlatformaStreaming.cpp
)

# NOTE: Add all defined targets (e.g. executables, libraries, etc. )
# NOTE: RUN_SANITIZERS is optional, if it's not present it will default to true
set_compiler_flags(RUN_SANITIZERS ${USE_ASAN} TARGET_NAMES ${MAIN_EXECUTABLE_NAME})
# set_compiler_flags(TARGET_NAMES ${MAIN_EXECUTABLE_NAME} ${FOO} ${BAR})
# where ${FOO} and ${BAR} represent additional executables or libraries
# you want to compile with the set compiler flags

###############################################################################

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
target_include_directories(${MAIN_EXECUTABLE_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)
target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE
        ext
)

target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE
        sqlite3
        Threads::Threads
#        SFML::Graphics SFML::Window SFML::System Threads::Threads
)

#if(APPLE)
#elseif(UNIX)
#    target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE X11)
#endif()

# target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ${<SomeLib>_SOURCE_DIR}/include)
# target_link_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${<SomeLib>_BINARY_DIR}/lib)
# target_link_libraries(${MAIN_EXECUTABLE_NAME} <SomeLib>)

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

copy_files(FILES tastatura.txt DIRECTORY assets COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
# copy_files(FILES tastatura.txt config.json DIRECTORY images sounds COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
# copy_files(DIRECTORY images sounds COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})