# CMakeLists.txt generated Mon Jun 25 23:51:21 CEST 2018
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

#library(WIN32 !MSC8ARM) "advapi32 comdlg32 comctl32";
if ((WIN32 AND NOT DEFINED flagMSC8ARM))
  list ( APPEND LINK_LIST advapi32 comdlg32 comctl32 )
endif()

#library((LINUX | BSD) & !NOGTK & !RAINBOW & !GTK3 & GUI) "gtk-x11-2.0 gdk-x11-2.0 atk-1.0 gdk_pixbuf-2.0 m pangocairo-1.0 fontconfig Xext Xrender Xinerama Xi Xrandr Xcursor Xfixes pango-1.0 cairo X11 gobject-2.0 gmodule-2.0 glib-2.0";
if ((${CMAKE_SYSTEM_NAME} MATCHES Linux  OR  ${CMAKE_SYSTEM_NAME} MATCHES BSD) AND (NOT BUILD_WITHOUT_GTK AND NOT BUILD_WITH_RAINBOW AND NOT GTK3 AND DEFINED flagGUI))
  find_package ( GTK2 REQUIRED gtk )
  if ( GTK2_FOUND )
      list ( APPEND INCLUDE_LIST ${GTK2_INCLUDE_DIRS} )
      list ( APPEND LINK_LIST ${GTK2_LIBRARIES} )
      # remove leading or trailing whitespace (e.g. for SDL2)
      if ( LINK_LIST )
          string ( STRIP "${LINK_LIST}" LINK_LIST )
      endif()
  endif()
  find_package ( PkgConfig REQUIRED )
  pkg_check_modules ( LIBNOTIFY REQUIRED libnotify )
  if ( LIBNOTIFY_FOUND )
      list ( APPEND INCLUDE_LIST ${LIBNOTIFY_INCLUDE_DIR} )
      list ( APPEND LINK_LIST ${LIBNOTIFY_LIBRARIES} )
  endif()
  find_package ( X11 REQUIRED  )
  if ( X11_FOUND )
      list ( APPEND INCLUDE_LIST ${X11_INCLUDE_DIR} )
      list ( APPEND LINK_LIST ${X11_LIBRARIES} )
      # remove leading or trailing whitespace (e.g. for SDL2)
      if ( LINK_LIST )
          string ( STRIP "${LINK_LIST}" LINK_LIST )
      endif()
  endif()
  list ( APPEND LINK_LIST gtk-x11-2.0 gdk-x11-2.0 atk-1.0 gdk_pixbuf-2.0 m pangocairo-1.0 fontconfig Xext Xrender Xinerama Xi Xrandr Xcursor Xfixes pango-1.0 cairo X11 gobject-2.0 gmodule-2.0 glib-2.0 )
endif()

#library((LINUX | BSD) & GTK3) "gtk-3.0 gdk-3.0 atk-1.0 gdk_3.0 m pangocairo-1.0 fontconfig Xext Xrender Xinerama Xi Xrandr Xcursor Xfixes pango-1.0 cairo X11 gobject-2.0 gmodule-2.0 glib-2.0";
if ((${CMAKE_SYSTEM_NAME} MATCHES Linux  OR  ${CMAKE_SYSTEM_NAME} MATCHES BSD) AND (GTK3))
  find_package ( PkgConfig REQUIRED )
  pkg_check_modules ( GTK3 REQUIRED gtk+-3.0)
  if ( GTK3_FOUND )
      list ( APPEND INCLUDE_LIST ${GTK3_INCLUDE_DIRS} )
      list ( APPEND LINK_LIST ${GTK3_LIBRARIES} )
      # remove leading or trailing whitespace (e.g. for SDL2)
      if ( LINK_LIST )
          string ( STRIP "${LINK_LIST}" LINK_LIST )
      endif()
  endif()
  find_package ( X11 REQUIRED  )
  if ( X11_FOUND )
      list ( APPEND INCLUDE_LIST ${X11_INCLUDE_DIR} )
      list ( APPEND LINK_LIST ${X11_LIBRARIES} )
      # remove leading or trailing whitespace (e.g. for SDL2)
      if ( LINK_LIST )
          string ( STRIP "${LINK_LIST}" LINK_LIST )
      endif()
  endif()
  list ( APPEND LINK_LIST gtk-3.0 gdk-3.0 atk-1.0 gdk_3.0 m pangocairo-1.0 fontconfig Xext Xrender Xinerama Xi Xrandr Xcursor Xfixes pango-1.0 cairo X11 gobject-2.0 gmodule-2.0 glib-2.0 )
endif()

#library(WIN32 !MSC8ARM) "user32 gdi32";
if ((WIN32 AND NOT DEFINED flagMSC8ARM))
  list ( APPEND LINK_LIST user32 gdi32 )
endif()

