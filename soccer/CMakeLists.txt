# CMakeLists.txt generated Mon Jun 25 23:51:20 CEST 2018
cmake_minimum_required ( VERSION 2.8.10 )

#################################################
# In-Source builds are strictly prohibited.
#################################################
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
  message ( FATAL_ERROR
  "\n****************************** ERROR ******************************\n"
  "In-source build are not allowed. "
  "Please do not polute the sources with binaries or any project unrelated files. "
  "To remove generated files run:\n"
  "'rm -rf CMakeCache.txt CMakeFiles'\n"
  "To build the project, please do the following:\n"
  "'mkdir build && cd build && cmake ..'"
  "\n****************************** ERROR ******************************\n")
endif()

# Set the default library directory to store built libraries
set ( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib )

# Module definitions
add_definitions ( -DflagMAIN )

list ( APPEND HEADER_LIST
      soccer/ai/heur/smartUniform.h
      soccer/ai/heur/uniform.h
      soccer/Ai.h
      soccer/ai/HeuristicSearch.h
      soccer/ai/RouletteSearch.h
      soccer/ai/DeepMaxOfFewSearch.h
      soccer/ai/MaxOfFewSearch.h
      soccer/ai/MaxSearch.h
      soccer/ai/heur/ReboundAwareNaive.h
      soccer/ai/heur/naive.h
      generator.hpp
      soccer/ai/open/AlphaBetaGenerator.h
      soccer/ai/AlphaBeta.h
      soccer/ai/Negamax.h
      soccer/Vector2.h
      soccer/core.h
      soccer/GameState.h
      Board.h
      Board.usc
      MainWindow.h
      soccer/contest/Pairwise.h
      soccer/contest/TwoTeam.h
      soccer/contest/Full.h
      soccer/Contest.h
      ab_contest.hpp
      soccer/AiStandalone.h
      sanity_old_contest.hpp
      sanity_contest.hpp
      soccer/ai/open/io.h
      soccer/ai/WithOpenings.h
      mcts_contest.hpp
      heavy_contest.hpp
      play.hpp
      judge.hpp
      soccer/ai/mcts/Tree.h
      soccer/ai/MonteCarloTreeSearch.h
      soccer/Timer.h
      soccer/ai/open/YourMove.h
      soccer/ai/open/MyMove.h
      soccer/ai/open/Move.h
      Main.lay
      k_tuning.hpp
      conversion.h
      AiVsAi.h
      PlayerVsAi.h
      soccer/ai/mcts/OldTree.h
      soccer/ai/OldMcts.h
      soccer/ai/heur/SimpleMonteCarlo.h
      soccer/timing/Uniform.h
      soccer/TimingStrategy.h
      soccer/Judge.h
      standalone_ab.hpp
      standalone_mcts.hpp
      time_contest.hpp
      timing_test.hpp
)

list ( APPEND SOURCE_LIST_CPP
      soccer/ai/heur/uniform.cpp
      soccer/ai/heur/smartUniform.cpp
      soccer/Ai.cpp
      soccer/ai/HeuristicSearch.cpp
      soccer/ai/RouletteSearch.cpp
      soccer/ai/MaxSearch.cpp
      soccer/ai/DeepMaxOfFewSearch.cpp
      soccer/ai/MaxOfFewSearch.cpp
      soccer/ai/heur/naive.cpp
      soccer/ai/heur/ReboundAwareNaive.cpp
      soccer/ai/open/AlphaBetaGenerator.cpp
      soccer/ai/AlphaBeta.cpp
      soccer/ai/Negamax.cpp
      Board.cpp
      soccer/Vector2.cpp
      soccer/core.cpp
      soccer/GameState.cpp
      MainWindow.cpp
      soccer/contest/TwoTeam.cpp
      soccer/contest/Pairwise.cpp
      soccer/contest/Full.cpp
      soccer/Contest.cpp
      soccer/AiStandalone.cpp
      soccer/ai/open/io.cpp
      soccer/ai/WithOpenings.cpp
      soccer/ai/mcts/Tree.cpp
      soccer/ai/MonteCarloTreeSearch.cpp
      soccer/Timer.cpp
      soccer/ai/open/MyMove.cpp
      soccer/ai/open/YourMove.cpp
      main.cpp
      conversion.cpp
      AiVsAi.cpp
      soccer/ai/mcts/OldTree.cpp
      soccer/ai/OldMcts.cpp
      soccer/ai/heur/SimpleMonteCarlo.cpp
      soccer/timing/Uniform.cpp
      soccer/Judge.cpp
      PlayerVsAi.cpp
      soccer/TimingStrategy.cpp
)

