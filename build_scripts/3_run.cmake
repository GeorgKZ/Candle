  cmake_minimum_required(VERSION 3.9...3.28)

##############################################################################
# Функция удаления файла нулевой длины
##############################################################################
  include(build_remove_zerofile.cmake)

##############################################################################
# Настройка окружения
##############################################################################

  include(build_set_builddir.cmake)

##############################################################################
# Настройка шаблона журналирования
##############################################################################

  # Вывод всех сообщений с указанием даты, времени, файла, строки
  set(MESSAGE_PATTERN_ALL "[%{time dd.MM.yyyy h:mm:ss.zzz}] %{if-debug}DEBUG%{endif}%{if-info}INFO%{endif}%{if-warning}WARNING%{endif}%{if-critical}CRITICAL%{endif}%{if-fatal}FATAL%{endif} %{file}:%{line} - %{message}")
  # Вывод только ошибок CRITICAL и FATAL
  set(MESSAGE_PATTERN_ERROR "%{if-critical}CRITICAL %{message}%{endif}%{if-fatal}FATAL %{message}%{endif}")
  # Вывод ошибок CRITICAL, FATAL и предупреждений WARNING
  set(MESSAGE_PATTERN_WARNING "%{if-critical}CRITICAL %{message}%{endif}%{if-fatal}FATAL %{message}%{endif}%{if-warning}WARNING %{message}%{endif}")
  # Вывод ошибок CRITICAL, FATAL, предупреждений WARNING и информационных сообщений INFO
  set(MESSAGE_PATTERN_INFO "%{if-critical}CRITICAL %{message}%{endif}%{if-fatal}FATAL %{message}%{endif}%{if-warning}WARNING %{message}%{endif}%{if-info}INFO %{message}%{endif}")
  # Вывод ошибок CRITICAL, FATAL, предупреждений WARNING, информационных сообщений INFO и трассировочных сообщения DEBUG
  set(MESSAGE_PATTERN_DEBUG "%{if-critical}CRITICAL %{message}%{endif}%{if-fatal}FATAL %{message}%{endif}%{if-warning}WARNING %{message}%{endif}%{if-info}INFO %{message}%{endif}%{if-debug}DEBUG %{message}%{endif}")

  # При компиляции можно указать QT_NO_DEBUG_OUTPUT, QT_NO_INFO_OUTPUT, or QT_NO_WARNING_OUTPUT
  set(ENV{QT_MESSAGE_PATTERN} "${MESSAGE_PATTERN_DEBUG}")

##############################################################################
# Запуск программы
##############################################################################

  file(REMOVE "${BUILDDIR}/log_run.txt")
  file(REMOVE "${BUILDDIR}/log_run_errors.txt")

  # Вывод информации о работе с плюгинами Qt
  set(ENV{QT_DEBUG_PLUGINS} 1)

  # для Windows
  if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")

      # Выполнить приложение
      execute_process(
        COMMAND "cmd" "/c"
        ${BUILDDIR}/install/candle.exe
        -DEBUG
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE  output_error
        ECHO_OUTPUT_VARIABLE ECHO_ERROR_VARIABLE
      )
      if (result EQUAL 0)
          message(STATUS "Run: Выполнение успешно завершено.")
      else()
          message(FATAL_ERROR "Run: Выполнение завершено с ошибкой ${result}. Выход.")
      endif()

  # для MacOS
  elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")

      # Выполнить приложение
      execute_process(
        COMMAND open -a ${BUILDDIR}/install/candle.app
        --stdout ${BUILDDIR}/log_run.txt
        --args -DEBUG
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE  output_error
        ECHO_OUTPUT_VARIABLE ECHO_ERROR_VARIABLE
      )
      if (result EQUAL 0)
          message(STATUS "Run: Запуск успешно выполнен.")
      else()
          message(FATAL_ERROR "Run: Запуск завершён с ошибкой ${result}. Выход.")
      endif()

  # для Linux
  elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")

#     set(ENV{QT_PLUGIN_PATH}  ${BUILDDIR}/install/lib/candle/plugins)

      # Выполнить приложение
      execute_process(
        COMMAND ${BUILDDIR}/install/bin/candle
        -DEBUG
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE  output_error
        ECHO_OUTPUT_VARIABLE ECHO_ERROR_VARIABLE
      )
      if (result EQUAL 0)
          message(STATUS "Run: Выполнение успешно завершено.")
      else()
          message(FATAL_ERROR "Run: Выполнение завершено с ошибкой ${result}. Выход.")
      endif()
  endif()

  if(NOT "^^${output}" STREQUAL "^^")
      file(WRITE "${BUILDDIR}/log_run.txt" "${output}")
  endif()
  if(NOT "^^${output_error}" STREQUAL "^^")
      file(WRITE "${BUILDDIR}/log_run_errors.txt" "${output_error}")
  endif()