#library(LINUX !RAINBOW GUI) "X11 Xrender Xinerama";
if ((${CMAKE_SYSTEM_NAME} MATCHES Linux AND NOT BUILD_WITH_RAINBOW AND DEFINED flagGUI))
  find_package ( X11 REQUIRED  )
  if ( X11_FOUND )
      list ( APPEND INCLUDE_LIST ${X11_INCLUDE_DIR} )
      list ( APPEND LINK_LIST ${X11_LIBRARIES} )
      # remove leading or trailing whitespace (e.g. for SDL2)
      if ( LINK_LIST )
          string ( STRIP "${LINK_LIST}" LINK_LIST )
      endif()
  endif()
  list ( APPEND LINK_LIST X11 Xrender Xinerama )
endif()

#library(LINUX !RAINBOW) dl;
if ((${CMAKE_SYSTEM_NAME} MATCHES Linux AND NOT BUILD_WITH_RAINBOW))
  list ( APPEND LINK_LIST dl )
endif()

#library(LINUX !XLFD !RAINBOW GUI) Xft;
if ((${CMAKE_SYSTEM_NAME} MATCHES Linux AND NOT DEFINED flagXLFD AND NOT BUILD_WITH_RAINBOW AND DEFINED flagGUI))
  list ( APPEND LINK_LIST Xft )
endif()

#library(BSD !RAINBOW) "X11 Xau Xdmcp";
if ((${CMAKE_SYSTEM_NAME} MATCHES BSD AND NOT BUILD_WITH_RAINBOW))
  find_package ( X11 REQUIRED  )
  if ( X11_FOUND )
      list ( APPEND INCLUDE_LIST ${X11_INCLUDE_DIR} )
      list ( APPEND LINK_LIST ${X11_LIBRARIES} )
      # remove leading or trailing whitespace (e.g. for SDL2)
      if ( LINK_LIST )
          string ( STRIP "${LINK_LIST}" LINK_LIST )
      endif()
  endif()
  list ( APPEND LINK_LIST X11 Xau Xdmcp )
endif()

#library(BSD !XLFD !RAINBOW) "Xft fontconfig Xrender freetype expat";
if ((${CMAKE_SYSTEM_NAME} MATCHES BSD AND NOT DEFINED flagXLFD AND NOT BUILD_WITH_RAINBOW))
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
  list ( APPEND LINK_LIST Xft fontconfig Xrender freetype expat )
endif()

#library(LINUX !XLFD !SHARED !RAINBOW GUI) "fontconfig Xrender freetype";
if ((${CMAKE_SYSTEM_NAME} MATCHES Linux AND NOT DEFINED flagXLFD AND NOT BUILD_SHARED_LIBS AND NOT BUILD_WITH_RAINBOW AND DEFINED flagGUI))
  find_package ( Freetype REQUIRED  )
  if ( FREETYPE_FOUND )
      list ( APPEND INCLUDE_LIST ${FREETYPE_INCLUDE_DIRS} )
      list ( APPEND LINK_LIST ${FREETYPE_LIBRARIES} )
      # remove leading or trailing whitespace (e.g. for SDL2)
      if ( LINK_LIST )
          string ( STRIP "${LINK_LIST}" LINK_LIST )
      endif()
  endif()
  list ( APPEND LINK_LIST fontconfig Xrender freetype )
endif()

#library(OSX11) "X11 Xft fontconfig Xrender Xinerama freetype expat";
if ((APPLE))
  find_package ( X11 REQUIRED  )
  if ( X11_FOUND )
      list ( APPEND INCLUDE_LIST ${X11_INCLUDE_DIR} )
      list ( APPEND LINK_LIST ${X11_LIBRARIES} )
      # remove leading or trailing whitespace (e.g. for SDL2)
      if ( LINK_LIST )
          string ( STRIP "${LINK_LIST}" LINK_LIST )
      endif()
  endif()
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
  list ( APPEND LINK_LIST X11 Xft fontconfig Xrender Xinerama freetype expat )
endif()

#library(FREEBSD | DRAGONFLY) xcb;
if ((${CMAKE_SYSTEM_NAME} MATCHES FreeBSD  OR  ${CMAKE_SYSTEM_NAME} MATCHES DragonFly))
  list ( APPEND LINK_LIST xcb )
endif()

#library(POSIX !NOGTK !RAINBOW GUI) notify;
if ((DEFINED flagPOSIX AND NOT BUILD_WITHOUT_GTK AND NOT BUILD_WITH_RAINBOW AND DEFINED flagGUI))
  list ( APPEND LINK_LIST notify )
endif()

#library(DRAGONFLY) "Xext Xinerama";
if ((${CMAKE_SYSTEM_NAME} MATCHES DragonFly))
  list ( APPEND LINK_LIST Xext Xinerama )
endif()

# Precompiled headers file
set ( PCH_FILE ${CMAKE_CURRENT_SOURCE_DIR}/CtrlCore.h )

