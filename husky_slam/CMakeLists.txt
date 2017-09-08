
cmake_minimum_required(VERSION 2.8.12)

project(husky_slam)

set( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake_Modules;${CMAKE_MODULE_PATH}")

find_package(catkin REQUIRED COMPONENTS
                        roscpp
                        roslib
)



set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(husky_slam_INCLUDE_DIRS
        src
        include
        nodes
)

include_directories(${husky_slam_INCLUDE_DIRS}
                    ${catkin_INCLUDE_DIRS})

catkin_package(
    INCLUDE_DIRS include
    CATKIN_DEPENDS roscpp roslib)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions( ${catkin_DEFINITIONS} )



add_executable( ${PROJECT_NAME}_node 
                include/husky_slam/HuskySlam.h
                nodes/HuskySlam_node.cpp
                src/HuskySlam.cpp
               )


add_dependencies(${PROJECT_NAME}_node ${catkin_EXPORTED_TARGETS})


target_link_libraries(${PROJECT_NAME}_node
                        ${catkin_LIBRARIES})

