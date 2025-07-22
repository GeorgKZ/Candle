##############################################################################
# Информация о компоненте
##############################################################################

# Имя проекта приложения
set(MAIN_NAME "scriptbindings")

# Вывод информации о собираемом компоненте
message(STATUS "##############################################################################")
message(STATUS "Проект '${CMAKE_PROJECT_NAME}', компонент '${MAIN_NAME}'")
message(STATUS "##############################################################################")

##############################################################################
# Директории с файлами, необходимыми для сборки
##############################################################################

# Список заголовков исходных текстов приложения
file(GLOB SOURCE_HEADERS_LIST
    ${CMAKE_SOURCE_DIR}/src/scriptbindings/*.h
)

# Список файлов c++ исходных текстов приложения
file(GLOB SOURCE_FILE_LIST
    ${CMAKE_SOURCE_DIR}/src/scriptbindings/*.cpp
)

# Определение для сборки библиотеки
add_definitions(-DWRAPPER_EXPORT_SYMBOLS)

##############################################################################
# Определение исполняемых файлов
##############################################################################

# Требуемые компоненты Qt6
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Qml)
find_package(Qt6 REQUIRED COMPONENTS UiTools)

# Определение собираемой библиотеки, её зависимости
add_library(${MAIN_NAME} SHARED
    ${SOURCE_FILE_LIST}
    ${SOURCE_HEADERS_LIST}
)

# Директории с включаемыми файлами
target_include_directories(${MAIN_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}/src/scriptbindings
    PRIVATE ${CMAKE_SOURCE_DIR}/src/designerplugins/cameraplugin
    PRIVATE ${CMAKE_SOURCE_DIR}/src/designerplugins/customwidgetsplugin
    PRIVATE ${CMAKE_SOURCE_DIR}/src
)

# Добавить необходимые библиотеки и библиотеки Qt
target_link_libraries(${MAIN_NAME} PRIVATE
    customwidgets
    cameraplugin
    Qt6::Core
    Qt6::Widgets
    Qt6::Qml
    Qt6::UiTools
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
    LIBRARY
    DESTINATION "./"
    COMPONENT libraries
)
