##############################################################################
# Информация о компоненте
##############################################################################

# Имя компонента по имени директории, содержащей компонент
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR STEM LAST_ONLY MAIN_NAME)

##############################################################################
# Обработка файлов с переводом
##############################################################################

find_package(Qt6 REQUIRED COMPONENTS LinguistTools)

file(GLOB SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
foreach(I ${SUBDIRS})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${I} AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${I})

        # Вывод информации о собираемом компоненте
        message(STATUS "##############################################################################")
        message(STATUS "Проект '${CMAKE_PROJECT_NAME}', компонент '${MAIN_NAME}': ${I}")
        message(STATUS "##############################################################################")

        set(PLUGIN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${I}")
        set(SRC_FILES "")
        if(EXISTS ${PLUGIN_PATH}/settings.ui)
            list(APPEND SRC_FILES ${PLUGIN_PATH}/settings.ui)
        endif()
        if(EXISTS ${PLUGIN_PATH}/widget.ui)
            list(APPEND SRC_FILES ${PLUGIN_PATH}/widget.ui)
        endif()

        # Перебрать все поддерживаемые языки
        foreach(L ${QT_LANG})
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
        endforeach(L)
    endif()
endforeach(I)

##############################################################################
# Формирование установочного набора
##############################################################################

# Вывод сообщений об установке только если было изменение
set(CMAKE_INSTALL_MESSAGE LAZY)

file(GLOB SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
foreach(I ${SUBDIRS})

    set(PLUGIN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${I}")
    if(IS_DIRECTORY ${PLUGIN_PATH} AND EXISTS ${PLUGIN_PATH})

        # Установка яваскриптов и файлов ui
        file(GLOB UI_FILES ${PLUGIN_PATH}/*.ui)
        install(FILES
            ${PLUGIN_PATH}/script.js
            ${UI_FILES}
            DESTINATION ${INST_PLUG_DIR}/${I}
        )

        # Установка скомпилированных файлов перевода
        foreach(L ${QT_LANG})
            string(SUBSTRING ${L} 0 2 LANG_F)
            install(FILES
                "${TRANSLATE_PATH}/${I}_${LANG_F}.qm"
                DESTINATION ${INST_PLUG_DIR}/${I}
            )
        endforeach(L)

        # Установка изображений (при наличии)
        set(IMG_PATH "${PLUGIN_PATH}/images")
        if(IS_DIRECTORY ${IMG_PATH} AND EXISTS ${IMG_PATH})
            file(GLOB IMG_FILES ${IMG_PATH}/*)
            install(FILES ${IMG_FILES}
                DESTINATION ${INST_PLUG_DIR}/${I}/images
            )
        endif()
    endif()
endforeach(I)
