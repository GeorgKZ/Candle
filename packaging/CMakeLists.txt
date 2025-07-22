string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWERCASE)                 # The application id (no spaces, lowercase!)

#set(IDE_BUNDLE_IDENTIFIER "org.${PROJECT_NAME_LOWERCASE}")            # The macOS application bundle identifier.
#set(IDE_APP_ID "org.${PROJECT_NAME_LOWERCASE}")                       # The free desktop application identifier.
#set(IDE_PUBLISHER "Publisher.")
#set(IDE_AUTHOR "${IDE_PUBLISHER} and other contributors.")
#set(IDE_COPYRIGHT "Copyright (C) ${IDE_AUTHOR}")

# Absolute, or relative to /src/app
# Should contain candle.ico, candle.xcassets
set(IDE_ICON_PATH "")
# Absolute, or relative to /src/app
# Should contain images/logo/(16|24|32|48|64|128|256|512)/${PROJECT_NAME_LOWERCASE}.png
set(IDE_LOGO_PATH "")

##############################################################################
# Выбор типов установочных пакетов в зависимости от целевой среды выполнения
##############################################################################

# При сборке для работы в среде Linux
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")

    set(CPACK_GENERATOR
        "DEB"
    )
    set(CPACK_PACKAGING_INSTALL_PREFIX "/usr")

# При сборке для работы в среде MacOS/OS X
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")

    set(CPACK_GENERATOR
        # Bundle;DragNDrop
        "DragNDrop"
    )

    set(CPACK_PACKAGING_INSTALL_PREFIX "/")

# При сборке для работы в среде Windows
elseif ((CMAKE_SYSTEM_NAME STREQUAL "Windows") OR (CMAKE_SYSTEM_NAME STREQUAL "MSYS"))

    set(CPACK_GENERATOR
# Для IFW необходим binarycreator
# NSIS надо будет сделать
#       "IFW;NSIS;ZIP"
        "NSIS;ZIP"
    )
    set(CPACK_PACKAGING_INSTALL_PREFIX "")

else()
    message(WARNING "Неизвестная среда сборки " ${CMAKE_SYSTEM_NAME})
endif()

##############################################################################
# Настойки, общие для всех типов установочных пакетов
##############################################################################

# Имя для установочного пакета, по умолчанию PROJECT_NAME
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
# Имя поставщика
set(CPACK_PACKAGE_VENDOR "Vendor name")
# Директория, в которой будет производиться упаковка
set(CPACK_PACKAGE_DIRECTORY "${BUILD_PATH}/packaging")
# Версия упаковываемого приложения
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
# Описание приложения
set(CPACK_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})
# Краткое описание приложения
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
# Контактные данные поставщика установочного пакета
set(CPACK_PACKAGE_CONTACT "Maintainer <maintainer@mail.com>")
# Директория целевой среды выполненния, в которую будет выполнена установка
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME_LOWERCASE}-${CMAKE_PROJECT_VERSION})
# Лицензия, которая будет встроена в установочный пакет (для WIX необходимо расширение .txt)
file(CREATE_LINK
  ${CMAKE_SOURCE_DIR}/LICENSE
  ${MISC_PATH}/LICENSE.txt
  COPY_ON_ERROR)
set(CPACK_RESOURCE_FILE_LICENSE ${MISC_PATH}/LICENSE.txt)
# Файл ReadMe, который будет встроен в инсталлятор (для PRODUCTBUILD необходимо расширение .txt)
file(CREATE_LINK
  ${CMAKE_SOURCE_DIR}/readme.md
  ${MISC_PATH}/readme.txt
  COPY_ON_ERROR)
set(CPACK_RESOURCE_FILE_README ${MISC_PATH}/readme.txt)
#set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_SOURCE_DIR}/Description.txt)
#set(CPACK_RESOURCE_FILE_WELCOME ${CMAKE_SOURCE_DIR}/Welcome.txt)

# Переменные CPACK_... будут записаны в файлы конфигурации как есть, т.е.
# никакие управляющий символы не будут обработаны
set(CPACK_VERBATIM_VARIABLES YES)
# Количество потоков, которые будут задействованы при сжатии установщика
set(CPACK_THREADS 4)



