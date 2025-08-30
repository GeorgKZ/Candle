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

# Путь к файлу значка ICO проекта
set(CUSTOM_ICON_FILE "${CMAKE_SOURCE_DIR}/src/candle/images/candle.ico")

##############################################################################
# Настройки Qt
##############################################################################

# Список необходимых для приложения плюгинов
set(QT_PLUGIN_LIST
  "accessible"
  "accessiblebridge"
  "iconengines"
  "imageformats"
  "permissions"
  "platforminputcontexts"
  "platforms"
  "platformthemes"
  "styles"
  "xcbglintegrations"
)

# Подсистемы Qt, для которых требуются переводы
set(QT_SYSTEMS "qt;qtbase;qtmultimedia;qtserialport")

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
