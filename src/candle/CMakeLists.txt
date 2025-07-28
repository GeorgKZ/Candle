##############################################################################
# Информация о компоненте
##############################################################################

# Имя компонента по имени директории, содержащей компонент
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR STEM LAST_ONLY MAIN_NAME)
message(STATUS "DIR: ${MAIN_NAME}")

# Вывод информации о собираемом компоненте
message(STATUS "##############################################################################")
message(STATUS "Проект '${CMAKE_PROJECT_NAME}', компонент '${MAIN_NAME}'")
message(STATUS "##############################################################################")

##############################################################################
# Директории с файлами, необходимыми для сборки
##############################################################################

# Путь к директории с исходными текстами
set(SOURCES_PATH "${CMAKE_SOURCE_DIR}/src/candle")

# Список заголовков исходных текстов приложения
file(GLOB SOURCE_HEADERS_LIST
    ${SOURCES_PATH}/*.h
    ${SOURCES_PATH}/drawers/*.h
    ${SOURCES_PATH}/parser/*.h
    ${SOURCES_PATH}/widgets/*.h
    ${SOURCES_PATH}/tables/*.h
)

# Список файлов c++ исходных текстов приложения
file(GLOB SOURCE_FILE_LIST
    ${SOURCES_PATH}/*.cpp
    ${SOURCES_PATH}/drawers/*.cpp
    ${SOURCES_PATH}/parser/*.cpp
    ${SOURCES_PATH}/widgets/*.cpp
    ${SOURCES_PATH}/tables/*.cpp
)

# Определение для неопределённого значения (больше или равно этому числу)
add_definitions(
    -DsNan=65536
)

# Определения с номером версии
add_definitions(
    -DVERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    -DVERSION_MINOR=${PROJECT_VERSION_MINOR}
    -DVERSION_PATCH=${PROJECT_VERSION_PATCH}
    -DVERSION_TWEAK=${PROJECT_VERSION_TWEAK}
    -DVERSION_STR="${PROJECT_VERSION}"
    -DPROJECT_NAME="${PROJECT_NAME}"
)

##############################################################################
# Настройка ресурсов в зависимости от целевой среды выполнения.
##############################################################################

# При сборке для работы в среде Windows
if ((CMAKE_SYSTEM_NAME STREQUAL "Windows") OR (CMAKE_SYSTEM_NAME STREQUAL "MSYS"))

    # Путь к файлу значка ICO для сборки исполняемого файла Windows
    set(ICON_FILE "${CMAKE_SOURCE_DIR}/src/candle/images/candle.ico")
    set(ICON_RESOURCE_STRING "IDI_ICON1 ICON DISCARDABLE \"${ICON_FILE}\"\n\n")

    # Создать файл ресурса по шаблону
    file(WRITE
        ${MISC_PATH}/${MAIN_NAME}.rc

       "${ICON_RESOURCE_STRING}"
        "#include <windows.h>\n"
        "\n"
        "#define VER_FILEVERSION          ${PROJECT_VERSION_MAJOR}, ${PROJECT_VERSION_MINOR}, ${PROJECT_VERSION_PATCH}\n"
        "#define VER_FILEVERSION_STR      \"${PROJECT_VERSION}\"\n"
        "#define VER_PRODUCTVERSION       VER_FILEVERSION\n"
        "#define VER_PRODUCTVERSION_STR   VER_FILEVERSION_STR\n"
        "#define VER_FILEDESCRIPTION_STR  \"${PROJECT_DESCRIPTION} ${BIT_WIDTH}-bit\"\n"
        "#define VER_INTERNALNAME_STR     \"${MAIN_NAME}\"\n"
        "#define VER_LEGALCOPYRIGHT_STR   \"\"\n"
        "#define VER_ORIGINALFILENAME_STR \"${MAIN_NAME}.exe\"\n"
        "#define VER_PRODUCTNAME_STR      \"${CMAKE_PROJECT_NAME} ${BIT_WIDTH}-bit for Win7, Win8, Win10, Win11\"\n"
        "\n"
        "VS_VERSION_INFO VERSIONINFO\n"
        "FILEVERSION     VER_FILEVERSION,0\n"
        "PRODUCTVERSION  VER_PRODUCTVERSION,0\n"
        "BEGIN\n"
        "    BLOCK \"StringFileInfo\"\n"
        "    BEGIN\n"
        "        BLOCK \"041904E3\"\n"
        "        BEGIN\n"
        "            VALUE \"FileDescription\",    VER_FILEDESCRIPTION_STR \"\\0\"\n"
        "            VALUE \"FileVersion\",        VER_FILEVERSION_STR \"\\0\"\n"
        "            VALUE \"InternalName\",       VER_INTERNALNAME_STR \"\\0\"\n"
        "            VALUE \"LegalCopyright\",     VER_LEGALCOPYRIGHT_STR \"\\0\"\n"
        "            VALUE \"OriginalFilename\",   VER_ORIGINALFILENAME_STR \"\\0\"\n"
        "            VALUE \"ProductName\",        VER_PRODUCTNAME_STR \"\\0\"\n"
        "            VALUE \"ProductVersion\",     VER_PRODUCTVERSION_STR \"\\0\"\n"
        "        END\n"
        "    END\n"
        "\n"
        "    BLOCK \"VarFileInfo\"\n"
        "    BEGIN\n"
        "        VALUE \"Translation\", 0x419, 1251\n"
        "    END\n"
        "END"
    )

    # Путь к файлу ресурсов для сборки исполняемого файла Windows
    set(RESOURCES_DEP "${MISC_PATH}/${MAIN_NAME}.rc")
#    cmake_path(NATIVE_PATH LOCAL_RESOURCES_DEP NORMALIZE RESOURCES_DEP)

    # Добавить флаги для сборки консольного приложения Win32
    add_definitions(
        -DWIN32
        -D_CONSOLE
        -D_UNICODE
        -DUNICODE
    )
endif()

##############################################################################
# Определение исполняемого файла
##############################################################################

# Требуемые компоненты Qt6
find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Gui REQUIRED)
find_package(Qt6 COMPONENTS OpenGL REQUIRED)
find_package(Qt6 COMPONENTS SerialPort REQUIRED)
find_package(Qt6 COMPONENTS Qml REQUIRED)
find_package(Qt6 COMPONENTS OpenGLWidgets REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS UiTools REQUIRED)
find_package(Qt6 COMPONENTS Quick REQUIRED)
find_package(Qt6 COMPONENTS Multimedia REQUIRED)
find_package(Qt6 COMPONENTS MultimediaWidgets REQUIRED)

# Сформировать список файлов с описанием интерфейса
file(GLOB UI "${SOURCES_PATH}/*.ui")

# Зависимости исполняемого файла приложения
qt_add_executable(${MAIN_NAME}
    MACOSX_BUNDLE
    ${SOURCE_FILE_LIST}
    ${SOURCE_HEADERS_LIST}
    ${UI}
    ${RESOURCES_DEP}
)

# Директории с включаемыми файлами
target_include_directories(${MAIN_NAME}
    PRIVATE ${SOURCES_PATH}
    PRIVATE ${SOURCES_PATH}/drawers
    PRIVATE ${SOURCES_PATH}/parser
    PRIVATE ${SOURCES_PATH}/widgets
    PRIVATE ${SOURCES_PATH}/tables
    PRIVATE ${CMAKE_SOURCE_DIR}/src
    PRIVATE ${CMAKE_SOURCE_DIR}/src/designerplugins/cameraplugin
    PRIVATE ${CMAKE_SOURCE_DIR}/src/designerplugins/customwidgetsplugin
    PRIVATE ${CMAKE_SOURCE_DIR}/src/scriptbindings
)

# Сформировать список шрифтов-ресурсов
set(RESOURCE_FONTS_PATH "${SOURCES_PATH}/fonts")
file(GLOB RC_FONTS "${RESOURCE_FONTS_PATH}/*.ttf")
foreach(FONT_PATH ${RC_FONTS})
    file(RELATIVE_PATH FONT_FILENAME "${RESOURCE_FONTS_PATH}" ${FONT_PATH})
    set(RESOURCE_FONTS ${RESOURCE_FONTS} "fonts/${FONT_FILENAME}")
endforeach(FONT_PATH)

# Добавить шрифты-ресурсы к ресурсам исполняемого файла
qt6_add_resources(${MAIN_NAME} "fonts"
    PREFIX "/"
    BIG_RESOURCES
    FILES ${RESOURCE_FONTS}
)

# Сформировать список шейдеров-ресурсов
set(RESOURCE_SHADERS_PATH "${SOURCES_PATH}/shaders")
file(GLOB RC_SHADERS "${RESOURCE_SHADERS_PATH}/*.glsl")
foreach(SHADER_PATH ${RC_SHADERS})
    file(RELATIVE_PATH SHADER_FILENAME "${RESOURCE_SHADERS_PATH}" ${SHADER_PATH})
    set(RESOURCE_SHADERS ${RESOURCE_SHADERS} "shaders/${SHADER_FILENAME}")
endforeach(SHADER_PATH)

# Добавить шейдеры-ресурсы к ресурсам исполняемого файла
qt6_add_resources(${MAIN_NAME} "shaders"
    PREFIX "/"
    BIG_RESOURCES
    FILES ${RESOURCE_SHADERS}
)

# Сформировать список изображений-ресурсов
set(RESOURCE_IMAGES_PATH "${SOURCES_PATH}/images")
file(GLOB RC_IMAGES "${RESOURCE_IMAGES_PATH}/*.ico" "${RESOURCE_IMAGES_PATH}/*.png" "${RESOURCE_IMAGES_PATH}/*.svg")
foreach(IMAGE_PATH ${RC_IMAGES})
    file(RELATIVE_PATH IMAGE_FILENAME "${RESOURCE_IMAGES_PATH}" ${IMAGE_PATH})
    set(RESOURCE_IMAGES ${RESOURCE_IMAGES} "images/${IMAGE_FILENAME}")
endforeach(IMAGE_PATH)

# Добавить изображения-ресурсы к ресурсам исполняемого файла
qt6_add_resources(${MAIN_NAME} "images"
    PREFIX "/"
    BIG_RESOURCES
    FILES ${RESOURCE_IMAGES}
)

# Добавить необходимые библиотеки и библиотеки Qt
target_link_libraries(${MAIN_NAME} PRIVATE
    scriptbindings
    cameraplugin
    customwidgetsplugin
)
target_link_libraries(${MAIN_NAME} PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::OpenGL
    Qt6::SerialPort
    Qt6::Qml
    Qt6::OpenGLWidgets
    Qt6::Widgets
    Qt6::UiTools
    Qt6::Quick
    Qt6::Multimedia
    Qt6::MultimediaWidgets
)

# !!! При сборке для Windows
#if((CMAKE_SYSTEM_NAME STREQUAL "Windows") OR (CMAKE_SYSTEM_NAME STREQUAL "MSYS"))
#    target_link_libraries(${MAIN_NAME} PRIVATE setupapi)
#endif()

##############################################################################
# Настройка ресурса с файлами переводов
##############################################################################

# Подключить подсистему лингвистики Qt
find_package(Qt6 COMPONENTS LinguistTools REQUIRED)

# Добавить файлы переводов в список файлов TS_FILES
#file(GLOB TS_FILES "${SOURCES_PATH}/translations/${MAIN_NAME}_*.ts")

# Обработать файлы перевода без интеграции в исполняемый файл
#qt6_add_translations(${MAIN_NAME}
#    TS_FILES ${TS_FILES}
#    QM_FILES_OUTPUT_VARIABLE QM_FILES
#    LUPDATE_OPTIONS -silent -source-language en_US
#    LRELEASE_OPTIONS -silent
#)

# Обработать файлы перевода приложения для интеграции в исполняемый файл,
# перебрать все поддерживаемые языки
set(QM_FILES "")
FOREACH(L ${QT_LANG})
    string(SUBSTRING ${L} 0 2 LANG_F)

    # Обновить файл перевода
    set(TS_FILE "${SOURCES_PATH}/translations/${MAIN_NAME}_${LANG_F}.ts")
    set(TS_SOURCES ${SOURCE_FILE_LIST} ${SOURCE_HEADERS_LIST} ${UI})
    add_custom_command(
        OUTPUT ${TS_FILE}
        COMMAND ${LUPDATE_CMD} ${TS_SOURCES} -silent -source-language en_US -target-language ${L} -ts ${TS_FILE}
        COMMENT "lupdate ${TS_FILE}"
        DEPENDS ${TS_SOURCES}
    )

    # Скомпилировать файл перевода
    set(QM_FILE "${TRANSLATE_PATH}/${MAIN_NAME}_${LANG_F}.qm")
    add_custom_command(
        OUTPUT ${QM_FILE}
        COMMAND ${LRELEASE_CMD} ${TS_FILE} -silent -qm ${QM_FILE}
        COMMENT "lrelease ${TS_FILE}"
        DEPENDS ${TS_FILE}
    )

    add_custom_target("translation_${MAIN_NAME}__${LANG_F}" ALL
        DEPENDS ${QM_FILE}
    )
    list(APPEND QM_FILES ${QM_FILE})
ENDFOREACH(L)

# Добавить переводы-ресурсы к ресурсам исполняемого файла
qt6_add_resources(${MAIN_NAME} "translations"
    PREFIX "/translations"
    BIG_RESOURCES
    BASE ${TRANSLATE_PATH}
    FILES ${QM_FILES}
)

# Файлы подсистем Qt, для которых требуются переводы
set(QT_SYSTEMS "qt;qtbase;qtmultimedia;qtserialport")

# Определить расположение файлов перевода
if(DEFINED ENV{QT_ROOT})
    set(QT_TBASE "${QT_DIR}/../../../translations")
else()
    set(QT_TBASE "/usr/share/qt6/translations")
endif()

# Перебрать поддерживаемые языки
foreach(L ${QT_LANG})
    string(SUBSTRING ${L} 0 2 LANG_F)
    # Перебрать необходимые файлы перевода
    foreach(I ${QT_SYSTEMS})
        # Добавить файл перевода к списку, установить ему алиас
        if(EXISTS "${QT_TBASE}/${I}_${LANG_F}.qm")
            list(APPEND QM_SYSTEM_FILES "${QT_TBASE}/${I}_${LANG_F}.qm")
        endif()
    endforeach(I)
endforeach(L)

# Добавить системные переводы-ресурсы к ресурсам исполняемого файла
qt6_add_resources(${MAIN_NAME} "system_translations"
    PREFIX "/system_translations"
    BIG_RESOURCES
    BASE ${QT_TBASE}
    FILES ${QM_SYSTEM_FILES}
)

##############################################################################
# Настройка свойств в зависимости от целевой среды выполнения.
##############################################################################

# При сборке для работы в среде Windows
if ((CMAKE_SYSTEM_NAME STREQUAL "Windows") OR (CMAKE_SYSTEM_NAME STREQUAL "MSYS"))

    set_target_properties(${MAIN_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )

# При сборке для работы в среде MacOS/OS X
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")

    set_target_properties(${MAIN_NAME} PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST "${SOURCES_PATH}/Info.plist.in"
        MACOSX_BUNDLE_GUI_IDENTIFIER my.application.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE_ICON_FILE not_yet.icns
        MACOSX_BUNDLE TRUE
    )

# При сборке для работы в среде Linux
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")

endif()


##############################################################################
# Установка
##############################################################################

if (CMAKE_CROSSCOMPILING)
    message(DEBUG "Кросскомпиляция -- установка не будет производиться")
else()
    # Если исполняемый файл собран под Linux для выполнения под Linux
    if ((CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux") AND (CMAKE_SYSTEM_NAME STREQUAL "Linux"))
        # Установка исполняемого файла в ~/.local/bin
        message(DEBUG "Предусмотрена установка для выполнения под Linux")
#       install(TARGETS ${MAIN_NAME} RUNTIME DESTINATION "~/.local/bin")
    endif()
    # Если исполняемый файл собран под Windows для выполнения под Windows
    if ((CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows") AND (CMAKE_SYSTEM_NAME STREQUAL "Windows"))
        # Установка исполняемого файла в C:/Program Files/???
        message(DEBUG "Предусмотрена установка для выполнения под Windows")
#       install(TARGETS ${MAIN_NAME} RUNTIME) # DESTINATION "C:/Program Files/????")
    endif()
    # Если исполняемый файл собран под MacOS/OS X для выполнения под MacOS/OS X
    if ((CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin") AND (CMAKE_SYSTEM_NAME STREQUAL "Darwin"))
        # Установка исполняемого файла в /Applications/???
        message(DEBUG "Предусмотрена установка для выполнения под MacOS/OS X")
#       install(TARGETS ${MAIN_NAME} RUNTIME) # DESTINATION "/Applications/????")
    endif()
endif()

##############################################################################
# Формирование установочного набора
##############################################################################

# Вывод сообщений об установке только если было изменение
set(CMAKE_INSTALL_MESSAGE LAZY)

# Для мультиконфигурации учесть директорию, в которой будет расположен результат сборки,
# значение которой будет определено в параметре cmake --config только на этапе сборки
#if (isMultiConfig)
#    set(BINPATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>")
#else()
#    set(BINPATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
#endif()


# Исполняемый файл
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # При сборке для работы в среде MacOS/OS X
#    install(DIRECTORY ${BINPATH}/${MAIN_NAME}.app
#        DESTINATION "./"
#        USE_SOURCE_PERMISSIONS
#        COMPONENT application
#    )


    install(TARGETS ${MAIN_NAME}
      RUNTIME DESTINATION ""
      BUNDLE DESTINATION "${CMAKE_INSTALL_PREFIX}"
    )


else()
#    install(FILES ${BINPATH}/${MAIN_NAME}${CMAKE_EXECUTABLE_SUFFIX}
#        DESTINATION "./" # ${DEST_PATH}
#        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
#        COMPONENT application
#    )
    install(TARGETS ${MAIN_NAME}
      RUNTIME DESTINATION ""
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

endif()
