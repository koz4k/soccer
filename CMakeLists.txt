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

# Overwrite cmake verbose makefile output
# (e.g. do not generate cmake verbose makefile output even when the debug flag is set)
# not set - do not overwrite settings
# 0 - do not generate cmake verbose makefile output
# 1 - always generate cmake verbose makefile output
set ( CMAKE_VERBOSE_OVERWRITE  )

# Project name
project ( soccer )

# Set the project common path
set ( UPP_SOURCE_DIRECTORY . )
set ( UPP_EXTRA_INCLUDE  )
set ( PROJECT_INC_DIR ${PROJECT_BINARY_DIR}/inc )
set ( PROJECT_PCH_DIR ${PROJECT_BINARY_DIR}/pch )

# Set the default include directory for the whole project
include_directories ( BEFORE ${UPP_SOURCE_DIRECTORY} )
include_directories ( BEFORE ${PROJECT_INC_DIR} ${UPP_EXTRA_INCLUDE} )
include_directories ( BEFORE ${CMAKE_CURRENT_SOURCE_DIR} )

include_directories ( BEFORE ${CMAKE_SOURCE_DIR}/./soccer )

# Set the default path for built executables to the bin directory
set ( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )

# Project definitions
add_definitions ( -DflagGUI -DflagMT -DflagGCC -DflagLINUX -DflagPOSIX -DflagSHARED -DflagGNUC14 -DflagMP -DflagPCH )

# Read compiler definitions - used to set appropriate modules
get_directory_property ( FlagDefs COMPILE_DEFINITIONS )

# Platform flags settings
if ( WIN32 )
  remove_definitions( -DflagPOSIX )
  remove_definitions( -DflagLINUX )
  remove_definitions( -DflagFREEBSD )
  remove_definitions( -DflagSOLARIS )

  if ( NOT "${FlagDefs}" MATCHES "flagWIN32" )
    add_definitions ( -DflagWIN32 )
  endif()

