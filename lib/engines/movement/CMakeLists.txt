add_library(MovementEngine 
    STATIC 
        MovementEngine.cpp
        MovementParser.cpp
    )

target_sources(MovementEngine 
    PRIVATE 
        ${CMAKE_CURRENT_LIST_DIR}/MovementEngine.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MovementParser.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/MovementEngine.hpp
        ${CMAKE_CURRENT_LIST_DIR}/MovementParser.hpp
    )

target_link_libraries(MovementEngine
    PUBLIC
        Logger
        pathfinder
        Vector2
        RobotMovement
        LocationEngine
    )
