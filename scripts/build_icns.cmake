##############################################################################
# Скрипт формирования значков icns
# Аргументы:
# ICONS_PATH - путь, по которому расположены файлы PNG
# MISC_PATH - путь для размещения временных файлов
# ICNS_FILE - путь/имя созданного значка ICNS
##############################################################################

# Список исходных и результирующих имён файлов PNG
set(PNG_LIST
  "16"   "16x16"
  "32"   "16x16@2x"
  "32"   "32x32"
  "64"   "32x32@2x"
  "128"  "128x128"
  "256"  "128x128@2x"
  "256"  "256x256"
  "512"  "256x256@2x"
  "512"  "512x512"
  "1024" "512x512@2x"
)

# Директория для заготовок значков Mac OS/OSX
set(ICNS_PATH "${MISC_PATH}/icns.iconset")
file(MAKE_DIRECTORY ${ICNS_PATH})
#execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${ICNS_PATH})

# Выполнить копирование и переименование битмапов
# согласно списка PNG_LIST
list(LENGTH PNG_LIST PNG_LIST_LEN)
math(EXPR PNG_LIST_LEN "${PNG_LIST_LEN} - 2") 
foreach(pos0 RANGE 0 "${PNG_LIST_LEN}" 2)
    math(EXPR pos1 "${pos0} + 1") 
    list(GET PNG_LIST "${pos0}" PNG_SRC)
    list(GET PNG_LIST "${pos1}" PNG_DST)
    file(COPY_FILE
      "${ICONS_PATH}/icon_${PNG_SRC}.png"
      "${ICNS_PATH}/icon_${PNG_DST}.png"
    )
endforeach()

# Преобразовать файлы PNG в файл ICNS
execute_process(COMMAND
  iconutil
  -c icns
  "${ICNS_PATH}"
  -o "${ICNS_FILE}"
  RESULT_VARIABLE result
  OUTPUT_VARIABLE output
  ERROR_VARIABLE  output_error
)
if(NOT result EQUAL 0)
  message(FATAL_ERROR "Ошибка выполнения скрипта build_icns: ${output_error}")
endif()

file(REMOVE_RECURSE "${ICNS_PATH}")
