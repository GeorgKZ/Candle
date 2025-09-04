##############################################################################
# Информация о компоненте
##############################################################################

# Имя компонента по имени директории, содержащей компонент
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR STEM LAST_ONLY MAIN_NAME)

# Вывод информации о собираемом компоненте
message(STATUS "##############################################################################")
message(STATUS "Проект '${CMAKE_PROJECT_NAME}', компонент '${MAIN_NAME}'")
message(STATUS "##############################################################################")

# RPATH, который будет использован на этапе установки
set(CMAKE_INSTALL_RPATH "\$ORIGIN")

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
foreach(lib ${QT_MODULES_LIST})
    find_package(Qt6 COMPONENTS ${lib} REQUIRED)
endforeach(lib)

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
foreach(lib ${QT_MODULES_LIST})
    target_link_libraries(${MAIN_NAME} PUBLIC
        Qt6::${lib}
    )
endforeach(lib)

# Подготовка к поиску набора динамических библиотек, от которых зависит цель
add_custom_target(get_deps_${MAIN_NAME} ALL
  ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:${MAIN_NAME}>" "${FIND_DEPS_PATH}/"
  COMMENT "Подготовка к поиску зависимостей цели ${MAIN_NAME}"
)
add_dependencies(get_deps_${MAIN_NAME} ${MAIN_NAME})
