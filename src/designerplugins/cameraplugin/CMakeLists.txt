##############################################################################
# Информация о компоненте
##############################################################################

# Имя проекта приложения
set(MAIN_NAME "cameraplugin")

# Вывод информации о собираемом компоненте
message(STATUS "##############################################################################")
message(STATUS "Проект '${CMAKE_PROJECT_NAME}', компонент '${MAIN_NAME}'")
message(STATUS "##############################################################################")

##############################################################################
# Директории с файлами, необходимыми для сборки
##############################################################################

# Список заголовков исходных текстов приложения
file(GLOB SOURCE_HEADERS_LIST
    ${CMAKE_SOURCE_DIR}/src/designerplugins/cameraplugin/*.h
    ${CMAKE_SOURCE_DIR}/src/*.h
)

# Список файлов c++ исходных текстов приложения
file(GLOB SOURCE_FILE_LIST
    ${CMAKE_SOURCE_DIR}/src/designerplugins/cameraplugin/*.cpp
)

# Определение для сборки библиотеки
add_definitions(-DCUSTOMWIDGETS_EXPORT)

##############################################################################
# Определение исполняемого файла
##############################################################################

# Требуемые компоненты Qt6
find_package(QT NAMES Qt6 COMPONENTS Core REQUIRED)
find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
find_package(QT NAMES Qt6 COMPONENTS Designer REQUIRED)
find_package(QT NAMES Qt6 COMPONENTS Multimedia REQUIRED)
find_package(QT NAMES Qt6 COMPONENTS MultimediaWidgets REQUIRED)
find_package(QT NAMES Qt6 COMPONENTS OpenGLWidgets REQUIRED)

# Определение собираемой библиотеки, её зависимости
add_library(${MAIN_NAME} SHARED
    ${SOURCE_FILE_LIST}
    ${SOURCE_HEADERS_LIST}
)

# Директории с включаемыми файлами
target_include_directories(${MAIN_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}/src/designerplugins/cameraplugin
    PRIVATE ${CMAKE_SOURCE_DIR}/src
)

# Добавить библиотеки Qt
target_link_libraries(${MAIN_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Designer
    Qt6::Multimedia
    Qt6::MultimediaWidgets
    Qt6::OpenGLWidgets
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
if (isMultiConfig)
    set(BINPATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIG>")
else()
    set(BINPATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
endif()

# Библиотека
install(FILES ${BINPATH}/${CMAKE_SHARED_LIBRARY_PREFIX}${MAIN_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}
    DESTINATION ${DEST_PATH}
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)
