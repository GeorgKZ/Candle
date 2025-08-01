##############################################################################
# Минимально необходимая для нормальной работы версия cmake, Qt
##############################################################################

cmake_minimum_required(VERSION 3.9...3.28)

##############################################################################
# Установки, которые необходимо выполнить до директивы project(...)
##############################################################################

# Директория для промежуточных и собранных файлов
if(DEFINED ENV{BUILDDIR}) 
    message(DEBUG "Для определения местоположения директории сборки использована переменная окружения BUILDDIR: $ENV{BUILDDIR}")
    cmake_path(SET BUILD_PATH NORMALIZE "$ENV{BUILDDIR}")
else()
    set(BUILD_PATH "${CMAKE_BINARY_DIR}/build")
endif()

# Директория для установочного набора
set(CMAKE_INSTALL_PREFIX "${BUILD_PATH}/install" CACHE PATH "Install path prefix, prepended onto install directories.")


##############################################################################
# Информация о проекте
##############################################################################

project(Candle
    VERSION 1.2.15.1
    DESCRIPTION "GRBL controller application with G-Code visualizer"
    LANGUAGES CXX
)

##############################################################################
# Установки, которые необходимо выполнить до поиска Qt
##############################################################################

# При сборке для работы в среде Linux
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")

    # Путь, где искать динамические библиотеки
    set(CMAKE_INSTALL_LIBDIR "lib/candle"
      CACHE  PATH "Object code libraries (lib)"
    )
    set(CMAKE_INSTALL_BINDIR "bin"
      CACHE  PATH "User executables (bin)"
    )

# При сборке для работы в среде MacOS/OS X
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")

    set(CMAKE_INSTALL_LIBDIR "candle.app/Contents/Resources"
      CACHE PATH "Object code libraries (lib)"
    )
    set(CMAKE_INSTALL_BINDIR "candle.app/Contents/MacOS"
      CACHE  PATH "User executables (bin)"
    )

# При сборке для работы в среде Windows
elseif ((CMAKE_SYSTEM_NAME STREQUAL "Windows") OR (CMAKE_SYSTEM_NAME STREQUAL "MSYS"))

else()
    message(WARNING "Неизвестная среда сборки " ${CMAKE_SYSTEM_NAME})
endif()


##############################################################################
# Настройка местоположения Qt
##############################################################################

if(DEFINED ENV{QT_ROOT})
    message(DEBUG "Для определения местоположения Qt использована переменная окружения QT_ROOT: $ENV{QT_ROOT}")
    # Эти переменные должны указывать на директорию, в которой расположен файл Qt6Config.cmake,
    # например /opt/qt691/lib/cmake/Qt6/
    set(QT_DIR  "$ENV{QT_ROOT}/lib/cmake/Qt6/" CACHE PATH "The directory containing a CMake configuration file for QT.")
    set(Qt6_DIR "$ENV{QT_ROOT}/lib/cmake/Qt6/" CACHE PATH "The directory containing a CMake configuration file for Qt6.")
    # Эта переменная должна указывать на установочную директорию Qt
    set(CMAKE_PREFIX_PATH "$ENV{QT_ROOT}")
    find_package(QT NAMES Qt6 COMPONENTS Core REQUIRED)
    find_package(Qt6 COMPONENTS Core REQUIRED)
    # Получить путь к библиотеке libQt6Core, например /opt/qt691/lib/libQt6Core.so.6.9.1
    get_target_property(QtCore_location Qt6::Core LOCATION)
    message(DEBUG "Qt6 libQt6Core location: ${QtCore_location}")
else()
    find_package(QT NAMES Qt6 COMPONENTS Core REQUIRED)
    find_package(Qt6 COMPONENTS Core REQUIRED)
    # Получить путь к библиотеке libQt6Core, например /usr/lib/x86_64-linux-gnu/libQt6Core.so.6.4.2
    get_target_property(QtCore_location Qt6::Core LOCATION)
    message(DEBUG "Qt6 libQt6Core location: ${QtCore_location}")
    # Получить из этого пути директорию, в которой расположен файл Qt6Config.cmake,
    # например /usr/lib/x86_64-linux-gnu/cmake/Qt6, и присвоить полченное значение
    # переменным QT_DIR, Qt6_DIR
    cmake_path(GET QtCore_location ROOT_DIRECTORY QtCore_path)
    set(QT_DIR  "$ENV{QtCore_path}/lib/cmake/Qt6/" CACHE PATH "The directory containing a CMake configuration file for QT.")
    set(Qt6_DIR "$ENV{QtCore_path}/lib/cmake/Qt6/" CACHE PATH "The directory containing a CMake configuration file for Qt6.")
endif()

##############################################################################
# Директории, создаваемые для выполнения сборки
##############################################################################

# Директория для результирующих бинарных файлов
set(BIN_PATH "${BUILD_PATH}/bin")
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${BIN_PATH})

# Директория для промежуточных файлов
set(MISC_PATH "${BUILD_PATH}/misc")
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${MISC_PATH})

# Директория для файлов с изображениями значка
set(ICONS_PATH "${BUILD_PATH}/icons")
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${ICONS_PATH})

# Директория для документации приложения
set(DOC_PATH "${BUILD_PATH}/docs")
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${DOC_PATH})

