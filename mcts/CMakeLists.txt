#===============================================================================
set(LIB_NAME mcts)
set(INC_FILES
        inc/mcts/MCTSAgent.h
        inc/mcts/MCTSTree.h
        inc/mcts/IAction.h
        inc/mcts/IRewardFunction.h
        inc/mcts/IState.h)
set(SRC_FILES
        src/MCTSAgent.cpp
        src/MCTSTree.cpp)
#===============================================================================
add_library(${LIB_NAME})
target_sources(${LIB_NAME} PRIVATE ${SRC_FILES})
#===============================================================================
if(ENABLE_TEST)
    add_subdirectory(tst)
endif()

#===============================================================================
prj_component_install(${LIB_NAME})
