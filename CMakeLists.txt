cmake_minimum_required(VERSION 3.12.3)
project(rispirit)

set(CMAKE_CXX_STANDARD 14)


add_executable(rispirit
        main.cpp
        States/Overworld/overworld.cpp
        States/Overworld/overworld.h
        States/Battlestate/BattleControlls.cpp
        States/Battlestate/BattleControlls.h
        States/Battlestate/Units.cpp
        States/Battlestate/Units.h
        States/Menu/Menu.cpp
        States/Menu/Menu.h
        States/Menu/Load.cpp
        States/Menu/Load.h
        States/Menu/Save.cpp
        States/Menu/Save.h
        States/Menu/Settings.cpp
        States/Menu/Settings.h
        States/Menu/Extras.cpp
        States/Menu/Extras.h
        States/Menu/CharacterCreation.cpp
        States/Menu/CharacterCreation.h States/Overworld/textbox.cpp States/Overworld/textbox.h
        States/Menu/CharacterCreation.h
        States/Menu/Pause.cpp
        States/Menu/Pause.h
        States/AudioHandler.h
        States/Battlestate/Attacks.cpp
        States/Battlestate/Attacks.h
        States/Battlestate/AI.h
        States/Inventory/Items.h
        States/Inventory/Inventory.cpp
        States/Inventory/Inventory.h)


target_link_libraries(rispirit sfml-graphics sfml-window sfml-audio sfml-system)
target_link_libraries(rispirit jsoncpp)
target_link_libraries(rispirit tgui)