# Директория для собираемых бинарных файлов сборки установочного набора
#!!! Потом убрать DEST_PATH
#if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
#    # При сборке для работы в среде MacOS/OS X
#    set(DEST_PATH "${CMAKE_INSTALL_PREFIX}/candle.app/Contents/MacOS")
#else()
#    set(DEST_PATH "${CMAKE_INSTALL_PREFIX}")
#endif()
#execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${DEST_PATH})
#execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${DEST_PATH}/candle_plugins)

# Путь к директории с изображениями для Doxygen
set(DOXY_IMAGES "${CMAKE_SOURCE_DIR}/screenshots;${CMAKE_SOURCE_DIR}/doc/images;${CMAKE_SOURCE_DIR}/wiki/images")
# Путь к директории с переводами
set(TRANSLATE_PATH "${BUILD_PATH}/translations")
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${TRANSLATE_PATH})

##############################################################################
# Пути к файлам lupdate, lrelease
##############################################################################

if ((CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux") OR CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")

    # Исполняемый файл lupdate
    if(EXISTS "/usr/lib/qt6/bin/lupdate")
        set(LUPDATE_CMD "/usr/lib/qt6/bin/lupdate")
    elseif(EXISTS "${QT_DIR}/../../../bin/lupdate")
        set(LUPDATE_CMD "${QT_DIR}/../../../bin/lupdate")
    else()
        set(LUPDATE_CMD "lupdate")
    endif()

    # Исполняемый файл lrelease
    if(EXISTS "/usr/lib/qt6/bin/lrelease")
        set(LRELEASE_CMD "/usr/lib/qt6/bin/lrelease")
    elseif(EXISTS "${QT_DIR}/../../../bin/lrelease")
        set(LRELEASE_CMD "${QT_DIR}/../../../bin/lrelease")
    else()
        set(LUPDATE_CMD "lrelease")
    endif()

elseif (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")

    # Исполняемый файл lupdate
    if(EXISTS "${QT_DIR}/../../../bin/lupdate.exe")
        set(LUPDATE_CMD "${QT_DIR}/../../../bin/lupdate.exe")
    else()
        set(LUPDATE_CMD "lupdate.exe")
    endif()

    # Исполняемый файл lrelease
    if(EXISTS "${QT_DIR}/../../../bin/lrelease.exe")
        set(LRELEASE_CMD "${QT_DIR}/../../../bin/lrelease.exe")
    else()
        set(LRELEASE_CMD "lrelease.exe")
    endif()

endif()

##############################################################################
# Определение битности исполняемого файла
##############################################################################

if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
    set(BIT_WIDTH "64")
elseif("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    set(BIT_WIDTH "32")
else()
    message(WARNING "Неизвестная битность исполняемого файла - ${CMAKE_SIZEOF_VOID_P} байт")
endif()

##############################################################################
# Настройка в зависимости от среды сборки
##############################################################################

if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")

# Команда перенаправления потока в нуль
    set(CMD_TO_NUL >/dev/null 2>&1)
# Команда удаления файла warnings.log нулевой длины
    set(CMD_CLN_WARN find warnings.log -size 0 | xargs rm -f)
# Командный файл для запуска pdflatex с параметром
    set(CMD_RUN_LATEX "${MISC_PATH}/runlatex.sh")
# Подготовить командный файл для запуска pdflatex с параметром
    file(WRITE ${CMD_RUN_LATEX} "#!/bin/bash\n\npdflatex --shell-escape $1")
    execute_process(COMMAND chmod +x ${CMD_RUN_LATEX})

elseif (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")

# Команда перенаправления потока в нуль
    set(CMD_TO_NUL >NUL 2>&1)
# Команда удаления файла warnings.log нулевой длины
    set(CMD_CLN_WARN FOR %A in ( warnings.log ) DO @IF %~zA EQU 0 DEL warnings.log)

elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")

# Команда перенаправления потока в нуль
    set(CMD_TO_NUL >/dev/null 2>&1)
# Команда удаления файла warnings.log нулевой длины
    set(CMD_CLN_WARN find warnings.log -size 0 | xargs rm -f)
# Командный файл для запуска pdflatex с параметром
    set(CMD_RUN_LATEX "${MISC_PATH}/runlatex.sh")
# Подготовить командный файл для запуска pdflatex с параметром
    file(WRITE ${CMD_RUN_LATEX} "#!/bin/zsh\n\npdflatex --shell-escape $1")
    execute_process(COMMAND chmod +x ${CMD_RUN_LATEX})

else()
    message(WARNING "Неизвестная среда сборки ${CMAKE_HOST_SYSTEM_NAME}")
endif()

##############################################################################
# Настройка в зависимости от используемого компилятора.
##############################################################################

# Требуемая версия компилятора C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# clang
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

    message(DEBUG "Определён компилятор Clang")

    add_compile_options(
#        "-Wall"
#        "-Wpedantic"
#        "-Wextra"
#        "-Wunused-but-set-variable"
        "-Weverything"
    )
    add_definitions(
        "-D__CLANG__"
        "-D__MYFUNCNAME__=__PRETTY_FUNCTION__"  #!!! Проверить на linux, windows!!!
    )
    # Обрезать таблицы символов для Release
    add_link_options(
        $<$<CONFIG:RELEASE>:-s>
    )
    # Обрезать таблицы символов для MinSizeRel
    add_link_options(
        $<$<CONFIG:MINSIZEREL>:-s>
    )
# clang из MacOX/OS X
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")

    message(DEBUG "Определён компилятор AppleClang")


    add_compile_options(
#        "-Wall"
#        "-Wpedantic"
#        "-Wextra"
#        "-Wunused-but-set-variable"
        "-Weverything"
        "-Wno-padded"
        "-Wno-c++98-compat"
        "-Wno-c++98-compat-pedantic"
        "-Wno-documentation-unknown-command"
        "-Wno-poison-system-directories"
        "-Wno-global-constructors"
        "-Wno-ctad-maybe-unsupported"

        # Временно
        "-Wno-implicit-float-conversion"
        "-Wno-implicit-int-conversion"
        "-Wno-float-conversion"
        "-Wno-double-promotion"
        "-Wno-float-equal"
        "-Wno-shorten-64-to-32"
        "-Wno-old-style-cast"
        "-Wno-sign-conversion"
        "-Wno-exit-time-destructors"
    )
    add_definitions(
        "-D__CLANG__"
        "-D__MYFUNCNAME__=__PRETTY_FUNCTION__"  #!!! Проверить на MacOS!!!
    )
    # Обрезать таблицы символов для Release
    add_link_options(
        $<$<CONFIG:RELEASE>:-s>
    )
    # Обрезать таблицы символов для MinSizeRel
    add_link_options(
        $<$<CONFIG:MINSIZEREL>:-s>
    )

# gcc
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

    message(DEBUG "Определён компилятор GNU gcc")

    # Подготовить командный файл для получения списка всех предупреждений компилятора
    set(CMD_GEN_WARN "${MISC_PATH}/gen_gcc_warn.sh")
    file(WRITE ${CMD_GEN_WARN} "#!/bin/bash\n\n${CMAKE_CXX_COMPILER} -Q --help=warning | sed -e \'s/^\\s*\\\(\\-\\S*\\\)\\s*\\[\\w*\\]/\\1 /gp;d\' | tr -d '\\n'")
    execute_process(COMMAND chmod +x ${CMD_GEN_WARN})
    # Получить список всех предупреждений компилятора
    execute_process(COMMAND ${CMD_GEN_WARN} OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE CXX_WARNINGS)
    # Обработать список всех предупреждений компилятора для избежания заключения его в кавычки
    separate_arguments(CXX_WARNINGS UNIX_COMMAND "${CXX_WARNINGS}")
 
    add_compile_options(
 #      ${CXX_WARNINGS}
        -Wall
        -Wpedantic
        -Wextra
        -Waddress
        -Wbool-compare
        -Wbool-operation
        -Wcast-align
        -Wcast-qual
        -Wcatch-value
        -Wchar-subscripts
        -Wcomment
        -Wctor-dtor-privacy
        -Wdisabled-optimization
        -Wformat=2
        -Wint-in-bool-context
        -Winit-self
        -Wlogical-not-parentheses
        -Wlogical-op
        -Wmaybe-uninitialized
        -Wmemset-elt-size
        -Wmemset-transposed-args
        -Wmisleading-indentation
        -Wmissing-attributes
        -Wmissing-include-dirs
        -Wmultistatement-macros
        -Wnoexcept
        -Wnonnull
        -Wnonnull-compare
 #      -Wold-style-cast
        -Woverloaded-virtual
        -Wparentheses
        -Wpessimizing-move
        -Wredundant-decls
        -Wreorder
        -Wreturn-type
#       -Wshadow
        -Wsequence-point
#       -Wsign-compare
#       -Wsign-promo
        -Wsizeof-pointer-div
        -Wsizeof-pointer-memaccess
        -Wstrict-aliasing
        -Wstrict-null-sentinel
#       -Wstrict-overflow=5
        -Wswitch
        -Wtautological-compare
        -Wtrigraphs
        -Wundef
        -Wuninitialized
        -Wunused-but-set-variable
        -Wunused-function
        -Wunused-variable
        -fdiagnostics-show-option
    )
    add_definitions(
        "-D__MYFUNCNAME__=__PRETTY_FUNCTION__"
    )
    # MinGW или MSYS для сборки под Windows
    if ((CMAKE_CXX_PLATFORM_ID STREQUAL "MinGW") OR (CMAKE_CXX_PLATFORM_ID STREQUAL "MSYS"))
        add_link_options(
            "-static"
        )
        add_definitions(
            "-D_POSIX_SOURCE"
        )
    endif()

    # Если выполняется сборка для работы под Windows системой MSYS
#    if ((CMAKE_SYSTEM_NAME STREQUAL "Windows") OR (CMAKE_SYSTEM_NAME STREQUAL "MSYS"))
#        add_link_options(
#            "-static-libstdc++"
#            "-static-libgcc"
#            "-static"
#           "-lwinpthread"
#        )
#    endif()


    # Обрезать таблицы символов для Release
    add_link_options(
        $<$<CONFIG:RELEASE>:-s>
    )
    # Обрезать таблицы символов для MinSizeRel
    add_link_options(
        $<$<CONFIG:MINSIZEREL>:-s>
    )

# Intel compiler
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")

    message(DEBUG "Определён компилятор Intel")

# Microsoft Visual Studio
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

    message(DEBUG "Определён компилятор Microsoft Visual Studio")

    add_definitions(
        "-D__MYFUNCNAME__=__FUNCSIG__"
        "-D__STDC_WANT_SECURE_LIB__=1"
        "-D_CRT_SECURE_NO_WARNINGS"
    )

    add_compile_options(
        /vd2
#       Разрешить все предупреждения
        /Wall
#       Запретить указанные предупреждения
        /wd4242 # C4242 =: преобразование "int" в "char", возможна потеря данных
        /wd4244 # C4244 =: преобразование "..." в "...", возможна потеря данных
        /wd4245 # C4245 инициализация: преобразование "..." в "...", несоответствие типов со знаком и без
        /wd4267 # C4267 аргумент: преобразование из "size_t" в "int"; возможна потеря данных
        /wd4305 # C4305 аргумент: усечение из "double" в "float"
        /wd4310 # C4310 приведение обуславливает усечение постоянного значения
        /wd4365 # C4365 преобразование "..." в "...", несоответствие типов со знаком и без
        /wd4456 # C4456 объявление "..." скрывает предыдущее локальное объявление
        /wd4458 # C4458 объявление "..." скрывает член класса
        /wd4464 # C4464 относительный путь включения содержит ".."
        /wd4514 # C4514 подставляемая функция, не используемая в ссылках, была удалена
        /wd4623 # C4623 конструктор по умолчанию неявно определен как удаленный
        /wd4625 # C4625 конструктор копий неявно определен как удаленный
        /wd4626 # C4626 оператор назначения неявно определен как удаленный
        /wd4710 # C4710 функция не является встроенной
        /wd4711 # C4711 функция "..." выбрана для автоматического преобразования во встроенную
        /wd4820 # C4820 отбивка размером "..." байт добавлена после данные-член
        /wd4866 # C4866 возможно, компилятор не выполняет вычисление справа налево для вызова
        /wd4946 # C4946 использование reinterpret_cast между связанными классами: "..." и "..."
        /wd5026 # C5026 конструктор перемещения неявно определён как удалённый
        /wd5027 # C5027 оператор назначения перемещением неявно определен как удаленный
        /wd5045 # C5045 Компилятор вставит компонент устранения рисков Spectre для загрузки памяти, если указан параметр /Qspectre
        /wd5219 # C5219 неявное преобразование "..." в "...", возможна потеря данных
        /wd5267 # C5267 определение неявного конструктор копий для '...' устарело, так как оно имеет предоставленный пользователем деструктор
#       /EHa   # Насчёт обработки исключений
    )
    # Настройка минимально требуемого размера стека
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} /STACK:4000000,10000")
else()
    message(WARNING "Неизвестный компилятор ${CMAKE_CXX_COMPILER_ID}")
endif()

##############################################################################
# Настройка в зависимости от целевой среды выполнения.
##############################################################################

# При сборке для работы в среде Linux
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")

# Параметры настройки RPATH - пути, где искать динамические библиотеки (для бинарника "установки")

# использовать (не пропускать) установку RPATH (для бинарника "сборки") - по месту сборки
#SET(CMAKE_SKIP_BUILD_RPATH FALSE)
# при сборке не применять "установочный" RPATH (CMAKE_INSTALL_RPATH)
#SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 
# RPATH, который будет вписан в бинарник "установки"
 SET(CMAKE_INSTALL_RPATH "${ORIGIN}/lib")
# don't add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
#SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


# При сборке для работы в среде MacOS/OS X
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")

# При сборке для работы в среде Windows
elseif ((CMAKE_SYSTEM_NAME STREQUAL "Windows") OR (CMAKE_SYSTEM_NAME STREQUAL "MSYS"))

else()
    message(WARNING "Неизвестная среда сборки " ${CMAKE_SYSTEM_NAME})
endif()

##############################################################################
# Настройка в зависимости от типа сборки.
##############################################################################

# Определить, является ли генератор мультиконфигурационным
get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if (isMultiConfig)
    # Типы сборки для генераторов с мульти-конфигом
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo;MinSizeRel")
    message(DEBUG "Будет собрана конфигурация, указанная при сборке")
    # Имя директории, где будут расположены директории с исполняемыми файлами
    # приложения для разных вариантов конфигурации
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BIN_PATH}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BIN_PATH}")
else()
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release")
        message(DEBUG "Будет собрана конфигурация по умолчанию " ${CMAKE_BUILD_TYPE})
    else()
        message(DEBUG "Будет собрана выбранная конфигурация " ${CMAKE_BUILD_TYPE})
    endif()
    # Имя директории, где будет расположен исполняемый файл приложения
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BIN_PATH}/${CMAKE_BUILD_TYPE}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BIN_PATH}/${CMAKE_BUILD_TYPE}")
endif()