list ( APPEND soccer_DEPEND_LIST
      CtrlLib-lib
)

# Module properties
create_cpps_from_icpps()
set_source_files_properties ( ${HEADER_LIST} PROPERTIES HEADER_FILE_ONLY ON )
add_library ( soccer-lib ${LIB_TYPE} ${SOURCE_LIST_CPP} ${SOURCE_LIST_C})
target_include_directories ( soccer-lib PUBLIC ${INCLUDE_LIST} )
set_property ( TARGET soccer-lib APPEND PROPERTY COMPILE_OPTIONS "${COMPILE_FLAGS_LIST}" )

# Module dependecies
if ( soccer_DEPEND_LIST )
  add_dependencies ( soccer-lib ${soccer_DEPEND_LIST} )
endif()

# Module link
if ( soccer_DEPEND_LIST OR LINK_LIST )
  target_link_libraries ( soccer-lib ${soccer_DEPEND_LIST} ${LINK_LIST} )
endif()

# Precompiled headers settings
get_directory_property ( PCH_COMPILE_DEFINITIONS COMPILE_DEFINITIONS )
set_target_properties ( soccer-lib PROPERTIES COMPILE_FLAGS_LIST "${COMPILE_FLAGS_LIST}" )
set_target_properties ( soccer-lib PROPERTIES PCH_FILE "${PCH_FILE}" )
set_target_properties ( soccer-lib PROPERTIES PCH_INCLUDE_LIST "${INCLUDE_LIST}" )
set_target_properties ( soccer-lib PROPERTIES PCH_COMPILE_DEFINITIONS "${PCH_COMPILE_DEFINITIONS}" )

list ( LENGTH PCH_FILE PCH_FILE_LENGTH )
if ( PCH_FILE_LENGTH GREATER 1 )
  message ( FATAL_ERROR "Precompiled headers list can contain only one header file!" )
endif()
if ( PCH_FILE AND DEFINED flagPCH )
  get_filename_component ( PCH_NAME ${PCH_FILE} NAME )
  set ( PCH_DIR ${PROJECT_PCH_DIR}/soccer-lib )
  set ( PCH_HEADER ${PCH_DIR}/${PCH_NAME} )
  if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" )
      if ( ${CMAKE_VERBOSE_MAKEFILE} EQUAL 1 )
        set ( PCH_INCLUDE_PARAMS " -H -Winvalid-pch -include ${PCH_HEADER}" )
      else()
        set ( PCH_INCLUDE_PARAMS " -Winvalid-pch -include ${PCH_HEADER}" )
      endif()
  endif()
  if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" )
      set ( PCH_INCLUDE_PARAMS " -Winvalid-pch -include-pch ${PCH_HEADER}.pch" )
  endif()
  if ( MSVC )
      set_target_properties ( soccer-lib PROPERTIES COMPILE_FLAGS "-Yu${PCH_NAME} -Fp${PCH_HEADER}.pch" )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "Yc${PCH_NAME} -Fp${PCH_HEADER}.pch" )
  endif()
  if ( PCH_INCLUDE_PARAMS )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "${PCH_INCLUDE_PARAMS}" )
  endif()
endif()

