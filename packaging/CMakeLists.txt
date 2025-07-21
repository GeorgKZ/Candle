#include(${CMAKE_CURRENT_LIST_DIR}/../cmake/QtCreatorIDEBranding.cmake)
set(IDE_VERSION "17.0.82")                            # The IDE version.
set(IDE_VERSION_COMPAT "17.0.82")                     # The IDE Compatibility version.
set(IDE_VERSION_DISPLAY "18.0.0-beta1")               # The IDE display version.

set(IDE_SETTINGSVARIANT "QtProject")                  # The IDE settings variation.
set(IDE_DISPLAY_NAME "Qt Creator")                    # The IDE display name.
set(IDE_ID "qtcreator")                               # The IDE id (no spaces, lowercase!)
set(IDE_CASED_ID "QtCreator")                         # The cased IDE id (no spaces!)
set(IDE_BUNDLE_IDENTIFIER "org.qt-project.${IDE_ID}") # The macOS application bundle identifier.
set(IDE_APP_ID "org.qt-project.${IDE_ID}")            # The free desktop application identifier.
set(IDE_PUBLISHER "The Qt Company Ltd.")
set(IDE_AUTHOR "${IDE_PUBLISHER} and other contributors.")
set(IDE_COPYRIGHT "Copyright (C) ${IDE_AUTHOR}")

set(PROJECT_USER_FILE_EXTENSION .user)
#set(IDE_DOC_FILE "qtcreator/qtcreator.qdocconf")
#set(IDE_DOC_FILE_ONLINE "qtcreator/qtcreator-online.qdocconf")

# Absolute, or relative to <qtcreator>/src/app
# Should contain qtcreator.ico, qtcreator.xcassets
set(IDE_ICON_PATH "")
# Absolute, or relative to <qtcreator>/src/app
# Should contain images/logo/(16|24|32|48|64|128|256|512)/QtProject-${IDE_ID}.png
set(IDE_LOGO_PATH "")




set(CPACK_PACKAGE_NAME ${IDE_CASED_ID})
set(CPACK_PACKAGE_VENDOR "The Qt Company Ltd")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${IDE_DISPLAY_NAME})
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${IDE_ID})
set(CPACK_VERBATIM_VARIABLES YES)

#set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_LIST_DIR}/Description.txt)
#set(CPACK_RESOURCE_FILE_WELCOME ${CMAKE_CURRENT_LIST_DIR}/Welcome.txt)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/../readme.md)

# WIX needs a license file ending with .txt
file(CREATE_LINK
  ${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE
  COPY_ON_ERROR)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE)

set(CPACK_PACKAGE_CONTACT "None")
set(CPACK_THREADS 4)
set(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
set(CPACK_DEBIAN_COMPRESSION_TYPE lzma)
set(CPACK_DEBIAN_PACKAGE_RELEASE 1)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Qt Project <qt-creator@qt-project.org>")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libdouble-conversion3,libxcb-cursor0")

# Make CMAKE_INSTALL_DEFAULT_COMPONENT_NAME the first component to install
get_cmake_property(CPACK_COMPONENTS_ALL COMPONENTS)
list(REMOVE_ITEM CPACK_COMPONENTS_ALL ${CMAKE_INSTALL_DEFAULT_COMPONENT_NAME})
list(REMOVE_ITEM CPACK_COMPONENTS_ALL libraries) # empty component, breaks WIX
list(REMOVE_ITEM CPACK_COMPONENTS_ALL DebugInfo) # exclude the huge debug info
list(PREPEND CPACK_COMPONENTS_ALL ${CMAKE_INSTALL_DEFAULT_COMPONENT_NAME})

set(CPACK_COMPONENT_Dependencies_HIDDEN TRUE)

if (APPLE)
  set(CPACK_INSTALL_PREFIX "/")
endif()

if (WIN32)
  set(CPACK_PACKAGE_INSTALL_DIRECTORY ${IDE_ID}-${CMAKE_PROJECT_VERSION})
else()
  set(CPACK_SET_DESTDIR ON)
  set(CPACK_STRIP_FILES ON)

  if (NOT APPLE)
    set(CPACK_INSTALL_CMAKE_PROJECTS
        "${CMAKE_BINARY_DIR};${IDE_CASED_ID};ALL;/"
        "${CMAKE_BINARY_DIR};Dependencies;Dependencies;/"
    )
  endif()
endif()

# NSIS-specific configuration
set(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/../src/candle/images/candle.ico")
set(CPACK_NSIS_MUI_UNIICON "${CMAKE_CURRENT_SOURCE_DIR}/../src/candle/images/candle.ico")
set(CPACK_NSIS_INSTALLED_ICON_NAME "${IDE_APP_PATH}\\${IDE_APP_TARGET}.exe")
set(CPACK_NSIS_DISPLAY_NAME "${IDE_DISPLAY_NAME} ${CMAKE_PROJECT_VERSION}")
set(CPACK_NSIS_PACKAGE_NAME "${IDE_DISPLAY_NAME} ${CMAKE_PROJECT_VERSION}")
set(CPACK_NSIS_COMPRESSOR "/SOLID lzma\n  SetCompressorDictSize 64")
#set(CPACK_NSIS_INSTALL_ROOT "C:\\Qt")
set(CPACK_NSIS_MUI_FINISHPAGE_RUN "${IDE_APP_TARGET}")
set(CPACK_NSIS_CREATE_ICONS_EXTRA
   "CreateShortCut '$SMPROGRAMS\\$STARTMENU_FOLDER\\${IDE_DISPLAY_NAME} ${CMAKE_PROJECT_VERSION}.lnk' '$INSTDIR\\${IDE_APP_PATH}\\${IDE_APP_TARGET}.exe' "
)
set(CPACK_NSIS_MANIFEST_DPI_AWARE ON)

# WIX-specific configuration
set(CPACK_WIX_PRODUCT_ICON "${CMAKE_CURRENT_SOURCE_DIR}/../src/candle/images/candle.ico")
set(CPACK_WIX_UPGRADE_GUID "E6A093A5-83DE-47FA-B669-1DE0102BE92A")
set(CPACK_WIX_LIGHT_EXTRA_FLAGS "-dcl:high") # set high compression

include(CPack)