##############################################################################
# Настройка языков локализации
##############################################################################

# Английский, испанский, французский, бразильский вариант португальского, русский
set(QT_LANG "en_US;es_ES;fr_FR;pt_BR;ru_RU")

##############################################################################
# Вывод информации о проекте, инструментах, среде сборки и среде исполнения
##############################################################################

# Получить уровень выводимых сообщений
cmake_language(GET_MESSAGE_LOG_LEVEL CMAKE_LOGGING_LEVEL)
# Существуют следующие уровни выводимых сообщений:
# FATAL_ERROR - серьёзная ошибка, вызывающая полную остановку сборки;
# SEND_ERROR - серьёзная ошибка, вызывающая остановку сборки без остановки выполнения скрипта Cmake;
# WARNING - предупреждение;
# AUTHOR_WARNING - предупреждение разработчика;
# DEPRECATION - ошибка или предупреждение об использовании устаревшей функции Cmake;
# NOTICE - важное сообщение, выводимое на устройство stderr;
# STATUS - краткое важное сообщение (это уровень по умолчанию);
# VERBOSE - подробная информация об особенностях сборки;
# DEBUG - подробная информация, необходимая только разработчику;
# TRACE - сообщение о ходе сборки для точного отслеживания процесса.
# Выводятся сообщения от указанного уровня (включая) и выше.
# Устанавливается заданием параметра cmake, например cmake --log-level=DEBUG

