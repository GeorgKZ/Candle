##############################################################################
# Информация о компоненте
##############################################################################

# Имя компонента по имени директории, содержащей компонент
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR STEM LAST_ONLY MAIN_NAME)

##############################################################################
# Директории с файлами, необходимыми для сборки
##############################################################################

# Путь к директории с плюгинами
set(SOURCES_PATH "${CMAKE_CURRENT_SOURCE_DIR}") # "${CMAKE_SOURCE_DIR}/src/candleplugins")

##############################################################################
# Настройка в зависимости от целевой среды выполнения.
##############################################################################

# При сборке для работы в среде Linux
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")

    # Путь для установки плюгинов
    set(DEST_DIR "./share/candle/plugins")

# При сборке для работы в среде MacOS/OS X
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")

    # Путь для установки плюгинов
    set(DEST_DIR "./candle.app/Contents/Resources/candle_plugins")

# При сборке для работы в среде Windows
elseif ((CMAKE_SYSTEM_NAME STREQUAL "Windows") OR (CMAKE_SYSTEM_NAME STREQUAL "MSYS"))

    # Путь для установки плюгинов
    set(DEST_DIR "./candle_plugins")

else()
    message(WARNING "Неизвестная среда сборки " ${CMAKE_SYSTEM_NAME})
endif()


##############################################################################
# Обработка файлов с переводом
##############################################################################

find_package(Qt6 REQUIRED COMPONENTS LinguistTools)

file(GLOB SUBDIRS RELATIVE ${SOURCES_PATH} ${SOURCES_PATH}/*)
foreach(I ${SUBDIRS})
    if(IS_DIRECTORY ${SOURCES_PATH}/${I} AND EXISTS ${SOURCES_PATH}/${I})

        # Вывод информации о собираемом компоненте
        message(STATUS "##############################################################################")
        message(STATUS "Проект '${CMAKE_PROJECT_NAME}', компонент '${MAIN_NAME}': ${I}")
        message(STATUS "##############################################################################")

        set(PLUGIN_PATH "${SOURCES_PATH}/${I}")
        set(SRC_FILES "")
        IF(EXISTS ${PLUGIN_PATH}/settings.ui)
            LIST(APPEND SRC_FILES ${PLUGIN_PATH}/settings.ui)
        ENDIF()
        IF(EXISTS ${PLUGIN_PATH}/widget.ui)
            LIST(APPEND SRC_FILES ${PLUGIN_PATH}/widget.ui)
        ENDIF()

        # Перебрать все поддерживаемые языки
        set(QM_FILES "")
        FOREACH(L ${QT_LANG})
            string(SUBSTRING ${L} 0 2 LANG_F)

            # Обновить файл перевода
            set(TS_FILE "${PLUGIN_PATH}/${I}_${LANG_F}.ts")
            add_custom_command(
                OUTPUT ${TS_FILE}
                COMMAND ${LUPDATE_CMD} ${SRC_FILES} -silent -source-language en_US -target-language ${L} -ts ${TS_FILE}
                COMMENT "lupdate ${TS_FILE}"
                DEPENDS ${SRC_FILES}
            )

            # Скомпилировать файл перевода
            set(QM_FILE "${TRANSLATE_PATH}/${I}_${LANG_F}.qm")
            add_custom_command(
                OUTPUT ${QM_FILE}
                COMMAND ${LRELEASE_CMD} ${TS_FILE} -silent -qm ${QM_FILE}
                COMMENT "lrelease ${TS_FILE}"
                DEPENDS ${TS_FILE}
            )

            add_custom_target("translation_${I}__${LANG_F}" ALL
                DEPENDS ${QM_FILE}
            )

            list(APPEND QM_FILES ${QM_FILE})

        ENDFOREACH(L)
    ENDIF()
ENDFOREACH(I)

##############################################################################
# Формирование установочного набора
##############################################################################

# Вывод сообщений об установке только если было изменение
set(CMAKE_INSTALL_MESSAGE LAZY)

file(GLOB SUBDIRS RELATIVE ${SOURCES_PATH} ${SOURCES_PATH}/*)
foreach(I ${SUBDIRS})
    if(IS_DIRECTORY ${SOURCES_PATH}/${I} AND EXISTS ${SOURCES_PATH}/${I})

        install(FILES
            ${PLUGIN_PATH}/script.js
            ${SRC_FILES}
            ${QM_FILES}
            DESTINATION "${DEST_DIR}/${I}"
            COMPONENT plugins
        )

        # Установка изображений (при наличии)
        SET(IMG_PATH "${PLUGIN_PATH}/images")
        IF(IS_DIRECTORY ${IMG_PATH} AND EXISTS ${IMG_PATH})
            FILE(GLOB IMG_FILES ${IMG_PATH}/*)
            install(FILES ${IMG_FILES}
                DESTINATION "${DEST_DIR}/${I}/images"
                COMPONENT plugins
            )
        ENDIF()
    ENDIF()
ENDFOREACH(I)
