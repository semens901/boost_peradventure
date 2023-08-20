 cmake_minimum_required(VERSION 3.19)

project(peradventure VERSION 0.0.1)

FIND_PACKAGE(Boost COMPONENTS filesystem date_time system regex serialization thread REQUIRED)

set(SRC src)

set(target_client ${PROJECT_NAME}_client)

add_executable(${target_client}
    ${SRC}/coroutine.hpp
    ${SRC}/yield.hpp
    ${SRC}/async_client.cpp
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

target_link_libraries(${target_client} PRIVATE ${LIBS})

set_target_properties(${target_client}
    PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(${target_client}
    PRIVATE
        ${H_DIR}
        ${SRC_DIR}
)