else()
  remove_definitions( -DflagWIN32 )

  if ( NOT "${FlagDefs}" MATCHES "POSIX" )
    add_definitions ( -DflagPOSIX )
  endif()

  if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Linux" AND NOT "${FlagDefs}" MATCHES "flagLINUX" )
    add_definitions( -DflagLINUX )
  endif()

  if ( ${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD" AND NOT "${FlagDefs}" MATCHES "flagFREEBSD" )
    add_definitions( -DflagFREEBSD )
  endif()

  if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Solaris" AND NOT "${FlagDefs}" MATCHES "flagSOLARIS" )
    add_definitions( -DflagSOLARIS )
  endif()

endif()
get_directory_property ( FlagDefs COMPILE_DEFINITIONS )

# Set GCC builder flag
if ( CMAKE_COMPILER_IS_GNUCC )
  if ( "${FlagDefs}" MATCHES "flagGNUC14(;|$)" AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.9 )
    message ( FATAL_ERROR "GNU GCC version 4.9+ is required to use -std=c++14 parameter!" )
  endif()

  remove_definitions ( -DflagMSC )

  if ( NOT "${FlagDefs}" MATCHES "flagGCC(;|$)" )
    add_definitions( -DflagGCC )
  endif()

  get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
endif()

# Check supported compilation architecture environment
if ( "${FlagDefs}" MATCHES "flagGCC32" OR NOT CMAKE_SIZEOF_VOID_P EQUAL 8 )
  set ( STATUS_COMPILATION "32" )
  set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -m32" )
else()
  set ( STATUS_COMPILATION "64" )
  set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -m64" )
  set ( MSVC_ARCH "X64" )
endif()
message ( STATUS "Build compilation: ${STATUS_COMPILATION} bits" )

# Set MSVC builder flags
if ( MSVC )
  remove_definitions( -DflagGCC )

  if ( NOT "${FlagDefs}" MATCHES "flagUSEMALLOC(;|$)" )
    add_definitions ( -DflagUSEMALLOC )
  endif()

  if ( NOT "${FlagDefs}" MATCHES "flagMSC(;|$)" )
    add_definitions ( -DflagMSC )
  endif()

  if ( ${MSVC_VERSION} EQUAL 1200 )
      add_definitions ( -DflagMSC6${MSVC_ARCH} )
  endif()
  if ( ${MSVC_VERSION} EQUAL 1300 OR ${MSVC_VERSION} EQUAL 1310)
      add_definitions ( -DflagMSC7${MSVC_ARCH} )
      add_definitions ( -DflagMSC71${MSVC_ARCH} )
  endif()
  if ( ${MSVC_VERSION} EQUAL 1400 )
      add_definitions ( -DflagMSC8${MSVC_ARCH} )
  endif()
  if ( ${MSVC_VERSION} EQUAL 1500 )
      add_definitions ( -DflagMSC9${MSVC_ARCH} )
  endif()
  if ( ${MSVC_VERSION} EQUAL 1600 )
      add_definitions ( -DflagMSC10${MSVC_ARCH} )
  endif()
  if ( ${MSVC_VERSION} EQUAL 1700 )
      add_definitions ( -DflagMSC11${MSVC_ARCH} )
  endif()
  if ( ${MSVC_VERSION} EQUAL 1800 )
      add_definitions ( -DflagMSC12${MSVC_ARCH} )
  endif()
  if ( ${MSVC_VERSION} EQUAL 1900 )
      add_definitions ( -DflagMSC14${MSVC_ARCH} )
  endif()
  if ( ${MSVC_VERSION} EQUAL 1910 )
      add_definitions ( -DflagMSC15${MSVC_ARCH} )
  endif()

  if ( "${FlagDefs}" MATCHES "flagMP" AND NOT ${MSVC_VERSION} LESS 1400 )
    set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -MP" )
  endif()

  get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
endif()

# Set Intel builder flag
if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel" AND NOT "${FlagDefs}" MATCHES "flagINTEL" )
  add_definitions( -DflagINTEL )
  get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
endif()

# Set CLANG compiler flags
if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" )
  set ( CMAKE_COMPILER_IS_CLANG TRUE )
  set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -Wno-logical-op-parentheses" )
endif()

# Set link directories on BSD systems
if ( ${CMAKE_SYSTEM_NAME} MATCHES BSD )
    link_directories ( /usr/local/lib )
endif()

# Set debug/release compiler options
if ( "${FlagDefs}" MATCHES "flagDEBUG" )
  set ( CMAKE_VERBOSE_MAKEFILE 1 )
  set ( CMAKE_BUILD_TYPE DEBUG )
  add_definitions ( -D_DEBUG )

  set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -O0" )

  if ( NOT "${FlagDefs}" MATCHES "(flagDEBUG)(;|$)" )
      add_definitions ( -DflagDEBUG )
      get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
  endif()

  if ( MSVC )
      if ( "${FlagDefs}" MATCHES "flagMSC(8|9|10|11|12|14|15)" OR "${FlagDefs}" MATCHES "flagMSC(8|9|10|11|12|14|15)X64" )
          set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -debug -OPT:NOREF" )
      else()
          set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -incremental:yes -debug -OPT:NOREF" )
      endif()
  endif()

else()
  set ( CMAKE_VERBOSE_MAKEFILE 0 )
  set ( CMAKE_BUILD_TYPE RELEASE )
  add_definitions ( -D_RELEASE )

  set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -O3" )
  set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -GS-" )

  if ( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_CLANG )
      set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -ffunction-sections -fdata-sections" )
      set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-s,--gc-sections" )
  endif()

  if ( MSVC )
      if ( "${FlagDefs}" MATCHES "flagMSC(8|9|10|11|12|14|15)" OR "${FlagDefs}" MATCHES "flagMSC(8|9|10|11|12|14|15)X64" )
          set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -release -OPT:REF,ICF" )
      else()
          set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -incremental:no -release -OPT:REF,ICF" )
      endif()
  endif()

endif()
message ( STATUS "Build type: " ${CMAKE_BUILD_TYPE} )

if ( CMAKE_VERBOSE_OVERWRITE EQUAL 0 OR CMAKE_VERBOSE_OVERWRITE EQUAL 1 )
  set ( CMAKE_VERBOSE_MAKEFILE ${CMAKE_VERBOSE_OVERWRITE} )
endif()

if ( "${FlagDefs}" MATCHES "flagDEBUG_MINIMAL" )
  if ( NOT MINGW )
      set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -ggdb" )
  endif()
  set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -g1" )
  set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -Zd" )
endif()

if ( "${FlagDefs}" MATCHES "flagDEBUG_FULL" )
  if ( NOT MINGW )
      set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -ggdb" )
  endif()
  set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -g2" )
  set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -Zi" )
endif()

# Set static/shared compiler options
if ( "${FlagDefs}" MATCHES "(flagSO)(;|$)" )
  set ( BUILD_SHARED_LIBS ON )
  set ( LIB_TYPE SHARED )
  if ( NOT "${FlagDefs}" MATCHES "(flagSHARED)(;|$)" )
      add_definitions ( -DflagSHARED )
      get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
  endif()
endif()

if ( "${FlagDefs}" MATCHES "flagSHARED" )
  set ( STATUS_SHARED "TRUE" )
  set ( EXTRA_GXX_FLAGS "${EXTRA_GXX_FLAGS} -fuse-cxa-atexit" )
else()
  set ( STATUS_SHARED "FALSE" )
  set ( BUILD_SHARED_LIBS OFF )
  set ( LIB_TYPE STATIC )
  set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -static -fexceptions" )

  if ( MINGW )
      set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc" )
  endif()

endif()
message ( STATUS "Build with flagSHARED: ${STATUS_SHARED}" )

# Precompiled headers support
if ( "${FlagDefs}" MATCHES "flagPCH" )
  if ( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_CLANG )
    if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.4 )
        message ( WARNING
            "Precompiled headers are introduced with GCC 3.4.\n"
            "No support of the PCH in any earlier releases. (current version ${CMAKE_CXX_COMPILER_VERSION})." )
        remove_definitions ( -DflagPCH )
    endif()
    if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.5 )
        message ( WARNING
            "There are some problems with precompiled headers in Clang version less 3.5.\n"
            "No support of the PCH in any earlier releases. (current version ${CMAKE_CXX_COMPILER_VERSION})." )
        remove_definitions ( -DflagPCH )
    endif()
  else()
    remove_definitions ( -DflagPCH )
  endif()

  get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
