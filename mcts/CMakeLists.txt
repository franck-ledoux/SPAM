#===============================================================================
set(LIB_NAME mcts)
set(INC_FILES
        inc/mcts/MCTSAgent.h
        inc/mcts/MCTSLoop.h
        inc/mcts/MCTSTree.h
        inc/mcts/IAction.h
        inc/mcts/IRewardFunction.h
        inc/mcts/IState.h)
set(SRC_FILES
        src/MCTSAgent.cpp
        src/MCTSLoop.cpp
        src/MCTSTree.cpp)
#===============================================================================
add_library(${LIB_NAME})
target_sources(${LIB_NAME} PRIVATE ${SRC_FILES})
target_link_libraries(${LIB_NAME} PRIVATE nlohmann_json::nlohmann_json)
#===============================================================================
if(ENABLE_TEST)
    add_subdirectory(tst)
endif()

#===============================================================================
prj_component_install(${LIB_NAME})
