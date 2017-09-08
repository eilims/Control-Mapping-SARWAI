cmake_minimum_required(VERSION 2.8.12)
project(crash_the_husky)

set( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake_Modules;${CMAKE_MODULE_PATH}")

find_package(catkin REQUIRED
                    roscpp
                    roslib
                    nav_msgs
                    vehicle
)


set(crash_the_husky_INCLUDE_DIRS
        src
        include
        nodes
)

include_directories(${crash_the_husky_INCLUDE_DIRS}
                    ${catkin_INCLUDE_DIRS} 
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp roslib
)

set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")

add_executable(${PROJECT_NAME}_node
                nodes/crash_the_husky_node.cpp
                src/CrashTheHusky.cpp
                include/crash_the_husky/CrashTheHusky.h
)

add_dependencies(${PROJECT_NAME}_node ${catkin_EXPORTED_TARGETS})

target_link_libraries(${PROJECT_NAME}_node
                        ${catkin_LIBRARIES}
)