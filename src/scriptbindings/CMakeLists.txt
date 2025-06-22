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

# Путь к директории с исходными текстами
set(SOURCES_PATH "${CMAKE_SOURCE_DIR}/src/scriptbindings")

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
add_definitions(-DWRAPPER_EXPORT_SYMBOLS)

##############################################################################
# Определение исполняемых файлов
##############################################################################

# Требуемые компоненты Qt6
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Qml)
find_package(Qt6 REQUIRED COMPONENTS UiTools)

# Зависимости исполняемого файла приложения
add_library(${MAIN_NAME} SHARED
    ${SOURCE_FILE_LIST}
    ${SOURCE_HEADERS_LIST}
)

# Дополнения для macOS/OS X
if(APPLE)
#    add_library(${MAIN_NAME} SHARED
#        MACOSX_BUNDLE
#    )
    set_target_properties(${MAIN_NAME}
        PROPERTIES MACOSX_BUNDLE_INFO_PLIST
        ${PROJECT_SOURCE_DIR}/macos/Info.plist
    )
endif()

# Добавить необходимые библиотеки и библиотеки Qt
target_link_libraries(${MAIN_NAME} PRIVATE
    customwidgets
    cameraplugin
    Qt6::Core
    Qt6::Widgets
    Qt6::Qml
    Qt6::UiTools
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
