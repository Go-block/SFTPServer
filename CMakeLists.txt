cmake_minimum_required(VERSION 3.10)
project(SFTPServer)

set(CMAKE_CXX_STANDARD 17)

# Temukan libssh
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBSSH REQUIRED libssh)

# Tambahkan jalur include untuk libssh dan header lokal
include_directories(${LIBSSH_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)

# Tambahkan file sumber
add_executable(SFTPServer
    src/main.cpp
    src/SFTPServer.cpp
    src/SessionHandler.cpp
    src/FileManager.cpp
)

# Tambahkan pustaka libssh
target_link_libraries(SFTPServer ${LIBSSH_LIBRARIES})