endif()

if ( "${FlagDefs}" MATCHES "flagPCH" )
  message ( STATUS "Build with flagPCH: TRUE" )
else()
  message ( STATUS "Build with flagPCH: FALSE" )
endif()

# Main configuration flags (MT, GUI, DLL)
if ( "${FlagDefs}" MATCHES "flagMT" )
  find_package ( Threads REQUIRED )
  if ( THREADS_FOUND )
      include_directories ( ${THREADS_INCLUDE_DIRS} )
      list ( APPEND main_LINK_LIST ${THREADS_LIBRARIES} )
  endif()
endif()

# Set compiler options
if ( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_CLANG )
  if ( "${FlagDefs}" MATCHES "flagGNUC14" )
    set ( EXTRA_GXX_FLAGS "${EXTRA_GXX_FLAGS} -std=c++14" )
  endif()

  if ( CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.9 OR CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 4.9 OR CMAKE_COMPILER_IS_CLANG )
      set ( EXTRA_GXX_FLAGSS "${EXTRA_GXX_FLAGS} -fdiagnostics-color")
  endif()

  if ( MINGW )
      get_directory_property ( FlagDefs COMPILE_DEFINITIONS )

      set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -mwindows" )

      if ( "${FlagDefs}" MATCHES "flagDLL" )
          set ( BUILD_SHARED_LIBS ON )
          set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -shared" )
          string ( REGEX REPLACE "-static " "" CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} )
      endif()

      if ("${FlagDefs}" MATCHES "flagGUI" )
          list ( APPEND main_LINK_LIST mingw32 )
      else()
          set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -mconsole" )
      endif()

      if ( "${FlagDefs}" MATCHES "flagMT" )
          set ( EXTRA_GCC_FLAGS "${EXTRA_GCC_FLAGS} -mthreads" )
      endif()

      # The optimalization might be broken on MinGW - remove optimalization flag (cross compile).
      string ( REGEX REPLACE "-O3" "" EXTRA_GCC_FLAGS ${EXTRA_GCC_FLAGS} )

      get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
  endif()

  set ( CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_CXX_FLAGS_${BUILD_TYPE}} ${EXTRA_GXX_FLAGS} ${EXTRA_GCC_FLAGS}" )
  set ( CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_C_FLAGS_${BUILD_TYPE}} ${EXTRA_GCC_FLAGS}" )

  set ( CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> rs <TARGET> <LINK_FLAGS> <OBJECTS>" )
  set ( CMAKE_CXX_ARCHIVE_APPEND "<CMAKE_AR> rs <TARGET> <LINK_FLAGS> <OBJECTS>" )
  set ( CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> rs <TARGET> <LINK_FLAGS> <OBJECTS>" )
  set ( CMAKE_C_ARCHIVE_APPEND "<CMAKE_AR> rs <TARGET> <LINK_FLAGS> <OBJECTS>" )

elseif ( MSVC )
  get_directory_property ( FlagDefs COMPILE_DEFINITIONS )

  set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nologo" )

  if ( "${FlagDefs}" MATCHES "flagEVC" )
      if ( NOT "${FlagDefs}" MATCHES "flagSH3" AND  NOT "${FlagDefs}" MATCHES "flagSH4" )
          # disable stack checking
          set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -Gs8192" )
      endif()
      # read-only string pooling, turn off exception handling
      set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -GF -GX-" )
  elseif ( "${FlagDefs}" MATCHES "flagCLR" )
      set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -EHac" )
  elseif ( "${FlagDefs}" MATCHES "flagMSC(8|9|10|11|12|14|15)" OR "${FlagDefs}" MATCHES "flagMSC(8|9)ARM" OR "${FlagDefs}" MATCHES "flagMSC(8|9|10|11|12|14|15)X64" )
      set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -EHsc" )
  else()
      set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -GX" )
  endif()

  if ( ${CMAKE_BUILD_TYPE} STREQUAL DEBUG )
      set ( EXTRA_MSVC_FLAGS_Mx "d" )
  endif()
  if ( "${FlagDefs}" MATCHES "flagSHARED" OR "${FlagDefs}" MATCHES "flagCLR" )
      set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -MD${EXTRA_MSVC_FLAGS_Mx}" )
  else()
      if ( "${FlagDefs}" MATCHES "flagMT" OR "${FlagDefs}" MATCHES "flagMSC(8|9|10|11|12|14|15)" OR "${FlagDefs}" MATCHES "flagMSC(8|9)ARM" OR "${FlagDefs}" MATCHES "flagMSC(8|9|10|11|12|14|15)X64" )
          set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -MT${EXTRA_MSVC_FLAGS_Mx}" )
      else()
          set ( EXTRA_MSVC_FLAGS "${EXTRA_MSVC_FLAGS} -ML${EXTRA_MSVC_FLAGS_Mx}" )
      endif()
  endif()

  #,5.01 needed to support WindowsXP
  if ( NOT "${FlagDefs}" MATCHES "(flagMSC(8|9|10|11|12|14|15)X64)" )
      set ( MSVC_LINKER_SUBSYSTEM ",5.01" )
  endif()
  if ( "${FlagDefs}" MATCHES "flagMSC(8|9)ARM" )
      set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -subsystem:windowsce,4.20 /ARMPADCODE -NODEFAULTLIB:\"oldnames.lib\"" )
  else()
      if ( "${FlagDefs}" MATCHES "flagGUI" OR "${FlagDefs}" MATCHES "flagMSC(8|9)ARM" )
          set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -subsystem:windows${MSVC_LINKER_SUBSYSTEM}" )
      else()
          set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -subsystem:console${MSVC_LINKER_SUBSYSTEM}" )
      endif()
  endif()

  if ( "${FlagDefs}" MATCHES "flagDLL" )
      set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -dll" )
  endif()

  set ( CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_CXX_FLAGS_${BUILD_TYPE}} ${EXTRA_MSVC_FLAGS}" )
  set ( CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE} "${CMAKE_C_FLAGS_${BUILD_TYPE}} ${EXTRA_MSVC_FLAGS}" )
