##############################################################################
# Минимально необходимая для нормальной работы версия cmake, Qt
##############################################################################

cmake_minimum_required(VERSION 3.9...3.28)

##############################################################################
# Информация о проекте
##############################################################################

project(Candle
    VERSION 1.2.15.1
    DESCRIPTION "GRBL controller application with G-Code visualizer"
    LANGUAGES CXX
)

##############################################################################
# Настройка местоположения Qt
##############################################################################

if(DEFINED ENV{QT_ROOT}) 
    set(QT_DIR  "$ENV{QT_ROOT}/lib/cmake/Qt6/" CACHE PATH "The directory containing a CMake configuration file for QT.")
    set(Qt6_DIR "$ENV{QT_ROOT}/lib/cmake/Qt6/" CACHE PATH "The directory containing a CMake configuration file for Qt6.")
    set(CMAKE_PREFIX_PATH $ENV{QT_ROOT})
endif()

find_package(QT NAMES Qt6 COMPONENTS Core REQUIRED)

##############################################################################
# Директории, создаваемые для выполнения сборки
##############################################################################

# Директория для промежуточных и собранных файлов
if(DEFINED ENV{BUILDDIR}) 
    set(BUILD_PATH "$ENV{BUILDDIR}")
else()
    set(BUILD_PATH "${CMAKE_BINARY_DIR}/..")
endif()

# Директория для результирующих бинарных файлов
set(BIN_PATH "${BUILD_PATH}/bin")
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${BIN_PATH})
# Директория для промежуточных файлов
set(MISC_PATH "${BUILD_PATH}/misc")
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${MISC_PATH})
include_directories(${MISC_PATH})
# Директория для файлов с изображениями значка
set(ICONS_PATH "${BUILD_PATH}/icons")
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${ICONS_PATH})
# Директория для документации приложения
set(DOC_PATH "${BUILD_PATH}/docs")
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${DOC_PATH})
# Директория для сборки установочного набора
set(DEST_PATH "${BUILD_PATH}/install")
if(APPLE)
    set(DEST_PATH "${BUILD_PATH}/install/candle.app/Contents/MacOS")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${DEST_PATH})
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${DEST_PATH}/translations)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${DEST_PATH}/plugins)
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
# Настройки компиляторов
##############################################################################

# Отключённые предупреждения C++ в GCC
set(CPP_DISABLED_WARN
#    -Wno-system-headers
    #-Wno-aggregate-return
    #-Wno-undef
#   -Wno-zero-as-null-pointer-constant
    -Wno-padded
    -Wno-long-long
    #-Wno-inline

    -Wno-shadow
   #-Wno-suggest-final-types
   #-Wno-suggest-final-methods
   #-Wno-suggest-attribute=cold
   #-Wno-suggest-attribute=const
   #-Wno-suggest-attribute=pure
   #-Wno-suggest-attribute=noreturn
   #-Wno-suggest-attribute=format
   #-Wno-unused-function
#  У GCC 10 это предупреждение не отключается
   -Wno-unused-macros
   -Wno-switch-default
   -Wno-conversion
   -Wno-sign-conversion
   #-Wno-suggest-attribute=malloc
# Для нового sdai
  # -Wno-ignored-qualifiers
# Временно!
  -Wno-unused-parameter
  -Wno-aggregate-return
#   -Wno-return-type
)

##############################################################################
# Настройка в зависимости от используемого компилятора.
##############################################################################

