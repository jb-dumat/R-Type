cmake_minimum_required(VERSION 3.9)
project(rtype)
set(VERSION "1.0.0")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BINARY_DIR build)  #[[Overwriting intelliJ IDEA default path and cie.]]

if (UNIX)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread -std=c++17 -fPIC -g3")
endif (UNIX)

include_directories("${PROJECT_SOURCE_DIR}/source/server/")
include_directories("${PROJECT_SOURCE_DIR}/source/client/")
include_directories("${PROJECT_SOURCE_DIR}/source/shared/")
include_directories("${PROJECT_SOURCE_DIR}/source/shared/async/")
include_directories("${PROJECT_SOURCE_DIR}/source/shared/ecs/")
include_directories("${PROJECT_SOURCE_DIR}/source/shared/net/")
include_directories("${PROJECT_SOURCE_DIR}/source/shared/graphic/")

include_directories("${PROJECT_SOURCE_DIR}/include/server/")
include_directories("${PROJECT_SOURCE_DIR}/include/client/")
include_directories("${PROJECT_SOURCE_DIR}/include/shared/")
include_directories("${PROJECT_SOURCE_DIR}/include/shared/graphic/")
include_directories("${PROJECT_SOURCE_DIR}/include/shared/components/")

if (WIN32)
    include_directories(${Boost_INCLUDE_DIRS})
endif (WIN32)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#[[AUTOMATIC TARGET ADDER]]
file(GLOB SERVER_SRC "source/server/*.cpp")
file(GLOB SERVER_INC "include/server/*.hpp")

file(GLOB CLIENT_SRC "source/client/*.cpp")
file(GLOB CLIENT_INC "include/client/*.hpp")

file(GLOB SHARED_SRC "source/shared/*.cpp")
file(GLOB SHARED_INC "include/shared/*.hpp")

file(GLOB ASYNC_SRC "source/shared/async/*.cpp")
file(GLOB ASYNC_INC "include/shared/async/*.hpp")

file(GLOB NET_SRC "source/shared/net/*.cpp")
file(GLOB NET_INC "include/shared/net/*.hpp")

file(GLOB ECS_SRC "source/shared/ecs/*.cpp")
file(GLOB ECS_INC "include/shared/ecs/*.hpp")

file(GLOB GRAPHIC_SRC "source/shared/graphic/*.cpp")
file(GLOB GRAPHIC_INC "include/shared/graphic/*.hpp")

add_executable(
    r-type_server
    ${SERVER_SRC}
    ${SERVER_INC}

    ${SHARED_SRC}
    ${SHARED_INC}

    ${ECS_SRC}
    ${ECS_INC}

    ${ASYNC_SRC}
    ${ASYNC_INC}

    ${NET_SRC}
    ${NET_INC}

    ${GRAPHIC_SRC}
    ${GRAPHIC_INC}
)

add_executable(
    r-type_client
    ${CLIENT_SRC}
    ${CLIENT_INC}

    ${SHARED_SRC}
    ${SHARED_INC}

    ${NET_SRC}
    ${NET_INC}

    ${ASYNC_SRC}
    ${ASYNC_INC}

    ${ECS_SRC}
    ${ECS_INC}

    ${GRAPHIC_SRC}
    ${GRAPHIC_INC}
)

target_link_libraries (r-type_server ${CMAKE_THREAD_LIBS_INIT} ${CONAN_LIBS} -lsfml-system -lsfml-graphics -lsfml-audio -lsfml-window )
target_link_libraries (r-type_client ${CMAKE_THREAD_LIBS_INIT} ${CONAN_LIBS} -lsfml-system -lsfml-graphics -lsfml-audio -lsfml-window )

add_custom_command(TARGET r-type_server
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_server> ${CMAKE_HOME_DIRECTORY}/.
    )

add_custom_command(TARGET r-type_client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_client> ${CMAKE_HOME_DIRECTORY}/.
    )
