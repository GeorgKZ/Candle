##############################################################################
# Информация о компоненте
##############################################################################

# Имя компонента по имени директории, содержащей компонент
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR STEM LAST_ONLY MAIN_NAME)

# Вывод информации о собираемом компоненте
message(STATUS "##############################################################################")
message(STATUS "Проект '${CMAKE_PROJECT_NAME}', компонент '${MAIN_NAME}'")
message(STATUS "##############################################################################")

##############################################################################
# Директории с файлами, необходимыми для сборки
##############################################################################

# Список заголовков исходных текстов приложения
file(GLOB SOURCE_HEADERS_LIST
    ${CMAKE_SOURCE_DIR}/src/designerplugins/customwidgetsplugin/*.h
    ${CMAKE_SOURCE_DIR}/src/*.h
)

# Список файлов c++ исходных текстов приложения
file(GLOB SOURCE_FILE_LIST
    ${CMAKE_SOURCE_DIR}/src/designerplugins/customwidgetsplugin/*.cpp
)

# Список файлов, описывающих интерфейс
set(UI
    ${CMAKE_SOURCE_DIR}/src/designerplugins/customwidgetsplugin/sliderbox.ui
)

# Определение для сборки библиотеки
add_definitions("-DCUSTOMWIDGETS_EXPORT")

##############################################################################
# Определение исполняемого файла
##############################################################################

find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS UiPlugin REQUIRED)
find_package(Qt6 COMPONENTS Multimedia REQUIRED)
find_package(Qt6 COMPONENTS MultimediaWidgets REQUIRED)

# Определение собираемой библиотеки, её зависимости
add_library(${MAIN_NAME} SHARED
        ${SOURCE_FILE_LIST}
        ${SOURCE_HEADERS_LIST}
        ${UI}
)

# Директории с включаемыми файлами
target_include_directories(${MAIN_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}/src/designerplugins/customwidgetsplugin
    PRIVATE ${CMAKE_SOURCE_DIR}/src
)

# Добавить библиотеки Qt
target_link_libraries(${MAIN_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::UiPlugin
    Qt6::Multimedia
    Qt6::MultimediaWidgets
    )

#if(WIN32)
#    target_link_libraries(${MAIN_NAME} PRIVATE setupapi)
#endif()

#set_target_properties(${MAIN_NAME} PROPERTIES OUTPUT_NAME "${MAIN_NAME}${SUFFIX}")

##############################################################################
# Формирование установочного набора
##############################################################################

# Вывод сообщений об установке только если было изменение
set(CMAKE_INSTALL_MESSAGE LAZY)

# Для мультиконфигурации учесть директорию, в которой будет расположен результат сборки,
# значение которой будет определено в параметре cmake --config только на этапе сборки
#if (isMultiConfig)
#    set(BINPATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIG>")
#else()
#    set(BINPATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
#endif()
# Библиотека
#install(FILES ${BINPATH}/${CMAKE_SHARED_LIBRARY_PREFIX}${MAIN_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}
#    DESTINATION "./"
#    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
#    COMPONENT libraries
#)

# Библиотека
install(TARGETS ${MAIN_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
