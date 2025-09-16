set(qt_mirrors "mirrors.ukfast.co.uk/sites/qt.io;ftp.fau.de/qtproject;mirrors.sau.edu.cn/qt;mirrors.ocf.berkeley.edu/qt")
set(qt_version "6.9.2")
#
string(REPLACE "." "" qt_version_dotless "${qt_version}")
#
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(ARCH_PATH "T:/archive")
    set(url_os "windows_x86")
    set(compiler_id1 "msvc2022_64")
    set(compiler_id "win64_msvc2022_64")
    set(qt_dir "C:/QT_${qt_version_dotless}")
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    set(ARCH_PATH "/var/tmp/archive")
    set(url_os "linux_x64")
    set(compiler_id1 "gcc_64")
    set(compiler_id "linux_gcc_64")
    set(qt_dir "/opt/qt${qt_version_dotless}")
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    set(ARCH_PATH "/tmp/archive")
    set(url_os "mac_x64")
    set(compiler_id1 "macos")
    set(compiler_id "clang_64")
    set(qt_dir "/opt/qt${qt_version_dotless}")
endif()
#
message(STATUS "Загрузка Qt ${qt_version} в ${qt_dir}")
file(MAKE_DIRECTORY "${qt_dir}")
#
# Пробовать загружать последовательно с каждого зеркала
foreach(mirror ${qt_mirrors})
    set(qt_base_url "https://${mirror}/online/qtsdkrepository/${url_os}/desktop/qt6_${qt_version_dotless}/qt6_${qt_version_dotless}")
    #
    # Выполнить 10 попыток загрузки файла Updates.xml
    foreach(retry RANGE 10)
        message(STATUS "Загрузка Updates.xml")
        cmake_language(EVAL CODE
          "file(DOWNLOAD \"${qt_base_url}/Updates.xml\" \"${ARCH_PATH}/Updates.xml\")"
        )
        file(SIZE ${ARCH_PATH}/Updates.xml fileSize)
        if (fileSize GREATER 0)
            break()
        endif()
    endforeach()
    #
    # Если за 10 попыток файл Updates.xml не загрузился, перейти к следующему зеркалу
    file(SIZE ${ARCH_PATH}/Updates.xml fileSize)
    if (fileSize EQUAL 0)
        continue()
    endif()
    #
    # Прочитать файл Updates.xml в переменную
    file(READ ${ARCH_PATH}/Updates.xml updates_xml)
    #
    # Получить блоки XML-описаний для указанного компилятора без отладочной информации
    string(REGEX REPLACE "<PackageUpdate>" ";<PackageUpdate>" sections "${updates_xml}")
    list(FILTER sections EXCLUDE REGEX "<Name>.*debug.*</Name>")
    list(FILTER sections INCLUDE REGEX "<Name>.*${compiler_id}.*</Name>") # <>qt.qt6.692.clang_64<>
    #
    # Последовательно обработать все блоки XML-описаний
    foreach(section ${sections})
        string(REGEX MATCH "<DisplayName>(.*)</DisplayName>" match "${section}")
        set(display_name ${CMAKE_MATCH_1})
        string(REGEX MATCH "<Name>(.*)</Name>" match "${section}")
        set(name ${CMAKE_MATCH_1})
        string(REGEX MATCH "<Version>(.*)</Version>" match "${section}")
        set(version ${CMAKE_MATCH_1})
        #
        message(STATUS "Загрузка ${display_name}")

        set(dest_list "")
        set(arch_list "")
        set(PREFIX "@TargetDir@/${qt_version}/${compiler_id1}")
        string(REGEX MATCHALL "<Argument>([^<]+)</Argument>" matches "${section}")
        foreach(match IN LISTS matches)
            string(REGEX REPLACE "<[^>]+>([^<]+)</[^>]+>" "\\1" content "${match}")
            if(content MATCHES "^${PREFIX}")
                string(REPLACE "${PREFIX}" "" content "${content}")
                if(^^${content} STREQUAL "^^")
                   list(APPEND dest_list ".")
                else()
                   list(APPEND dest_list ${content})
                endif()
            else()
                list(APPEND arch_list ${content})
            endif()
        endforeach(match)
        list(LENGTH arch_list arch_list_len)

        math(EXPR len "${arch_list_len} - 1")

        foreach(i RANGE 0 ${len})
            list(GET dest_list ${i} arg1)
            list(GET arch_list ${i} arg2)
            message(STATUS "ARG: ${arg1} <- ${arg2}")
        endforeach(i)

        string(REGEX MATCH "<DownloadableArchives>(.*)</DownloadableArchives>" match "${section}")
        set(archive_list ${CMAKE_MATCH_1})
        #
        # Заменить запятую с пробелом на точку с запятой
        string(REPLACE ", " ";" archive_list "${archive_list}")
        # Перебрать элементы списка
        foreach(archive ${archive_list})
            # Выполнить 10 попыток загрузки архива
            foreach(retry RANGE 10)
#                cmake_language(EVAL CODE
#                  "file(DOWNLOAD \"${qt_base_url}/${name}/${version}${archive}\" \"${ARCH_PATH}/${archive}\")"
#                )
                # Если загрузка успешна (размер файла не равен нулю), завершить попытки загрузки
                file(SIZE "${ARCH_PATH}/${archive}" fileSize)
                if (fileSize GREATER 0)
                    break()
                endif()
            endforeach(retry)
            message(STATUS "Разжатие ${archive}")
#            execute_process(COMMAND ${CMAKE_COMMAND} -E tar xvf "${ARCH_PATH}/${archive}"
#              WORKING_DIRECTORY "${qt_dir}"
#              OUTPUT_QUIET
#            )
        endforeach(archive)
    endforeach(section)
    #
    # Завершить перебор зеркал
    break()
endforeach(mirror)

# для Windows поместить системные библиотеки в директорию Qt, чтобы их было проще собрать в установочный пакет
if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    foreach(file vcruntime140.dll concrt140.dll msvcp140_1.dll msvcp140_2.dll
                 msvcp140_codecvt_ids.dll vcruntime140_1.dll msvcp140.dll)
    file(INSTALL "C:/Windows/System32/${file}"
      DESTINATION "qt/bin")
    endforeach()
endif()
