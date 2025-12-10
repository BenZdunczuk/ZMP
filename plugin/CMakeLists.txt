cmake_minimum_required(VERSION 3.0)

set(PROJ_NAME "plugins_4_program")
project(${PROJ_NAME})

include_directories(${PROJECT_SOURCE_DIR}/inc ${PROJECT_SOURCE_DIR}/../inc)
add_library(Interp4Move MODULE src/Interp4Move.cpp)
target_sources(Interp4Move PRIVATE
    src/Interp4Move.cpp
    ../src/Vector3D.cpp
    ../src/ComInterface.cpp
    ../inc/AbstractComChannel.hh
)
target_include_directories(Interp4Move PRIVATE ${PROJECT_SOURCE_DIR}/../inc)
add_custom_command(TARGET Interp4Move POST_BUILD
    # COMMAND ${CMAKE_COMMAND} -E copy libInterp4Move.so ~/ZMP/libs
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo " Utworzony zostal plugin:  libInterp4Move.so"
    COMMAND ${CMAKE_COMMAND} -E echo ""    
  )
add_library(Interp4Rotate MODULE src/Interp4Rotate.cpp)
target_sources(Interp4Rotate PRIVATE
    src/Interp4Rotate.cpp
    ../src/Vector3D.cpp
    ../src/ComInterface.cpp
    ../inc/AbstractComChannel.hh
)
target_include_directories(Interp4Rotate PRIVATE ${PROJECT_SOURCE_DIR}/../inc)
add_custom_command(TARGET Interp4Rotate POST_BUILD
    # COMMAND ${CMAKE_COMMAND} -E copy libInterp4Rotate.so ~/ZMP/libs
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo " Utworzony zostal plugin:  libInterp4Rotate.so"
    COMMAND ${CMAKE_COMMAND} -E echo ""    
  )
add_library(Interp4Pause MODULE src/Interp4Pause.cpp)
target_sources(Interp4Pause PRIVATE
    src/Interp4Pause.cpp
    ../src/Vector3D.cpp
    ../src/ComInterface.cpp
    ../inc/AbstractComChannel.hh
)
target_include_directories(Interp4Pause PRIVATE ${PROJECT_SOURCE_DIR}/../inc)
add_custom_command(TARGET Interp4Pause POST_BUILD
    # COMMAND ${CMAKE_COMMAND} -E copy libInterp4Pause.so ~/ZMP/libs
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo " Utworzony zostal plugin:  libInterp4Pause.so"
    COMMAND ${CMAKE_COMMAND} -E echo ""    
  )
add_library(Interp4Set MODULE src/Interp4Set.cpp)
target_sources(Interp4Set PRIVATE
    src/Interp4Set.cpp
    ../src/Vector3D.cpp
    ../src/ComInterface.cpp
    ../inc/AbstractComChannel.hh
)
target_include_directories(Interp4Set PRIVATE ${PROJECT_SOURCE_DIR}/../inc)
add_custom_command(TARGET Interp4Set POST_BUILD
    # COMMAND ${CMAKE_COMMAND} -E copy libInterp4Set.so ~/ZMP/libs
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo " Utworzony zostal plugin:  libInterp4Set.so"
    COMMAND ${CMAKE_COMMAND} -E echo ""    
  )


