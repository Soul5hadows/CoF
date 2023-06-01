#Minimum version required
cmake_minimum_required(VERSION 3.12)

#Project name and version
    project(ROGUE VERSION 1.0)

    

#Request C standard features
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    add_compile_options(-Wall)

#Compile source files
add_executable(ROGUE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/componentvector.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ecs.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/game.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/stack.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/tilesystem.c")
#Output directory
set_target_properties(ROGUE PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

#Add Directores
target_include_directories(ROGUE PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(ROGUE ${CMAKE_SOURCE_DIR}/lib/pdcurses.a)
target_link_libraries(ROGUE ${CMAKE_SOURCE_DIR}/lib/BearLibTerminal.lib)