message(STATUS "##############################################################################")
message(STATUS "Проект '${CMAKE_PROJECT_NAME}' версии ${PROJECT_VERSION}")
message(STATUS "CMake версии ${CMAKE_VERSION}")
message(STATUS "Уровень журналирования CMake ${CMAKE_LOGGING_LEVEL} и выше")
message(STATUS "Компилятор ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Генератор ${CMAKE_GENERATOR}")
message(STATUS "Платформа ${CMAKE_CXX_PLATFORM_ID}")
message(STATUS "Среда сборки ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "Целевая среда исполнения ${CMAKE_SYSTEM_NAME}")
if (CMAKE_BUILD_TYPE)
    message(STATUS "Конфигурация ${CMAKE_BUILD_TYPE}")
endif()

message(STATUS "Qt версии ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
if (DEFINED QT_HOST_PATH) 
    message(STATUS "Будет использован Qt, расположенный в '${QT_HOST_PATH}'")
endif()

message(STATUS "##############################################################################")

# Создавать заголовочные файлы для файлов *.ui
set(CMAKE_AUTOUIC ON)
# Использовать метаобъектный компилятор
set(CMAKE_AUTOMOC ON)

##############################################################################
# Обработка компонентов (библиотеки, скрипты, исполняемый файл, упаковка)
##############################################################################

add_subdirectory(src/designerplugins/cameraplugin)

add_subdirectory(src/designerplugins/customwidgetsplugin)

add_subdirectory(src/scriptbindings)

add_subdirectory(src/candle)

add_subdirectory(src/candleplugins)

add_subdirectory(packaging)

##############################################################################
# Архивирование всего проекта в директорию сборки
##############################################################################

set(ARCHIVE_NAME "${CMAKE_PROJECT_NAME}.tar.gz") 

add_custom_target(backup
    COMMENT "Создание архива исходных текстов"
    COMMAND touch ${ARCHIVE_NAME}
    COMMAND tar --exclude=.git --exclude=${ARCHIVE_NAME} --create --gzip --file=${ARCHIVE_NAME} .
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    VERBATIM
)

##############################################################################
# Создание файлов документации (HTML, PDF)
##############################################################################

# Использовать компонент для поиска Doxygen
include(FindDoxygen)

# Должны быть найдены doxygen и dot (начиная с CMAKE 3.9)
find_package(Doxygen QUIET COMPONENTS dot)

# Если doxygen найден, создать цели формирования файлов документации
if (DOXYGEN_FOUND)
    # Настройка переменных окружения Доксигена для основной цели
    set(DOXYGEN_PROJECT_NAME            "${CMAKE_PROJECT_NAME}")
    set(DOXYGEN_PROJECT_BRIEF           "Программа Candle")
    set(DOXYGEN_PROJECT_NUMBER          "${PROJECT_VERSION}")
    set(DOXYGEN_OUTPUT_DIRECTORY        "${DOC_PATH}")
    set(DOXYGEN_OUTPUT_LANGUAGE         "Russian")
    set(DOXYGEN_STRIP_FROM_PATH         "src/")
    set(DOXYGEN_TAB_SIZE                "2")
    set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C   YES)
    set(DOXYGEN_LOOKUP_CACHE_SIZE       2)
    set(DOXYGEN_NUM_PROC_THREADS        8)
    set(DOXYGEN_QUIET                   YES)
    set(DOXYGEN_EXTRACT_ALL             YES)
    set(DOXYGEN_EXTRACT_PRIVATE         YES)
    set(DOXYGEN_EXTRACT_PRIV_VIRTUAL    YES)
    set(DOXYGEN_EXTRACT_PACKAGE         YES)
    set(DOXYGEN_EXTRACT_STATIC          YES)
    set(DOXYGEN_HIDE_SCOPE_NAMES        YES)
    set(DOXYGEN_SORT_MEMBER_DOCS        NO)
    set(DOXYGEN_STRICT_PROTO_MATCHING   YES)
    set(DOXYGEN_WARN_NO_PARAMDOC        YES)
    set(DOXYGEN_WARN_LOGFILE            "${DOC_PATH}/warnings.log")
    set(DOXYGEN_FILE_PATTERNS           *.h *.hxx *.cpp *.md)
    set(DOXYGEN_EXAMPLE_PATH            "${SOURCES_PATH}")
    set(DOXYGEN_IMAGE_PATH              ${DOXY_IMAGES})
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE  readme.md)
    set(DOXYGEN_ALPHABETICAL_INDEX      NO)
    set(DOXYGEN_HTML_STYLESHEET         "${CMAKE_SOURCE_DIR}/doc/stylesheet.css")
    set(DOXYGEN_GENERATE_TREEVIEW       YES)
    set(DOXYGEN_ENUM_VALUES_PER_LINE    1)
    set(DOXYGEN_HTML_FORMULA_FORMAT     svg)
    set(DOXYGEN_FORMULA_FONTSIZE        12)
    set(DOXYGEN_USE_MATHJAX             YES)
    set(DOXYGEN_MATHJAX_VERSION         MathJax_3)
    set(DOXYGEN_MATHJAX_FORMAT          chtml)
    set(DOXYGEN_MATHJAX_RELPATH         "../../../mathjax")
    set(DOXYGEN_MATHJAX_EXTENSIONS      require ams mathtools textcomp unicode)
    set(DOXYGEN_GENERATE_LATEX          YES)
    set(DOXYGEN_USE_PDFLATEX            YES)
    set(DOXYGEN_LATEX_CMD_NAME          ${CMD_RUN_LATEX})
    set(DOXYGEN_EXTRA_PACKAGES          "{amsmath, verbatimbox, svg}")
    set(DOXYGEN_LATEX_HEADER            "${CMAKE_SOURCE_DIR}/doc/header.tex")
    set(DOXYGEN_LATEX_EXTRA_STYLESHEET  "${CMAKE_SOURCE_DIR}/doc/doxygen.sty")
    set(DOXYGEN_LATEX_BATCHMODE         YES)
    set(DOXYGEN_MACRO_EXPANSION         YES)
    set(DOXYGEN_PREDEFINED              "__DOXYGEN__")
    set(DOXYGEN_SKIP_FUNCTION_MACROS    NO)
    set(DOXYGEN_HAVE_DOT                YES)
    set(DOXYGEN_INCLUDE_GRAPH           NO)
    set(DOXYGEN_INCLUDED_BY_GRAPH       NO)
    set(DOXYGEN_DIRECTORY_GRAPH         NO)
    set(DOXYGEN_DOT_IMAGE_FORMAT        svg)
    set(DOXYGEN_INTERACTIVE_SVG         YES)
    set(DOXYGEN_DOT_GRAPH_MAX_NODES     200)
    set(DOXYGEN_MAX_DOT_GRAPH_DEPTH     1000)
    set(DOXYGEN_VERBATIM_HEADERS        NO)

    # Формирование файлов документации html при помощи doxygen (начиная с CMAKE 3.9)
    doxygen_add_docs(html_doc_proc
        ${SOURCES_PATH}
        WORKING_DIRECTORY ${SOURCES_PATH}
        COMMENT "Создание документации ${MAIN_NAME} в формате html"
    )

    # Удаление файла warnings.log, если он нулевой длины
    add_custom_target(html_doc
        ${CMD_CLN_WARN}
        WORKING_DIRECTORY ${DOC_PATH}
        COMMENT "Удаление файлов нулевой длины"
        VERBATIM
    )
    add_dependencies(html_doc html_doc_proc)

    # Формирование файла документации pdf при помощи doxygen
    add_custom_target(pdf_doc
        make ${CMD_TO_NUL}
        WORKING_DIRECTORY ${DOC_PATH}/latex
        COMMENT "Создание документации ${MAIN_NAME} в формате pdf"
    )
    add_dependencies(pdf_doc html_doc)
