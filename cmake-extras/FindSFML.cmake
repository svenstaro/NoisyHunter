# Locate the SFML library
#
# This module defines
#  SFML_FOUND, if false, do not try to link to SFML
#  SFML_XXX_LIBRARY, library corresponding to the XXX component (release)
#  SFML_XXX_LIBRARY_DEBUG, library corresponding to the XXX component (debug)
#  SFML_LIBRARIES, list containing all the libraries corresponding to the requested components
#  SFML_INCLUDE_DIR, where to find SFML/Config.hpp
#
# By default, the dynamic libraries of SFML will be found. To find the static ones instead,
# you must set the SFML_STATIC_LIBRARIES variable to TRUE before calling find_package(SFML ...).

# deduce the SFML libraries prefix from the major version number
set(FIND_SFML_LIB_PREFIX "sfml-")
if(${SFML_FIND_VERSION_MAJOR} GREATER 1)
    set(FIND_SFML_LIB_PREFIX "sfml${SFML_FIND_VERSION_MAJOR}-")
endif()

# deduce the libraries suffix from the options
set(FIND_SFML_LIB_SUFFIX "")
if(SFML_STATIC_LIBRARIES)
    set(FIND_SFML_LIB_SUFFIX "${FIND_SFML_LIB_SUFFIX}-s")
endif()

# find the SFML include directory
find_path(SFML_INCLUDE_DIR SFML/Config.hpp
          PATH_SUFFIXES include
          PATHS
          ~/Library/Frameworks
          /Library/Frameworks
          /usr/local/
          /usr/
          /sw          # Fink
          /opt/local/  # DarwinPorts
          /opt/csw/    # Blastwave
          /opt/
          ${SFMLDIR})

# find the requested components
set(FIND_SFML_LIB_PATHS ~/Library/Frameworks
                        /Library/Frameworks
                        /usr/local
                        /usr
                        /sw
                        /opt/local
                        /opt/csw
                        /opt
                        ${SFMLDIR})
foreach(FIND_SFML_COMPONENT ${SFML_FIND_COMPONENTS})
    string(TOLOWER ${FIND_SFML_COMPONENT} FIND_SFML_COMPONENT_LOWER)
    string(TOUPPER ${FIND_SFML_COMPONENT} FIND_SFML_COMPONENT_UPPER)
    set(FIND_SFML_COMPONENT_VAR SFML_${FIND_SFML_COMPONENT_UPPER}_LIBRARY)
    set(FIND_SFML_COMPONENT_NAME ${FIND_SFML_LIB_PREFIX}${FIND_SFML_COMPONENT_LOWER}${FIND_SFML_LIB_SUFFIX})

    # release library
    find_library(${FIND_SFML_COMPONENT_VAR}
                 NAMES ${FIND_SFML_COMPONENT_NAME}
                 PATH_SUFFIXES lib64 lib
                 PATHS ${FIND_SFML_LIB_PATHS})

    # debug library
    find_library(${FIND_SFML_COMPONENT_VAR}_DEBUG
                 NAMES ${FIND_SFML_COMPONENT_NAME}-d
                 PATH_SUFFIXES lib64 lib
                 PATHS ${FIND_SFML_LIB_PATHS})

    set(SFML_LIBRARIES_NAMES ${SFML_LIBRARIES_NAMES} ${FIND_SFML_COMPONENT_VAR})
    set(SFML_LIBRARIES ${SFML_LIBRARIES} ${${FIND_SFML_COMPONENT_VAR}})
endforeach()

# handle the QUIETLY and REQUIRED arguments and set SFML_FOUND to TRUE if all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SFML DEFAULT_MSG SFML_INCLUDE_DIR ${SFML_LIBRARIES_NAMES})
MARK_AS_ADVANCED(SFML_INCLUDE_DIR ${SFML_LIBRARIES_NAMES})
