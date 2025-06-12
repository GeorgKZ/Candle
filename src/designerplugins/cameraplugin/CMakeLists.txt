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

# Путь к директории с исходными текстами
set(SOURCES_PATH "${CMAKE_SOURCE_DIR}/src/designerplugins/cameraplugin")

# Список заголовков исходных текстов приложения
file(GLOB SOURCE_HEADERS_LIST
    ${SOURCES_PATH}/*.h
)

# Добавить директории с заголовочными файлами приложения
include_directories(${SOURCES_PATH})

# Список файлов c++ исходных текстов приложения
file(GLOB SOURCE_FILE_LIST
    ${SOURCES_PATH}/*.cpp
)

# Определение для сборки библиотеки
add_definitions(-DCUSTOMWIDGETS_EXPORT)

##############################################################################
# Определение исполняемого файла
##############################################################################

# Требуемые компоненты Qt6
find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Designer REQUIRED)
find_package(Qt6 COMPONENTS Multimedia REQUIRED)
find_package(Qt6 COMPONENTS MultimediaWidgets REQUIRED)
find_package(Qt6 COMPONENTS OpenGLWidgets REQUIRED)

# Зависимости исполняемого файла приложения
add_library(${MAIN_NAME} SHARED
    ${SOURCE_FILE_LIST}
    ${SOURCE_HEADERS_LIST}
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

if(WIN32)
    target_link_libraries(${MAIN_NAME} PRIVATE setupapi)
endif()

#set_target_properties(${MAIN_NAME} PROPERTIES OUTPUT_NAME "${MAIN_NAME}${SUFFIX}")

##############################################################################
# Формирование установочного набора
##############################################################################

# Вывод сообщений об установке только если было изменение
set(CMAKE_INSTALL_MESSAGE LAZY)

# Библиотека
install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_SHARED_LIBRARY_PREFIX}${MAIN_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}
    DESTINATION ${DEST_PATH}
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