endif(DOXYGEN_FOUND)

##############################################################################
# Статический анализ исходных текстов при помощи Clang-Tidy
##############################################################################

# Проверить наличие исполняемого файла Clang-Tidy
find_program(CLANG_TIDY_EXE
     NAMES "clang-tidy"
)

if (EXISTS ${CLANG_TIDY_EXE})

    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" -checks=-*, readability-*)

endif()

##############################################################################
# Статический анализ исходных текстов при помощи PVS-Studio
##############################################################################

# Проверить наличие исполняемых файлов PVS-Studio
find_program(PVS_STUDIO_ANALYZER
    HINTS "C:/Program Files/PVS-Studio" "C:/Program Files (x86)/PVS-Studio" "D:/Program Files/PVS-Studio" "D:/Program Files (x86)/PVS-Studio"
    NAMES CompilerCommandsAnalyzer.exe pvs-studio-analyzer
)

find_program(PVS_STUDIO_CONVERTER
    HINTS "C:/Program Files/PVS-Studio" "C:/Program Files (x86)/PVS-Studio" "D:/Program Files/PVS-Studio" "D:/Program Files (x86)/PVS-Studio"
    NAMES HtmlGenerator.exe plog-converter
)

# BIN path                      path to pvs-studio-analyzer (Unix) or CompilerCommandsAnalyzer.exe (Windows)
# CONVERTER path                path to plog-converter (Unix) or HtmlGenerator.exe (Windows)

