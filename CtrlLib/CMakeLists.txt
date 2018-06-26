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

#uses(POSIX | LINUX | FREEBSD) PdfDraw;
if ((DEFINED flagPOSIX  OR  ${CMAKE_SYSTEM_NAME} MATCHES Linux  OR  ${CMAKE_SYSTEM_NAME} MATCHES FreeBSD))
  list ( APPEND CtrlLib_DEPEND_LIST PdfDraw-lib  )
endif()

# Precompiled headers file
set ( PCH_FILE ${CMAKE_CURRENT_SOURCE_DIR}/CtrlLib.h )

list ( APPEND HEADER_LIST
      CtrlLib.h
      LabelBase.h
      PushCtrl.h
      EditCtrl.h
      TextEdit.h
      ScrollBar.h
      HeaderCtrl.h
      ArrayCtrl.h
      MultiButton.h
      DropChoice.h
      StaticCtrl.h
      Splitter.h
      SliderCtrl.h
      ColumnList.h
      Progress.h
      AKeys.h
      key_header.h
      key_source.h
      RichText.h
      DateTimeCtrl.h
      SuggestCtrl.h
      Bar.h
      MenuImp.h
      StatusBar.h
      TabCtrl.h
      TreeCtrl.h
      DlgColor.h
      FileSel.h
      CtrlUtil.h
      Ctrl.iml
      Ctrl.lay
      CtrlLib.t
      Lang.h
      Ch.h
      XPTheme.dli
      Ctrls.iml
      ChGtk.h
      ClassicCtrls.iml
      AmbientCtrls.iml
      Normal.upt
      Complex.upt
      CtrlLib.usc
)

list ( APPEND SOURCE_LIST_CPP
      LabelBase.cpp
      Button.cpp
      Switch.cpp
      EditField.cpp
      Text.cpp
      LineEdit.cpp
      DocEdit.cpp
      ScrollBar.cpp
      HeaderCtrl.cpp
      ArrayCtrl.cpp
      MultiButton.cpp
      PopupTable.cpp
      DropList.cpp
      DropChoice.cpp
      Static.cpp
      Splitter.cpp
      FrameSplitter.cpp
      SliderCtrl.cpp
      ColumnList.cpp
      Progress.cpp
      AKeys.cpp
      RichTextView.cpp
      Prompt.cpp
      Help.cpp
      DateTimeCtrl.cpp
      SuggestCtrl.cpp
      Bar.cpp
      MenuItem.cpp
      MenuBar.cpp
      ToolButton.cpp
      ToolBar.cpp
      ToolTip.cpp
      StatusBar.cpp
      TabCtrl.cpp
      TreeCtrl.cpp
      DropTree.cpp
      DlgColor.cpp
      ColorPopup.cpp
      ColorPusher.cpp
      FileList.cpp
      FileSel.cpp
      FileSelUtil.cpp
      PrinterJob.cpp
      Windows.cpp
      Win32.cpp
      Gtk.cpp
      TrayIconWin32.cpp
      TrayIconX11.cpp
      TrayIconGtk.cpp
      Update.cpp
      CtrlUtil.cpp
      CtrlLibInit.cpp
      LNGCtrl.cpp
      Ch.cpp
      ChWin32.cpp
      ChGtk0.cpp
      ChGtk.cpp
)

list ( APPEND CtrlLib_DEPEND_LIST
      CtrlCore-lib
)

# Module properties
create_cpps_from_icpps()
set_source_files_properties ( ${HEADER_LIST} PROPERTIES HEADER_FILE_ONLY ON )
add_library ( CtrlLib-lib ${LIB_TYPE} ${SOURCE_LIST_CPP} ${SOURCE_LIST_C})
target_include_directories ( CtrlLib-lib PUBLIC ${INCLUDE_LIST} )
set_property ( TARGET CtrlLib-lib APPEND PROPERTY COMPILE_OPTIONS "${COMPILE_FLAGS_LIST}" )

# Module dependecies
if ( CtrlLib_DEPEND_LIST )
  add_dependencies ( CtrlLib-lib ${CtrlLib_DEPEND_LIST} )
endif()

# Module link
if ( CtrlLib_DEPEND_LIST OR LINK_LIST )
  target_link_libraries ( CtrlLib-lib ${CtrlLib_DEPEND_LIST} ${LINK_LIST} )
endif()

# Precompiled headers settings
get_directory_property ( PCH_COMPILE_DEFINITIONS COMPILE_DEFINITIONS )
set_target_properties ( CtrlLib-lib PROPERTIES COMPILE_FLAGS_LIST "${COMPILE_FLAGS_LIST}" )
set_target_properties ( CtrlLib-lib PROPERTIES PCH_FILE "${PCH_FILE}" )
set_target_properties ( CtrlLib-lib PROPERTIES PCH_INCLUDE_LIST "${INCLUDE_LIST}" )
set_target_properties ( CtrlLib-lib PROPERTIES PCH_COMPILE_DEFINITIONS "${PCH_COMPILE_DEFINITIONS}" )

list ( LENGTH PCH_FILE PCH_FILE_LENGTH )
if ( PCH_FILE_LENGTH GREATER 1 )
  message ( FATAL_ERROR "Precompiled headers list can contain only one header file!" )
endif()
if ( PCH_FILE AND DEFINED flagPCH )
  get_filename_component ( PCH_NAME ${PCH_FILE} NAME )
  set ( PCH_DIR ${PROJECT_PCH_DIR}/CtrlLib-lib )
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
      set_target_properties ( CtrlLib-lib PROPERTIES COMPILE_FLAGS "-Yu${PCH_NAME} -Fp${PCH_HEADER}.pch" )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "Yc${PCH_NAME} -Fp${PCH_HEADER}.pch" )
  endif()
  if ( PCH_INCLUDE_PARAMS )
      set_source_files_properties ( ${SOURCE_LIST_CPP} PROPERTIES COMPILE_FLAGS "${PCH_INCLUDE_PARAMS}" )
  endif()
endif()

