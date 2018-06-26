# CMakeLists.txt generated Mon Jun 25 23:51:23 CEST 2018
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

#library(WIN32 !MSC8ARM) "user32 gdi32";
if ((WIN32 AND NOT DEFINED flagMSC8ARM))
  list ( APPEND LINK_LIST user32 gdi32 )
endif()

#library(LINUX) "dl freetype";
if ((${CMAKE_SYSTEM_NAME} MATCHES Linux))
  find_package ( Freetype REQUIRED  )
  if ( FREETYPE_FOUND )
      list ( APPEND INCLUDE_LIST ${FREETYPE_INCLUDE_DIRS} )
      list ( APPEND LINK_LIST ${FREETYPE_LIBRARIES} )
      # remove leading or trailing whitespace (e.g. for SDL2)
      if ( LINK_LIST )
          string ( STRIP "${LINK_LIST}" LINK_LIST )
      endif()
  endif()
  list ( APPEND LINK_LIST dl freetype )
endif()

#library(BSD !XLFD) "fontconfig freetype expat";
if ((${CMAKE_SYSTEM_NAME} MATCHES BSD AND NOT DEFINED flagXLFD))
  find_package ( Freetype REQUIRED  )
  if ( FREETYPE_FOUND )
      list ( APPEND INCLUDE_LIST ${FREETYPE_INCLUDE_DIRS} )
      list ( APPEND LINK_LIST ${FREETYPE_LIBRARIES} )
      # remove leading or trailing whitespace (e.g. for SDL2)
      if ( LINK_LIST )
          string ( STRIP "${LINK_LIST}" LINK_LIST )
      endif()
  endif()
  find_package ( EXPAT REQUIRED  )
  if ( EXPAT_FOUND )
      list ( APPEND INCLUDE_LIST ${EXPAT_INCLUDE_DIRS} )
      list ( APPEND LINK_LIST ${EXPAT_LIBRARIES} )
      # remove leading or trailing whitespace (e.g. for SDL2)
      if ( LINK_LIST )
          string ( STRIP "${LINK_LIST}" LINK_LIST )
      endif()
  endif()
  list ( APPEND LINK_LIST fontconfig freetype expat )
endif()

#library(LINUX !XLFD) "fontconfig expat";
if ((${CMAKE_SYSTEM_NAME} MATCHES Linux AND NOT DEFINED flagXLFD))
  find_package ( EXPAT REQUIRED  )
  if ( EXPAT_FOUND )
      list ( APPEND INCLUDE_LIST ${EXPAT_INCLUDE_DIRS} )
      list ( APPEND LINK_LIST ${EXPAT_LIBRARIES} )
      # remove leading or trailing whitespace (e.g. for SDL2)
      if ( LINK_LIST )
          string ( STRIP "${LINK_LIST}" LINK_LIST )
      endif()
  endif()
  list ( APPEND LINK_LIST fontconfig expat )
endif()

#library(OSX11) "fontconfig freetype expat";
if ((APPLE))
  find_package ( Freetype REQUIRED  )
  if ( FREETYPE_FOUND )
      list ( APPEND INCLUDE_LIST ${FREETYPE_INCLUDE_DIRS} )
      list ( APPEND LINK_LIST ${FREETYPE_LIBRARIES} )
      # remove leading or trailing whitespace (e.g. for SDL2)
      if ( LINK_LIST )
          string ( STRIP "${LINK_LIST}" LINK_LIST )
      endif()
  endif()
  find_package ( EXPAT REQUIRED  )
  if ( EXPAT_FOUND )
      list ( APPEND INCLUDE_LIST ${EXPAT_INCLUDE_DIRS} )
      list ( APPEND LINK_LIST ${EXPAT_LIBRARIES} )
      # remove leading or trailing whitespace (e.g. for SDL2)
      if ( LINK_LIST )
          string ( STRIP "${LINK_LIST}" LINK_LIST )
      endif()
  endif()
  list ( APPEND LINK_LIST fontconfig freetype expat )
endif()

#library(FREEBSD) xcb;
if ((${CMAKE_SYSTEM_NAME} MATCHES FreeBSD))
  list ( APPEND LINK_LIST xcb )
