cmake_minimum_required(VERSION 3.0)

project(PathfindingAPI)

add_executable(PathfindingAPI
    main.cpp
    PathfinderResourceFactory.cpp
    PathfinderService.cpp
    PathfinderServiceSettingsFactory.cpp)
target_link_libraries(PathfindingAPI restbed)
target_include_directories(PathfindingAPI PUBLIC ${CMAKE_SOURCE_DIR}/include)
set_property(TARGET PathfindingAPI PROPERTY CXX_STANDARD 17)