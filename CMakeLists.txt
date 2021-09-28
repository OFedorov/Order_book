cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME
        "order_book"
)

project(${PROJECT_NAME})

set(SOURCES
    main.cpp
    order_book.cpp
    order.cpp
)

set(HEADERS
    order_book.h
    order.h
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