endif()

# Precompiled headers file
set ( PCH_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Draw.h )

list ( APPEND HEADER_LIST
      Draw.h
      FontInt.h
      Display.h
      Image.h
      Raster.h
      ImageOp.h
      iml.h
      iml_header.h
      iml_source.h
      DrawImg.iml
      DDARasterizer.h
      SDraw.h
      Cham.h
      gobj.dli
      gdk.dli
      gpixbuf.dli
      gtk.dli
      gnome.dli
)

list ( APPEND SOURCE_LIST_CPP
      Font.cpp
      FontCR.cpp
      FontWin32.cpp
      FontFc.cpp
      Draw.cpp
      DrawText.cpp
      DrawData.cpp
      Drawing.cpp
      ImageAnyDraw.cpp
      DrawUtil.cpp
      DrawTextUtil.cpp
      Display.cpp
      Image.cpp
      ImageBlit.cpp
      RasterFormat.cpp
      RasterWrite.cpp
      Palette.cpp
      Raster.cpp
      RasterEncoder.cpp
      ImageOp.cpp
      ImageChOp.cpp
      ImageScale.cpp
      BiCubic.cpp
      RescaleFilter.cpp
      MakeCache.cpp
      DrawRasterData.cpp
      Uhd.cpp
      Iml.cpp
      DDARasterizer.cpp
      SDrawClip.cpp
      SDrawPut.cpp
      SDrawText.cpp
      SDraw.cpp
      SImageDraw.cpp
      Cham.cpp
      SSettings.cpp
)

list ( APPEND Draw_DEPEND_LIST
      Core-lib
)

# Module properties
create_cpps_from_icpps()
set_source_files_properties ( ${HEADER_LIST} PROPERTIES HEADER_FILE_ONLY ON )
add_library ( Draw-lib ${LIB_TYPE} ${SOURCE_LIST_CPP} ${SOURCE_LIST_C})
target_include_directories ( Draw-lib PUBLIC ${INCLUDE_LIST} )
set_property ( TARGET Draw-lib APPEND PROPERTY COMPILE_OPTIONS "${COMPILE_FLAGS_LIST}" )

# Module dependecies
if ( Draw_DEPEND_LIST )
  add_dependencies ( Draw-lib ${Draw_DEPEND_LIST} )
endif()

# Module link
if ( Draw_DEPEND_LIST OR LINK_LIST )
  target_link_libraries ( Draw-lib ${Draw_DEPEND_LIST} ${LINK_LIST} )
endif()

# Precompiled headers settings
get_directory_property ( PCH_COMPILE_DEFINITIONS COMPILE_DEFINITIONS )
set_target_properties ( Draw-lib PROPERTIES COMPILE_FLAGS_LIST "${COMPILE_FLAGS_LIST}" )
set_target_properties ( Draw-lib PROPERTIES PCH_FILE "${PCH_FILE}" )
set_target_properties ( Draw-lib PROPERTIES PCH_INCLUDE_LIST "${INCLUDE_LIST}" )
set_target_properties ( Draw-lib PROPERTIES PCH_COMPILE_DEFINITIONS "${PCH_COMPILE_DEFINITIONS}" )

list ( LENGTH PCH_FILE PCH_FILE_LENGTH )
if ( PCH_FILE_LENGTH GREATER 1 )
  message ( FATAL_ERROR "Precompiled headers list can contain only one header file!" )
endif()
if ( PCH_FILE AND DEFINED flagPCH )
  get_filename_component ( PCH_NAME ${PCH_FILE} NAME )
  set ( PCH_DIR ${PROJECT_PCH_DIR}/Draw-lib )
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
      set_target_properties ( Draw-lib PROPERTIES COMPILE_FLAGS "-Yu${PCH_NAME} -Fp${PCH_HEADER}.pch" )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "Yc${PCH_NAME} -Fp${PCH_HEADER}.pch" )
  endif()
  if ( PCH_INCLUDE_PARAMS )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "${PCH_INCLUDE_PARAMS}" )
  endif()
endif()

