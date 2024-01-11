cmake_minimum_required(VERSION 3.0.2)
project(udp_comunication)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    geometry_msgs
    unitree_legged_msgs
)

catkin_package()


link_directories(${CMAKE_SOURCE_DIR}/udp_comunication/lib/amd64)


set(EXTRA_LIBS -pthread libunitree_legged_sdk.so libfaceLight_SDK_amd64.so) 


set(CMAKE_CXX_FLAGS "-O3 -fPIC")

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include/unitree_legged_sdk
)



add_executable(example_joystick src/example_joystick.cpp)
target_link_libraries(example_joystick ${EXTRA_LIBS} ${catkin_LIBRARIES})
add_dependencies(example_joystick ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(faceLightClient src/faceLightClient.cpp)
target_link_libraries(faceLightClient ${EXTRA_LIBS} ${catkin_LIBRARIES})
add_dependencies(faceLightClient ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


add_executable(example_walk src/example_walk.cpp)
target_link_libraries(example_walk ${EXTRA_LIBS} ${catkin_LIBRARIES})
add_dependencies(example_walk ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(ros_udp src/ros_udp.cpp)
target_link_libraries(ros_udp ${EXTRA_LIBS} ${catkin_LIBRARIES})
add_dependencies(ros_udp ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