if ((EXISTS ${PVS_STUDIO_ANALYZER}) AND (EXISTS ${PVS_STUDIO_CONVERTER}))

    include(PVS-Studio.cmake)

    # Анализ приложения
    pvs_studio_add_target(TARGET analyze
        FORMAT errorfile-verbose
        ANALYZE "candle" #${CMAKE_PROJECT_NAME}
        MODE GA;OP;CS;64
        LOG ${BUILD_PATH}/pvs_report.txt
#       CONVERTER_ARGS -d V112,V122,V550,V601,V2014
        BIN ${PVS_STUDIO_ANALYZER}
        CONVERTER ${PVS_STUDIO_CONVERTER}
    )

else()
    message(NOTICE "--- Программа PVS Studio не найдена: будет отсутствовать возможность статического анализа")
endif()

##############################################################################
# Формирование установочного набора
##############################################################################

# Вывод сообщений об установке только если было изменение
set(CMAKE_INSTALL_MESSAGE LAZY)

# Включить в список файлов, для которых будут найдены зависимости, цели проекта
# (исполняемый файл, библиотеки).
set(DEP_FILE_SET
  "${CMAKE_INSTALL_BINDIR}/candle${CMAKE_EXECUTABLE_SUFFIX}"
  "${CMAKE_INSTALL_LIBDIR}/${CMAKE_SHARED_LIBRARY_PREFIX}scriptbindings${CMAKE_SHARED_LIBRARY_SUFFIX}"
  "${CMAKE_INSTALL_LIBDIR}/${CMAKE_SHARED_LIBRARY_PREFIX}customwidgetsplugin${CMAKE_SHARED_LIBRARY_SUFFIX}"
  "${CMAKE_INSTALL_LIBDIR}/${CMAKE_SHARED_LIBRARY_PREFIX}cameraplugin${CMAKE_SHARED_LIBRARY_SUFFIX}"
)

