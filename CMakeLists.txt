cmake_minimum_required(VERSION 3.19)

project(peradventure VERSION 0.0.1)

FIND_PACKAGE(Boost COMPONENTS filesystem date_time system regex serialization thread REQUIRED)

set(H_DIR Header_files)
set(SRC_DIR Source_files)

set(target_server ${PROJECT_NAME}_server)
set(target_client ${PROJECT_NAME}_client)

add_executable(${target_server}
    main.cpp

    ${H_DIR}/client_session.h
    ${H_DIR}/coroutine.hpp
    ${H_DIR}/globals.h
    ${H_DIR}/includes.h
    ${H_DIR}/server.h
    ${H_DIR}/yield.hpp

    ${SRC_DIR}/client_session.cpp
    ${SRC_DIR}/globals.cpp
    ${SRC_DIR}/server.cpp
)

add_executable(${target_client}
    async_client.cpp
    ${H_DIR}/coroutine.hpp
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
target_link_libraries(${target_client} PRIVATE ${LIBS})

set_target_properties(${target_server}
    PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
)

set_target_properties(${target_client}
    PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(${target_server}
    PRIVATE
        ${H_DIR}
        ${SRC_DIR}
)

target_include_directories(${target_client}
    PRIVATE
        ${H_DIR}
        ${SRC_DIR}
)
