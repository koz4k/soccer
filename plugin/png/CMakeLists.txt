# CMakeLists.txt generated Mon Jun 25 23:51:25 CEST 2018
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

#options(BUILDER_OPTION) NOWARNINGS;
if ( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_CLANG )
  set ( CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}} -w")
  set ( CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE}} -w")
elseif ( MSVC )
  set ( CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}} -W0")
  set ( CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE}} -W0")
endif()

#library(!WIN32) png;
if ((NOT WIN32))
  find_package ( PNG REQUIRED  )
  if ( PNG_FOUND )
      list ( APPEND INCLUDE_LIST ${PNG_INCLUDE_DIRS} )
      list ( APPEND LINK_LIST ${PNG_LIBRARIES} )
      # remove leading or trailing whitespace (e.g. for SDL2)
      if ( LINK_LIST )
          string ( STRIP "${LINK_LIST}" LINK_LIST )
      endif()
  endif()
  list ( APPEND LINK_LIST png )
endif()

#options(MSC8ARM) "-D_WIN32_WCE -DARM -D_ARM_ -DUNDER_CE -DUNICODE -D_UNICODE";
if ((DEFINED flagMSC8ARM))
  list ( APPEND COMPILE_FLAGS_LIST -D_WIN32_WCE -DARM -D_ARM_ -DUNDER_CE -DUNICODE -D_UNICODE )
endif()

add_definitions (
-DPNG_NO_READ_EXPAND
-DPNG_NO_READ_SHIFT
-DPNG_NO_READ_PACK
-DPNG_NO_READ_SWAP
-DPNG_NO_READ_PACKSWAP
-DPNG_NO_READ_INVERT
-DPNG_NO_READ_DITHER
-DPNG_NO_READ_BACKGROUND
-DPNG_NO_READ_FILLER
-DPNG_NO_READ_GAMMA
-DPNG_NO_READ_GRAY_TO_RGB
-DPNG_NO_READ_SWAP_ALPHA
-DPNG_NO_READ_INVERT_ALPHA
-DPNG_NO_READ_STRIP_ALPHA
-DPNG_NO_READ_USER_TRANSFORM
-DPNG_NO_READ_RGB_TO_GRAY
-DPNG_NO_PROGRESSIVE_READ
-DPNG_NO_READ_COMPOSITE_NODIV
-DPNG_NO_MNG_FEATURES
-DPNG_NO_READ_EMPTY_PLTE
-DPNG_NO_WRITE_SHIFT
-DPNG_NO_WRITE_PACK
-DPNG_NO_WRITE_SWAP
-DPNG_NO_WRITE_PACKSWAP
-DPNG_NO_WRITE_INVERT
-DPNG_NO_WRITE_FILLER
-DPNG_NO_WRITE_SWAP_ALPHA
-DPNG_NO_WRITE_INVERT_ALPHA
-DPNG_NO_WRITE_USER_TRANSFORM
-DPNG_NO_USER_TRANSFORM_PTR
-DPNG_NO_WRITE_EMPTY_PLTE
-DPNG_NO_EASY_ACCESS
-DPNG_NO_READ_bKGD
-DPNG_NO_READ_cHRM
-DPNG_NO_READ_gAMA
-DPNG_NO_READ_iCCP
-DPNG_NO_READ_oFFs
-DPNG_NO_READ_pCAL
-DPNG_NO_READ_sCAL
-DPNG_NO_READ_sBIT
-DPNG_NO_READ_sPLT
-DPNG_NO_READ_sRGB
-DPNG_NO_READ_tIME
-DPNG_NO_READ_zTXt
-DPNG_NO_READ_OPT_PLTE
-DPNG_NO_INFO_IMAGE
)

list ( APPEND HEADER_LIST
      png.h
      lib/png.h
)

list ( APPEND SOURCE_LIST_C
      pnglib.c
)

list ( APPEND SOURCE_LIST_CPP
      pngupp.cpp
)

list ( APPEND SOURCE_LIST_ICPP
      pngreg.icpp
)

list ( APPEND plugin_png_DEPEND_LIST
      Core-lib
      Draw-lib
)

# Module properties
create_cpps_from_icpps()
set_source_files_properties ( ${HEADER_LIST} PROPERTIES HEADER_FILE_ONLY ON )
add_library ( plugin_png-lib ${LIB_TYPE} ${SOURCE_LIST_CPP} ${SOURCE_LIST_C})
target_include_directories ( plugin_png-lib PUBLIC ${INCLUDE_LIST} )
set_property ( TARGET plugin_png-lib APPEND PROPERTY COMPILE_OPTIONS "${COMPILE_FLAGS_LIST}" )

# Module dependecies
if ( plugin_png_DEPEND_LIST )
  add_dependencies ( plugin_png-lib ${plugin_png_DEPEND_LIST} )
endif()

# Module link
if ( plugin_png_DEPEND_LIST OR LINK_LIST )
  target_link_libraries ( plugin_png-lib ${plugin_png_DEPEND_LIST} ${LINK_LIST} )
endif()

# Precompiled headers settings
get_directory_property ( PCH_COMPILE_DEFINITIONS COMPILE_DEFINITIONS )
set_target_properties ( plugin_png-lib PROPERTIES COMPILE_FLAGS_LIST "${COMPILE_FLAGS_LIST}" )
set_target_properties ( plugin_png-lib PROPERTIES PCH_FILE "${PCH_FILE}" )
set_target_properties ( plugin_png-lib PROPERTIES PCH_INCLUDE_LIST "${INCLUDE_LIST}" )
set_target_properties ( plugin_png-lib PROPERTIES PCH_COMPILE_DEFINITIONS "${PCH_COMPILE_DEFINITIONS}" )

list ( LENGTH PCH_FILE PCH_FILE_LENGTH )
if ( PCH_FILE_LENGTH GREATER 1 )
  message ( FATAL_ERROR "Precompiled headers list can contain only one header file!" )
endif()
if ( PCH_FILE AND DEFINED flagPCH )
  get_filename_component ( PCH_NAME ${PCH_FILE} NAME )
  set ( PCH_DIR ${PROJECT_PCH_DIR}/plugin_png-lib )
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
      set_target_properties ( plugin_png-lib PROPERTIES COMPILE_FLAGS "-Yu${PCH_NAME} -Fp${PCH_HEADER}.pch" )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "Yc${PCH_NAME} -Fp${PCH_HEADER}.pch" )
  endif()
  if ( PCH_INCLUDE_PARAMS )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "${PCH_INCLUDE_PARAMS}" )
  endif()
endif()