# Получить список файлов в плюгинах Qt
file(GLOB_RECURSE PLUG_LIST
  RELATIVE "${QT_DIR}/../../../plugins"
  "${QT_DIR}/../../../plugins/*"
)
# Установить плюгины Qt, добавить библиотеки в список файлов,
# для которых будут найдены зависимости
foreach(FILE ${PLUG_LIST})
    get_filename_component(FILE_PATH "${FILE}" DIRECTORY)
    get_filename_component(FILE_NAME "${FILE}" NAME)
    get_filename_component(EXTENSION "${FILE}" LAST_EXT)
    install(FILES "${QT_DIR}/../../../plugins/${FILE}"
      DESTINATION "${CMAKE_INSTALL_LIBDIR}/plugins/${FILE_PATH}"
    )
    # Если это библиотека, дополнить список поиска зависимостей
    if("${EXTENSION}" STREQUAL "${CMAKE_SHARED_LIBRARY_SUFFIX}")
        list(APPEND DEP_FILE_SET "${CMAKE_INSTALL_LIBDIR}/plugins/${FILE}")
    else()
# !!!TODO!!! Не устанавливать .debug для релизной сборки
    endif()
endforeach()


# if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
#    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Resources/"
#            DESTINATION "${CMAKE_INSTALL_BUNDLEDIR}/${MACOSX_BUNDLE_BUNDLE_NAME}.app/Contents/Resources")
#    )
#    include(BundleUtilities)
#    fixup_bundle("${CMAKE_INSTALL_PREFIX}/${MACOSX_BUNDLE_BUNDLE_NAME}.app"
#                 ""
#                 "${CMAKE_INSTALL_PREFIX}/lib") # Or wherever your libraries are installed


