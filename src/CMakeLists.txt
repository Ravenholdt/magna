find_package(SFML 2 COMPONENTS network audio graphics window system REQUIRED)

add_executable(magna 
    main.cpp 
    galaxy.cpp 
    system.cpp 
    celestial.cpp 
    colony.cpp
    resources.cpp
	AI.cpp
    
    ships.cpp
    shipParts.cpp
    
    algorithms.cpp
    generateSol.cpp
    
    gui/gui.cpp)

target_link_libraries(magna sfml-system sfml-window sfml-graphics sfml-network sfml-audio)


# sfml-system sfml-window sfml-graphics sfml-network sfml-audio