# Make CMAKE_INSTALL_DEFAULT_COMPONENT_NAME the first component to install
#get_cmake_property(CPACK_COMPONENTS_ALL COMPONENTS)
#list(REMOVE_ITEM CPACK_COMPONENTS_ALL ${CMAKE_INSTALL_DEFAULT_COMPONENT_NAME})
#list(REMOVE_ITEM CPACK_COMPONENTS_ALL libraries) # empty component, breaks WIX
#list(REMOVE_ITEM CPACK_COMPONENTS_ALL DebugInfo) # exclude the huge debug info
#list(PREPEND CPACK_COMPONENTS_ALL ${CMAKE_INSTALL_DEFAULT_COMPONENT_NAME})

#set(CPACK_COMPONENT_Dependencies_HIDDEN TRUE)

#if (APPLE)
#  set(CPACK_INSTALL_PREFIX "/")
#endif()

if (NOT WIN32)
# устанавливать префикс пути установки автоматически
#  set(CPACK_SET_DESTDIR ON)
  set(CPACK_STRIP_FILES ON)

 # if (NOT APPLE)
 #   set(CPACK_INSTALL_CMAKE_PROJECTS
 #       "${CMAKE_BINARY_DIR};${PROJECT_NAME};ALL;/"
 #       "${CMAKE_BINARY_DIR};Dependencies;Dependencies;/"
 #   )
 # endif()
endif()

##############################################################################
# Специфичные для создания пакетов-архивов (.7z, .tar, .tar.bz2, .tar.gz,
# .tar.xz, .tar.Z, .tar.zst, .zip) настройки
# https://cmake.org/cmake/help/latest/cpack_gen/archive.html
##############################################################################

##############################################################################
# Специфичные для создания пакета Bundle настройки
# https://cmake.org/cmake/help/latest/cpack_gen/bundle.html
##############################################################################

# Имя пакета
set(CPACK_BUNDLE_NAME ${PROJECT_NAME})
# Файл Info.plist приложения
set(CPACK_BUNDLE_PLIST "${CMAKE_INSTALL_PREFIX}/candle.app/Contents/Info.plist")
# Значок прилжения
set(CPACK_BUNDLE_ICON "???")

##############################################################################
# Специфичные для создания пакета Cygwin настройки
# https://cmake.org/cmake/help/latest/cpack_gen/cygwin.html
##############################################################################

##############################################################################
# Специфичные для создания пакета Debian (.deb) настройки
# https://cmake.org/cmake/help/latest/cpack_gen/deb.html
##############################################################################

# Имя пакета Debian - обычно CPACK_PACKAGE_NAME в нижнем регистре
set(CPACK_DEBIAN_PACKAGE_NAME ${PROJECT_NAME_LOWERCASE})
# Архитектура целевого процессора
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
# Зависимости от других пакетов
#set(CPACK_DEBIAN_PACKAGE_DEPENDS "libdouble-conversion3,libxcb-cursor0")
# Обычно CPACK_PACKAGE_CONTACT
set(CPACK_DEBIAN_PACKAGE_MAINTAINER ${CPACK_PACKAGE_CONTACT})
# Описание пакета -  обычно CPACK_PACKAGE_DESCRIPTION_SUMMARY
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})
# Секция пакета (admin, cli-mono, comm, database, debug, devel, doc, editors, education,
# electronics, embedded, fonts, games, gnome, gnu-r, gnustep, graphics, hamradio, haskell,
# httpd, interpreters, introspection, java, javascript, kde, kernel, libdevel, libs, lisp,
# localization, mail, math, metapackages, misc, net, news, ocaml, oldlibs, otherosfs, perl,
# php, python, ruby, rust, science, shells, sound, tasks, tex, text, utils, vcs, video, web,
# x11, xfce, zope)
# По умолчанию разработка - devel
set(CPACK_DEBIAN_PACKAGE_SECTION devel)
# Приоритет установки (required, important, standard, optional, extra)
# По умолчанию необязательно - optional
set(CPACK_DEBIAN_PACKAGE_PRIORITY optional)

