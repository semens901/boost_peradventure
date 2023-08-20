 cmake_minimum_required(VERSION 3.19)

project(peradventure VERSION 0.0.1)

FIND_PACKAGE(Boost COMPONENTS filesystem date_time system regex serialization thread REQUIRED)

set(SRC src)

set(target_server ${PROJECT_NAME}_server)

add_executable(${target_server}
    ${SRC}/main.cpp

    ${SRC}/client_session.h
    ${SRC}/coroutine.hpp
    ${SRC}/globals.h
    ${SRC}/includes.h
    ${SRC}/server.h
    ${SRC}/yield.hpp

    ${SRC}/client_session.cpp
    ${SRC}/globals.cpp
    ${SRC}/server.cpp
)

set(LIBS
    Boost::filesystem
    Boost::date_time
    Boost::system
    Boost::regex
    Boost::serialization
    Boost::thread
    pthread
)

target_link_libraries(${target_server} PRIVATE ${LIBS})

set_target_properties(${target_server}
    PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(${target_server}
    PRIVATE
        ${SRC}
)
