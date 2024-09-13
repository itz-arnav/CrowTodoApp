cmake_minimum_required(VERSION 3.5)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/Arnav/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(BasicServerWithCrow LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DNOMINMAX)

add_executable(BasicServerWithCrow main.cpp
    include/application.h include/controller.h include/database.h include/model.h
    src/application.cpp src/controller.cpp src/database.cpp src/model.cpp
    include/db_constants.h)

include(GNUInstallDirs)
install(TARGETS BasicServerWithCrow
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

find_package(Boost 1.84.0 REQUIRED COMPONENTS system)
# Find packages
find_package(asio CONFIG REQUIRED)
find_package(Crow CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)


# Link libraries
target_link_libraries(BasicServerWithCrow PRIVATE
    Crow::Crow
    asio::asio
    unofficial::sqlite3::sqlite3
    Ws2_32
    Mswsock
    Boost::boost
    Boost::system
)
