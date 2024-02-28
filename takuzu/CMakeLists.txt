#===============================================================================
set(EXE_NAME Takuzu)

set(INC_FILES
        inc/TakuzuRewardFunction.h
        inc/TakuzuAction.h
        inc/TakuzuState.h)

set(SRC_FILES
        src/TakuzuRewardFunction.cpp
        src/TakuzuAction.cpp
        src/TakuzuState.cpp
        src/main.cpp)

#===============================================================================
add_executable(${EXE_NAME})
target_sources(${EXE_NAME} PRIVATE ${SRC_FILES})
target_link_libraries(${EXE_NAME} PRIVATE mcts)