endif()

# Function to generate precompiled header
function ( generate_pch TARGET_NAME PCH_FILE PCH_INCLUDE_DIRS )
    set ( PCH_OUTPUT_DIR ${PROJECT_PCH_DIR}/${TARGET_NAME} )
    get_filename_component ( PCH_NAME ${PCH_FILE} NAME )
    get_filename_component ( TARGET_DIR ${PCH_FILE} PATH )

    file ( COPY ${PCH_FILE} DESTINATION ${PCH_OUTPUT_DIR} )

    # Prepare compile flag definition
    get_target_property ( COMPILE_FLAGS_LIST ${TARGET_NAME} COMPILE_FLAGS_LIST )
    string ( REGEX REPLACE ";" " " COMPILE_FLAGS_LIST "${COMPILE_FLAGS_LIST}" )
    set ( compile_flags "${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}} ${COMPILE_FLAGS_LIST}" )

    # Add main target defined include directories
    get_directory_property ( include_directories DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} INCLUDE_DIRECTORIES )
    foreach ( include_dir ${include_directories} )
        list ( APPEND compile_flags "-I${include_dir}" )
    endforeach()

    # Add source directory of the precompiled header file - for quoted include files
    list ( APPEND compile_flags "-iquote${TARGET_DIR}" )

    # Add included directories of the external packages collected from defintions of all targets
    foreach ( include_dir ${PCH_INCLUDE_DIRS} )
        list ( APPEND compile_flags "-I${include_dir}" )
    endforeach()

    # Add target compile definitions
    get_target_property ( PCH_COMPILE_DEFINITIONS ${TARGET_NAME} PCH_COMPILE_DEFINITIONS )
    foreach ( compile_def ${PCH_COMPILE_DEFINITIONS} )
        list ( APPEND compile_flags "-D${compile_def}" )
    endforeach()

    list ( REMOVE_DUPLICATES compile_flags )
    separate_arguments ( compile_flags )

    # Prepare compilations options
    set ( PCH_BINARY_SUFFIX ".pch" )
    if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" )
        set ( PCH_BINARY_SUFFIX ".gch" )
    endif()

    set ( PCH_HEADER "${PCH_OUTPUT_DIR}/${PCH_NAME}" )
    set ( PCH_BINARY "${PCH_HEADER}${PCH_BINARY_SUFFIX}" )
    set ( PCH_COMPILE_PARAMS -x c++-header -o ${PCH_BINARY} ${PCH_HEADER} )

    # Generate precompiled header file
    add_custom_command ( OUTPUT ${PCH_BINARY}
        COMMAND ${CMAKE_CXX_COMPILER} ${compile_flags} ${PCH_COMPILE_PARAMS}
        COMMENT "PCH for the file ${PCH_HEADER}"
    )

    add_custom_target ( ${TARGET_NAME}_gch DEPENDS ${PCH_BINARY} )
    add_dependencies ( ${TARGET_NAME} ${TARGET_NAME}_gch )