list ( APPEND HEADER_LIST
      CtrlCore.h
      MKeys.h
      stdids.h
      TopWindow.h
      lay.h
      llay.h
      CtrlCore.iml
      CtrlCore.t
      CtrlCore.defs
      Win32Gui.h
      Win32GuiA.h
      Win32Keys.h
      MultiMon.dli
      Win32Ctrl.h
      Win32Top.h
      Win32Msg.i
      X11Gui.h
      X11GuiA.h
      X11Keys.h
      X11Ctrl.h
      X11Top.h
      X11Event.i
      Gtk.h
      GtkAfter.h
      GtkKeys.h
      GtkCtrl.h
      GtkTop.h
)

list ( APPEND SOURCE_LIST_CPP
      SystemDraw.cpp
      Frame.cpp
      CtrlMt.cpp
      Ctrl.cpp
      CtrlChild.cpp
      CtrlPos.cpp
      CtrlDraw.cpp
      CtrlMouse.cpp
      CtrlKbd.cpp
      CtrlTimer.cpp
      CtrlClip.cpp
      LocalLoop.cpp
      CtrlCoreInit.cpp
      TopWindow.cpp
      DrawWin32.cpp
      DrawOpWin32.cpp
      DrawTextWin32.cpp
      ImageWin32.cpp
      MetaFile.cpp
      UtilWin32.cpp
      Win32Ctrl.cpp
      Win32Wnd.cpp
      Win32Clip.cpp
      Win32DnD.cpp
      Win32Proc.cpp
      TopWin32.cpp
      DHCtrl.cpp
      DrawX11.cpp
      DrawOpX11.cpp
      DrawTextX11.cpp
      ImageX11.cpp
      UtilX11.cpp
      X11Ctrl.cpp
      X11Wnd.cpp
      X11Proc.cpp
      X11Clip.cpp
      X11DnD.cpp
      X11Top.cpp
      X11ImgClip.cpp
      X11App.cpp
      X11DHCtrl.cpp
      GtkDrawOp.cpp
      GtkDrawText.cpp
      GtkDrawImage.cpp
      GdkImage.cpp
      GtkUtil.cpp
      GtkX11Util.cpp
      GtkCtrl.cpp
      GtkCapture.cpp
      GtkWnd.cpp
      GtkCreate.cpp
      GtkEvent.cpp
      GtkTop.cpp
      GtkClip.cpp
      GtkDnD.cpp
      GtkApp.cpp
      ParseRTF.cpp
      EncodeRTF.cpp
)

list ( APPEND CtrlCore_DEPEND_LIST
      Draw-lib
      plugin_bmp-lib
      RichText-lib
)

# Module properties
create_cpps_from_icpps()
set_source_files_properties ( ${HEADER_LIST} PROPERTIES HEADER_FILE_ONLY ON )
add_library ( CtrlCore-lib ${LIB_TYPE} ${SOURCE_LIST_CPP} ${SOURCE_LIST_C})
target_include_directories ( CtrlCore-lib PUBLIC ${INCLUDE_LIST} )
set_property ( TARGET CtrlCore-lib APPEND PROPERTY COMPILE_OPTIONS "${COMPILE_FLAGS_LIST}" )

# Module dependecies
if ( CtrlCore_DEPEND_LIST )
  add_dependencies ( CtrlCore-lib ${CtrlCore_DEPEND_LIST} )
endif()

# Module link
if ( CtrlCore_DEPEND_LIST OR LINK_LIST )
  target_link_libraries ( CtrlCore-lib ${CtrlCore_DEPEND_LIST} ${LINK_LIST} )
endif()

# Precompiled headers settings
get_directory_property ( PCH_COMPILE_DEFINITIONS COMPILE_DEFINITIONS )
set_target_properties ( CtrlCore-lib PROPERTIES COMPILE_FLAGS_LIST "${COMPILE_FLAGS_LIST}" )
set_target_properties ( CtrlCore-lib PROPERTIES PCH_FILE "${PCH_FILE}" )
set_target_properties ( CtrlCore-lib PROPERTIES PCH_INCLUDE_LIST "${INCLUDE_LIST}" )
set_target_properties ( CtrlCore-lib PROPERTIES PCH_COMPILE_DEFINITIONS "${PCH_COMPILE_DEFINITIONS}" )

list ( LENGTH PCH_FILE PCH_FILE_LENGTH )
if ( PCH_FILE_LENGTH GREATER 1 )
  message ( FATAL_ERROR "Precompiled headers list can contain only one header file!" )
endif()
if ( PCH_FILE AND DEFINED flagPCH )
  get_filename_component ( PCH_NAME ${PCH_FILE} NAME )
  set ( PCH_DIR ${PROJECT_PCH_DIR}/CtrlCore-lib )
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
      set_target_properties ( CtrlCore-lib PROPERTIES COMPILE_FLAGS "-Yu${PCH_NAME} -Fp${PCH_HEADER}.pch" )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "Yc${PCH_NAME} -Fp${PCH_HEADER}.pch" )
  endif()
  if ( PCH_INCLUDE_PARAMS )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "${PCH_INCLUDE_PARAMS}" )
  endif()
endif()

