#===============================================================================
set(EXE_NAME Takuzu)
set(SRC_FILES Takuzu.h Takuzu.cpp main.cpp)
#===============================================================================
add_executable(${EXE_NAME})
target_sources(${EXE_NAME} PRIVATE ${SRC_FILES})
target_link_libraries(${EXE_NAME} PRIVATE mcts)