endfunction()

# Function to create cpp source from icpp files
function ( create_cpps_from_icpps )
  file ( GLOB icpp_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*.icpp" )
  foreach ( icppFile ${icpp_files} )
      set ( output_file "${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}/${icppFile}.cpp" )
      file ( WRITE "${output_file}" "#include \"${CMAKE_CURRENT_SOURCE_DIR}/${icppFile}\"\n" )
  endforeach()
endfunction()

# Function to create cpp source file from binary resource definition
function ( create_brc_source input_file output_file symbol_name compression symbol_append )
  if ( NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${input_file} )
      message ( FATAL_ERROR "Input file does not exist: ${CMAKE_CURRENT_SOURCE_DIR}/${input_file}" )
  endif()
  message ( STATUS "Creating cpp source file \"${output_file}\" from the binary resource \"${input_file}\"" )

  file ( REMOVE ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name} )

  if ( ${compression} MATCHES "[bB][zZ]2" )
      find_program ( BZIP2_EXEC bzip2 )
      if ( NOT BZIP2_EXEC )
          message ( FATAL_ERROR "BZIP2 executable not found!" )
      endif()
      set ( COMPRESS_SUFFIX "bz2" )
      set ( COMMAND_COMPRESS ${BZIP2_EXEC} -k -f ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name} )
  elseif ( ${compression} MATCHES "[zZ][iI][pP]" )
      find_program ( ZIP_EXEC zip )
      if ( NOT ZIP_EXEC )
          message ( FATAL_ERROR "ZIP executable not found!" )
      endif()
      set ( COMPRESS_SUFFIX "zip" )
      set ( COMMAND_COMPRESS ${ZIP_EXEC} ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name}.${COMPRESS_SUFFIX} ${symbol_name} )
  elseif ( ${compression} MATCHES "[lL][zZ][mM][aA]" )
      find_program ( LZMA_EXEC lzma )
      if ( NOT LZMA_EXEC )
          message ( FATAL_ERROR "LZMA executable not found!" )
      endif()
      set ( COMPRESS_SUFFIX "lzma" )
      set ( COMMAND_COMPRESS ${LZMA_EXEC} ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name} )
  elseif ( ${compression} MATCHES "[lL][zZ]4" )
      find_program ( LZ4_EXEC lz4c )
      if ( NOT LZ4_EXEC )
          message ( FATAL_ERROR "LZ4 executable not found!" )
      endif()
      set ( COMPRESS_SUFFIX "lz4" )
      set ( COMMAND_COMPRESS ${LZ4_EXEC} -f ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name} ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name}.${COMPRESS_SUFFIX} )
  elseif ( ${compression} MATCHES "[zZ][sS][tT[dD]" )
      find_program ( ZSTD_EXEC zstd )
      if ( NOT ZSTD_EXEC )
          message ( FATAL_ERROR "ZSTD executable not found!" )
      endif()
      set ( COMPRESS_SUFFIX "zst" )
      set ( COMMAND_COMPRESS ${ZSTD_EXEC} ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name} -o ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name}.${COMPRESS_SUFFIX} )
  endif()

  file ( COPY ${CMAKE_CURRENT_SOURCE_DIR}/${input_file} DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
  get_filename_component ( input_file_name ${CMAKE_CURRENT_SOURCE_DIR}/${input_file} NAME )
  file ( RENAME ${CMAKE_CURRENT_BINARY_DIR}/${input_file_name} ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name} )
  if ( COMMAND_COMPRESS )
      execute_process ( COMMAND ${COMMAND_COMPRESS} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} OUTPUT_VARIABLE XXXX )
      file ( RENAME ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name}.${COMPRESS_SUFFIX} ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name} )
  endif()

  file ( READ ${CMAKE_CURRENT_BINARY_DIR}/${symbol_name} hex_string HEX )

  set ( CUR_INDEX 0 )
  string ( LENGTH "${hex_string}" CUR_LENGTH )
  math ( EXPR FILE_LENGTH "${CUR_LENGTH} / 2" )
  set ( ${hex_string} 0)

  string ( REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1, " hex_converted ${hex_string} )

  set ( output_string "static unsigned char ${symbol_name}_[] = {\n" )
  set ( output_string "${output_string} ${hex_converted}0x00 }\;\n\n" )
  set ( output_string "${output_string}unsigned char *${symbol_name} = ${symbol_name}_\;\n\n" )
  set ( output_string "${output_string}int ${symbol_name}_length = ${FILE_LENGTH}\;\n\n" )

  if ( ${symbol_append} MATCHES "append" )
      file ( APPEND ${CMAKE_CURRENT_BINARY_DIR}/${output_file} ${output_string} )
  else()
      file ( WRITE ${CMAKE_CURRENT_BINARY_DIR}/${output_file} ${output_string} )
  endif()
endfunction()

# Initialize definition flags (flags are used during targets compilation)
get_directory_property ( FlagDefs COMPILE_DEFINITIONS )
foreach( comp_def ${FlagDefs} )
  message ( STATUS "  initialize flag " ${comp_def} )
  set ( ${comp_def} 1 )
endforeach()

# Include dependent directories of the project
add_subdirectory ( ./CtrlLib ${CMAKE_CURRENT_BINARY_DIR}/CtrlLib )
add_subdirectory ( ./CtrlCore ${CMAKE_CURRENT_BINARY_DIR}/CtrlCore )
add_subdirectory ( ./PdfDraw ${CMAKE_CURRENT_BINARY_DIR}/PdfDraw )
add_subdirectory ( ./Draw ${CMAKE_CURRENT_BINARY_DIR}/Draw )
add_subdirectory ( ./plugin/bmp ${CMAKE_CURRENT_BINARY_DIR}/plugin/bmp )
add_subdirectory ( ./RichText ${CMAKE_CURRENT_BINARY_DIR}/RichText )
add_subdirectory ( ./Core ${CMAKE_CURRENT_BINARY_DIR}/Core )
add_subdirectory ( ./plugin/png ${CMAKE_CURRENT_BINARY_DIR}/plugin/png )
add_subdirectory ( ./plugin/z ${CMAKE_CURRENT_BINARY_DIR}/plugin/z )
add_subdirectory ( ./soccer ${CMAKE_CURRENT_BINARY_DIR}/soccer )

# Creation of the file build_info.h
set ( BUILD_INFO_H ${PROJECT_INC_DIR}/build_info.h )
string ( TIMESTAMP bmYEAR %Y )
string ( TIMESTAMP bmMONTH %m )
string ( TIMESTAMP bmDAY %d )
string ( TIMESTAMP bmHOUR %H )
string ( TIMESTAMP bmMINUTE %M )
string ( TIMESTAMP bmSECOND %S )
string ( REGEX REPLACE "^0(.*)" \\1 bmMONTH ${bmMONTH} )
string ( REGEX REPLACE "^0(.*)" \\1 bmDAY ${bmDAY} )
string ( REGEX REPLACE "^0(.*)" \\1 bmHOUR ${bmHOUR} )
string ( REGEX REPLACE "^0(.*)" \\1 bmMINUTE ${bmMINUTE} )
string ( REGEX REPLACE "^0(.*)" \\1 bmSECOND ${bmSECOND} )
cmake_host_system_information ( RESULT bmHOSTNAME QUERY HOSTNAME )
file ( WRITE  ${BUILD_INFO_H} "#define bmYEAR ${bmYEAR}\n#define bmMONTH ${bmMONTH}\n#define bmDAY ${bmDAY}\n" )
file ( APPEND ${BUILD_INFO_H} "#define bmHOUR ${bmHOUR}\n#define bmMINUTE ${bmMINUTE}\n#define bmSECOND ${bmSECOND}\n" )
file ( APPEND ${BUILD_INFO_H} "#define bmTIME Time(${bmYEAR}, ${bmMONTH}, ${bmDAY}, ${bmHOUR}, ${bmMINUTE}, ${bmSECOND})\n" )
file ( APPEND ${BUILD_INFO_H} "#define bmMACHINE \"${bmHOSTNAME}\"\n" )
if ( WIN32 )
  file ( APPEND ${BUILD_INFO_H} "#define bmUSER \"$ENV{USERNAME}\"\n" )
else()
  file ( APPEND ${BUILD_INFO_H} "#define bmUSER \"$ENV{USER}\"\n" )
endif()

# Collect icpp files
file ( GLOB_RECURSE cpp_ini_files "${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}/*.icpp.cpp" )

# Collect windows resource config file
if ( WIN32 )
  file ( GLOB rc_file "${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}/*.rc" )
endif()

# Main program definition
file ( WRITE ${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}/null.cpp "" )
if ( "${FlagDefs}" MATCHES "(flagSO)(;|$)" )
  add_library ( soccer-bin ${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}/null.cpp ${rc_file} ${cpp_ini_files} )
  if ( WIN32 )
    include ( GenerateExportHeader )
    generate_export_header ( soccer-bin
        BASE_NAME soccer-bin
        EXPORT_MACRO_NAME soccer-bin_EXPORT
        EXPORT_FILE_NAME soccer-bin_Export.h
        STATIC_DEFINE soccer-bin_BUILT_AS_STATIC
    )
  endif()
else()
  add_executable ( soccer-bin ${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}/null.cpp ${rc_file} ${cpp_ini_files} )
endif()

# Main program dependecies
set ( soccer_DEPEND_LIST "soccer-lib;Core-lib;CtrlCore-lib;CtrlLib-lib;Draw-lib;PdfDraw-lib;plugin_bmp-lib;plugin_png-lib;plugin_z-lib;RichText-lib;" )

add_dependencies ( soccer-bin ${soccer_DEPEND_LIST} )
if ( DEFINED MAIN_TARGET_LINK_FLAGS )
  set_target_properties ( soccer-bin PROPERTIES LINK_FLAGS ${MAIN_TARGET_LINK_FLAGS} )
endif()

# Precompiled headers processing
if ( "${FlagDefs}" MATCHES "flagPCH" )
  if ( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_CLANG )
    # Collect included directories of the external packages from all targets
    foreach ( target ${soccer_DEPEND_LIST} )
        get_target_property ( PCH_INCLUDE_LIST ${target} PCH_INCLUDE_LIST )
        list ( APPEND PCH_INCLUDE_DIRS ${PCH_INCLUDE_LIST} )
    endforeach()
    if ( PCH_INCLUDE_DIRS )
        list ( REMOVE_DUPLICATES PCH_INCLUDE_DIRS )
    endif()

    foreach ( target ${soccer_DEPEND_LIST} )
        get_target_property ( PCH_FILE ${target} PCH_FILE )
        if ( PCH_FILE )
            generate_pch ( ${target} ${PCH_FILE} "${PCH_INCLUDE_DIRS}" )
        endif()
    endforeach()
  endif()
endif()

# Main program link
target_link_libraries ( soccer-bin ${main_LINK_LIST} ${soccer_DEPEND_LIST} )
set_target_properties ( soccer-bin PROPERTIES OUTPUT_NAME soccer )
