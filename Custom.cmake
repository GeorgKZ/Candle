##############################################################################
# Информация о проекте
##############################################################################

# Имя, версия, описание проекта
set(CUSTOM_PROJECT_NAME "Candle")
set(CUSTOM_VERSION "1.2.15.1")
set(CUSTOM_DESCRIPTION "GRBL controller application with G-Code visualizer")
set(CUSTOM_HOMEPAGE_URL "https://github.com/GeorgKZ/Candle")
set(CUSTOM_LANGUAGES CXX)

# Поставщик установочного пакета
set(CUSTOM_PROJECT_VENDOR "GeorgKZ")

# Контактные данные поставщика установочного пакета
set(CUSTOM_PROJECT_MAINTAINER "${PROJECT_VENDOR} https://github.com/GeorgKZ")

# Путь к файлу значка SVG проекта
set(CUSTOM_SVG_ICON_FILE "${CMAKE_SOURCE_DIR}/icons/icon.svg")

# Список компонентов проекта с путями, которые включаются как поддиректории
set(PROJECT_MODULES_LIST
  "designerplugins/cameraplugin"
  "designerplugins/customwidgetsplugin"
  "scriptbindings"
  "candle"
  "candleplugins"
)

# Путь к директории с изображениями для Doxygen
set(CUSTOM_IMAGES "${CMAKE_SOURCE_DIR}/screenshots;${CMAKE_SOURCE_DIR}/doc/images;${CMAKE_SOURCE_DIR}/wiki/images")

#  Использовать MathJax, использовать расширения
set(CUSTOM_MATHJAX require ams mathtools textcomp unicode)

##############################################################################
# Настройки Qt
##############################################################################

# Список необходимых для приложения плюгинов
set(QT_PLUGIN_LIST
  "accessible"
  "accessiblebridge"
  "iconengines"
  "imageformats"
  "multimedia"
  "permissions"
  "platforminputcontexts"
  "platforms"
  "platformthemes"
  "styles"
  "xcbglintegrations"
)

# Подсистемы Qt, для которых требуются переводы
set(QT_SYSTEMS "qt;qtbase;qtdesigner;qtmultimedia;qtserialport")

# Список необходимых для приложения модулей Qt
set(QT_MODULES_LIST
  "Core"                 # candle scriptbindings camera customdesigner
  "Designer"             #                       camera
  "Gui"                  # candle
  "Multimedia"           # candle                camera customdesigner
  "MultimediaWidgets"    # candle                camera customdesigner
  "OpenGL"               # candle
  "OpenGLWidgets"        # candle                camera
  "Qml"                  # candle scriptbindings
  "Quick"                # candle
  "SerialPort"           # candle
  "UiTools"              # candle scriptbindings
  "UiPlugin"             #                              customdesigner
  "Widgets"              # candle scriptbindings camera customdesigner
)

# Настройка языков локализации Qt:
# английский, испанский, французский, бразильский вариант португальского, русский
set(QT_LANG "en_US;es_ES;fr_FR;pt_BR;ru_RU")