# Имя файла пакета Debian
#set(CPACK_DEBIAN_FILE_NAME ${PROJECT_NAME}.deb)
set(CPACK_DEBIAN_PACKAGE_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
set(CPACK_DEBIAN_PACKAGE_RELEASE 1)
set(CPACK_DEBIAN_COMPRESSION_ARCHIVE gnutar)
# Алгоритм сжатия пакета (lzma, xz, bzip2, gzip, zstd)
set(CPACK_DEBIAN_COMPRESSION_TYPE gzip)


##############################################################################
# Специфичные для создания пакета DragNDrop (.dmg) настройки
# https://cmake.org/cmake/help/latest/cpack_gen/dmg.html
##############################################################################

##############################################################################
# https://cmake.org/cmake/help/latest/cpack_gen/innosetup.html
##############################################################################

##############################################################################
# https://cmake.org/cmake/help/latest/cpack_gen/ifw.html
##############################################################################

##############################################################################
# Специфичные для создания пакета NSIS (.msi) настройки
# https://cmake.org/cmake/help/latest/cpack_gen/nsis.html
##############################################################################

# The default installation directory presented to the end user by the NSIS installer is under this root dir
set(CPACK_NSIS_INSTALL_ROOT "C:")
# Значок для установки пакета
set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/src/candle/images/candle.ico")
# Значок для удаления пакета
set(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/src/candle/images/candle.ico")

#set(CPACK_NSIS_INSTALLED_ICON_NAME "${IDE_APP_PATH}\\${IDE_APP_TARGET}.exe")
set(CPACK_NSIS_DISPLAY_NAME "${PROJECT_DESCRIPTION} ${CMAKE_PROJECT_VERSION}")
set(CPACK_NSIS_PACKAGE_NAME "${PROJECT_DESCRIPTION} ${CMAKE_PROJECT_VERSION}")
# Параметры, которые будут переданы архиватору
set(CPACK_NSIS_COMPRESSOR "/SOLID lzma\n  SetCompressorDictSize 64")
# Specify an executable to add an option to run on the finish page of the NSIS installer
#set(CPACK_NSIS_MUI_FINISHPAGE_RUN "${IDE_APP_TARGET}")
# Additional NSIS commands for creating Start Menu shortcuts
#set(CPACK_NSIS_CREATE_ICONS_EXTRA
#   "CreateShortCut '$SMPROGRAMS\\$STARTMENU_FOLDER\\${PROJECT_NAME} ${CMAKE_PROJECT_VERSION}.lnk' '$INSTDIR\\${IDE_APP_PATH}\\${IDE_APP_TARGET}.exe' "
#)
# if set, declares that the installer is DPI-aware
set(CPACK_NSIS_MANIFEST_DPI_AWARE ON)

##############################################################################
# https://cmake.org/cmake/help/latest/cpack_gen/nuget.html
##############################################################################

##############################################################################
# https://cmake.org/cmake/help/latest/cpack_gen/packagemaker.html
##############################################################################

##############################################################################
# https://cmake.org/cmake/help/latest/cpack_gen/productbuild.html
##############################################################################

##############################################################################
# Специфичные для создания пакета RPM (.rpm) настройки
# https://cmake.org/cmake/help/latest/cpack_gen/rpm.html
##############################################################################

# Обычно CPACK_PACKAGE_DESCRIPTION_SUMMARY
set(CPACK_RPM_PACKAGE_SUMMARY ${CPACK_PACKAGE_DESCRIPTION_SUMMARY})
# defaults to lower case of CPACK_PACKAGE_NAME
set(CPACK_RPM_PACKAGE_NAME ${PROJECT_NAME_LOWERCASE})
# Обычно of CPACK_PACKAGE_VERSION.
set(CPACK_RPM_PACKAGE_VERSION $CPACK_PACKAGE_VERSION})
# Архитектура целевого процессора
set(CPACK_RPM_PACKAGE_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
# Версия файла RPM
set(CPACK_RPM_PACKAGE_RELEASE "1")
#
set(CPACK_RPM_PACKAGE_GROUP "none")
#
set(CPACK_RPM_PACKAGE_VENDOR ${CPACK_PACKAGE_VENDOR})

##############################################################################
# Специфичные для создания пакета WIX (.msi) настройки
# https://cmake.org/cmake/help/latest/cpack_gen/wix.html
##############################################################################

set(CPACK_WIX_PRODUCT_ICON "${CMAKE_SOURCE_DIR}/src/candle/images/candle.ico")
set(CPACK_WIX_UPGRADE_GUID "E6A093A5-83DE-47FA-B669-1DE0102BE92A")
set(CPACK_WIX_LIGHT_EXTRA_FLAGS "-dcl:high") # set high compression

##############################################################################
# Подключить CPack из расширений CMake
##############################################################################

include(CPack)