# Формирование файла-скрипта для установки зависимостей
file(WRITE
    ${MISC_PATH}/inst_deps.cmake

"# Функция, выполняющая поиск библиотеки по имени в известных директориях,\n"
"# установку её во временную директорию вместе с её зависимостями\n"
"function(install_unresolved_library_with_deps LIB_NAME)\n"
"    # Проверить, может это библиотека из указанного Qt\n"
"    if(EXISTS \"${QT_DIR}/../../\${LIB_NAME}\")\n"
"        set(LIBRARY \"${QT_DIR}/../../\${LIB_NAME}\")\n"
"    # Проверить, может это библиотека приложения\n"
"    elseif(EXISTS \"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/\${LIB_NAME}\")\n"
"        set(LIBRARY \"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/\${LIB_NAME}\")\n"
"    # Проверить, может эта библиотека уже установлена\n"
"    elseif(EXISTS \"${MISC_PATH}/libs/\${LIB_NAME}\")\n"
"        set(LIBRARY \"\")\n"
"    else()\n"
"        set(LIBRARY \"\")\n"
"        message(DEBUG \"Не удалось определить расположение библиотеки \${LIB_NAME}\")\n"
"    endif()\n"
"    # Если библиотека найдена, обработать её\n"
"    if(NOT \"^^\${LIBRARY}\" STREQUAL \"^^\")\n"
"        install_library_with_deps(\"\${LIBRARY}\")\n"
"    endif()\n"
"endfunction()\n"
"\n"
"# Функция, выполняющая установку во временную директорию\n"
"# указанной библиотеки и её зависимостей\n"
"function(install_library_with_deps LIBRARY)\n"
"    # Разделить полный путь на директорию и файл\n"
"    get_filename_component(NAME \"\${LIBRARY}\" NAME)\n"
"\n"
"    # Проверить, может это библиотека из указанного Qt\n"
"    if(EXISTS \"${QT_DIR}/../../\${NAME}\")\n"
"        set(TEST_LIB \"${QT_DIR}/../../\${NAME}\")\n"
"        set(DIRR \"${QT_DIR}/../..\")\n"
"    else()\n"
"        set(TEST_LIB \"\${LIBRARY}\")\n"
"        get_filename_component(DIRR \"\${LIBRARY}\" DIRECTORY)\n"
"    endif()\n"
"\n"
"    # Проверить, может такая библиотека уже установлена, тогда ничего не делать\n"
"    if ((EXISTS \"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/\${NAME}\")\n"
"       OR (EXISTS \"${MISC_PATH}/libs/\${NAME}\"))\n"
"    else()\n"
"        file(INSTALL\n"
"          DESTINATION \"${MISC_PATH}/libs\"\n"
"          TYPE SHARED_LIBRARY\n"
"          FILES \"\${TEST_LIB}\"\n"
"        )\n"
"\n"
"        if(IS_SYMLINK \${TEST_LIB})\n"
"            # Эта зависимотсь - символическиая ссылка.\n"
"            # Повотрить процедуру для файла, на который указывает эта сылка.\n"
"            file(READ_SYMLINK \${TEST_LIB} SYM_FILE)\n"
"            install_library_with_deps(\"\${DIRR}/\${SYM_FILE}\")\n"
"        else()\n"
"\n"
"            # Определить зависимости для файла\n"
"            file(GET_RUNTIME_DEPENDENCIES\n"
"              LIBRARIES \${TEST_LIB}\n"
"              RESOLVED_DEPENDENCIES_VAR RESOLVED_DEPS\n"
"              UNRESOLVED_DEPENDENCIES_VAR UNRESOLVED_DEPS\n"
"            )\n"
"\n"
"            # Перебрать все зависимости, для каждой повторить процедуру\n"
"            foreach(FILE \${RESOLVED_DEPS})\n"
"                install_library_with_deps(\"\${FILE}\")\n"
"            endforeach()\n"
"            foreach(FILE \${UNRESOLVED_DEPS})\n"
"                install_unresolved_library_with_deps(\"\${FILE}\")\n"
"            endforeach()\n"
"        endif()\n"
"    endif()\n"
"endfunction()\n"
"\n"
"message(STATUS \"Установить файлы-библиотеки зависимостей для списка файлов:\")\n"
"foreach(F ${DEP_FILE_SET})\n"
"\n"
"    message(STATUS \"Найти и установить зависимости для \${F}\")\n"
"    file(GET_RUNTIME_DEPENDENCIES\n"
"      EXECUTABLES \"${CMAKE_INSTALL_PREFIX}/\${F}\"\n"
"      RESOLVED_DEPENDENCIES_VAR RESOLVED_DEPS\n"
"      UNRESOLVED_DEPENDENCIES_VAR UNRESOLVED_DEPS\n"
"    )\n"
"\n"
"    foreach(FILE \${RESOLVED_DEPS})\n"
"        install_library_with_deps(\"\${FILE}\")\n"
"    endforeach()\n"
"\n"
"    foreach(FILE \${UNRESOLVED_DEPS})\n"
"        install_unresolved_library_with_deps(\"\${FILE}\")\n"
"    endforeach()\n"
"endforeach()\n"
"\n"
"message(DEBUG \"Получить список файлов-библиотек зависимостей во временной директории\")\n"
"file(GLOB TMP_DEP_LIST\n"
"  \"${MISC_PATH}/libs/*.*\"\n"
")\n"
"list(LENGTH TMP_DEP_LIST TMP_DEP_LIST_SIZE)\n"
"message(STATUS \"Установить файлы-библиотеки зависимостей (\${TMP_DEP_LIST_SIZE} шт.) из временной директории\")\n"
"foreach(FILE \${TMP_DEP_LIST})\n"
"    message(DEBUG \"From MISC: \${FILE} to ${CMAKE_INSTALL_LIBDIR}\")\n"

# Только для Линукса и Макоси!
"execute_process(COMMAND \${CMAKE_COMMAND} -E chdir \"${CMAKE_INSTALL_PREFIX}\")\n"

#!!!TODO!!! Проблема: абсолютный путь портит этап установки
"    file(INSTALL\n"
#"      DESTINATION \"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}\"\n"
"      DESTINATION \"${CMAKE_INSTALL_LIBDIR}\"\n"
"      TYPE SHARED_LIBRARY\n"
"      FILES \"\${FILE}\"\n"
"    )\n"
"endforeach()\n"
)

# Запустить скрипт поиска зависимостей (этап установки)
install(SCRIPT "${MISC_PATH}/inst_deps.cmake")

# Если сборка предназначена для выполнения под Windows
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")

    # Файл лицензии (этап конфигурации)
    message(DEBUG "Установить файл лицензии")
    install(FILES ${CMAKE_SOURCE_DIR}/LICENSE
        DESTINATION "./"
        COMPONENT docs
    )

# Если сборка предназначена для выполнения под Linux
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")

    # Файл лицензии (этап конфигурации)
    message(DEBUG "Установить файл лицензии")
    install(FILES ${CMAKE_SOURCE_DIR}/LICENSE
        DESTINATION "share/doc/candle"
        COMPONENT docs
    )

    #!!! Можно использовать один и тот же SVG для всех разрешений
    # Значок программы (этап конфигурации)
    message(DEBUG "Установить файл значка программы")
    install(FILES ${CMAKE_SOURCE_DIR}/src/candle/images/candle_256.png
        DESTINATION "share/icons/hicolor/256x256/apps"
        RENAME candle.png
    )
endif()