# Требуемая версия компилятора C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# clang
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(
        "-Wall"
        "-Wpedantic"
        "-Wextra"
        "-Wunused-but-set-variable"
    )
    add_definitions(
        "-D__CLANG__"
        "-D__MYFUNCNAME__=__PRETTY_FUNCTION__"  #linux-win!!!
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
    add_compile_options(
        "-Wall"
        "-Wpedantic"
        "-Wextra"
        "-Wunused-but-set-variable"
    )
    add_definitions(
        "-D__CLANG__"
        "-D__MYFUNCNAME__=__PRETTY_FUNCTION__"
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
    add_compile_options(
        "-Wall"
        "-Wpedantic"
        "-Wextra"
        "-Wunused-but-set-variable"
#        ${CPP_DISABLED_WARN}
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

# Microsoft Visual Studio
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_definitions(
        "-D__MYFUNCNAME__=__FUNCSIG__"
        "-D__STDC_WANT_SECURE_LIB__=1"
        "-D_CRT_SECURE_NO_WARNINGS"
    )
    include_directories($ENV{INCLUDE})
    link_directories($ENV{LIB})
    add_compile_options(
        /vd2
#       Разрешить все предупреждения
        /Wall
#       Запретить указанные предупреждения
        /wd4242 # C4242 =: преобразование "int" в "char", возможна потеря данных
        /wd4244 # C4244 =: преобразование "..." в "...", возможна потеря данных
        /wd4245 # C4245 инициализация: преобразование "..." в "...", несоответствие типов со знаком и без
        /wd4365 # C4365 преобразование "..." в "...", несоответствие типов со знаком и без
        /wd4514 # C4514 подставляемая функция, не используемая в ссылках, была удалена
        /wd4623 # C4623 конструктор по умолчанию неявно определен как удаленный
        /wd4710 # C4710 функция не является встроенной
        /wd4820 # C4820 отбивка размером "..." байт добавлена после данные-член
        /wd4866 # C4866 возможно, компилятор не выполняет вычисление справа налево для вызова
        /wd4946 # C4946 использование reinterpret_cast между связанными классами: "..." и "..."
        /wd5045 # C5045 Компилятор вставит компонент устранения рисков Spectre для загрузки памяти, если указан параметр /Qspectre
        /wd5219 # C5219 неявное преобразование "..." в "...", возможна потеря данных
        /wd5267 # C5267 определение неявного конструктор копий для '...' устарело, так как оно имеет предоставленный пользователем деструктор
        /EHsc   # Насчёт обработки исключений
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
#   message(STATUS "Будет собрана конфигурация, указанная при сборке")
    # Имя директории, где будут расположены директории с исполняемыми файлами
    # приложения для разных вариантов конфигурации
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BIN_PATH}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BIN_PATH}")
else()
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release")
#       message(STATUS "Будет собрана конфигурация по умолчанию " ${CMAKE_BUILD_TYPE})
    else()
#       message(STATUS "Будет собрана выбранная конфигурация " ${CMAKE_BUILD_TYPE})
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

message(STATUS "##############################################################################")
message(STATUS "Проект '${CMAKE_PROJECT_NAME}' версии ${PROJECT_VERSION}")
message(STATUS "CMake версии ${CMAKE_VERSION}")
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
# Обработка компонентов (библиотеки, скрипты, исполняемый файл)
##############################################################################

add_subdirectory(src/designerplugins/cameraplugin)

add_subdirectory(src/designerplugins/customwidgetsplugin)

add_subdirectory(src/scriptbindings)

add_subdirectory(src/candle)

add_subdirectory(src/candleplugins)

##############################################################################
# Архивирование всего проекта в директорию cmake
##############################################################################

set(ARCHIVE_NAME "${CMAKE_PROJECT_NAME}.tar.gz") 

add_custom_target(backup
    COMMENT "Создание архива исходных текстов"
    COMMAND touch ${ARCHIVE_NAME}
    COMMAND tar --exclude=build --exclude=TEST* --exclude=${ARCHIVE_NAME} --create --gzip --file=${ARCHIVE_NAME} .
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
    set(DOXYGEN_STRIP_FROM_PATH         "../src/")
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
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE  README.md)
    set(DOXYGEN_ALPHABETICAL_INDEX      NO)
    set(DOXYGEN_HTML_STYLESHEET         "${CMAKE_SOURCE_DIR}/stylesheet.css")
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
    set(DOXYGEN_LATEX_HEADER            "${CMAKE_SOURCE_DIR}/header.tex")
    set(DOXYGEN_LATEX_EXTRA_STYLESHEET  "${CMAKE_SOURCE_DIR}/doxygen.sty")
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
    message(STATUS "Программа PVS Studio не найдена: будет отсутствовать возможность статического анализа")
endif()

##############################################################################
# Формирование установочного набора
##############################################################################

# Вывод сообщений об установке только если было изменение
set(CMAKE_INSTALL_MESSAGE LAZY)

# Файл лицензии
install(FILES ${CMAKE_SOURCE_DIR}/LICENSE
    DESTINATION "${DEST_PATH}"
)


# Файлы переводов Qt
set(QT_LIBS "qt;qtbase;qtmultimedia;qtserialport")

# Перебрать поддерживаемые языки
foreach(L ${QT_LANG})
    string(SUBSTRING ${L} 0 2 LANG_F)
    # Перебрать необходимые файлы перевода
    foreach(I ${QT_LIBS})

        if(EXISTS "/usr/share/qt6/translations/${I}_${LANG_F}.qm")
            set(QT_TRANSLATION "/usr/share/qt6/translations/${I}_${LANG_F}.qm")
        elseif(EXISTS "${QT_DIR}/../../../translations/${I}_${LANG_F}.qm")
            set(QT_TRANSLATION "${QT_DIR}/../../../translations/${I}_${LANG_F}.qm")
        endif()

        install(FILES "${QT_TRANSLATION}"
            DESTINATION "${DEST_PATH}/translations"
        )
    endforeach(I)
endforeach(L)

# Файлы библиотек Qt
set(QT_LIBS "Core;Gui;Qml;Multimedia;MultimediaWidgets;OpenGL;OpenGLWidgets;SerialPort;Widgets")
foreach(I ${QT_LIBS})

    if(EXISTS "/usr/lib/x86_64-linux-gnu/${CMAKE_SHARED_LIBRARY_PREFIX}Qt6${I}${CMAKE_SHARED_LIBRARY_SUFFIX}")
        set(QTLIB "/usr/lib/x86_64-linux-gnu/${CMAKE_SHARED_LIBRARY_PREFIX}Qt6${I}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    elseif(EXISTS "${QT_DIR}/../../lib/${CMAKE_SHARED_LIBRARY_PREFIX}Qt6${I}${CMAKE_SHARED_LIBRARY_SUFFIX}")
        set(QTLIB "${QT_DIR}/../../lib/${CMAKE_SHARED_LIBRARY_PREFIX}Qt6${I}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    endif()

    file(INSTALL ${QTLIB}
        DESTINATION ${DEST_PATH}
        FOLLOW_SYMLINK_CHAIN
    )

#    install(FILES "${QTLIB}"
#        DESTINATION "${DEST_PATH}"
#    )
endforeach(I)

#file(GET_RUNTIME_DEPENDENCIES RESOLVED_DEPENDENCIES_VAR r UNRESOLVED_DEPENDENCIES_VAR ur EXECUTABLES "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/candle")
#message(STATUS "Resolved ${r} Unresolved ${ur}")
