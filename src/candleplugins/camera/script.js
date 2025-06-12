// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

// Vars
var appPath = app.path;
var pluginPath = script.path;
var pluginName;
var loader = new QUiLoader();
var settings = new QSettings(pluginPath + "/settings.ini", QSettings.IniFormat);
var storedName;
var storedResolution;
var storedZoom;
var storedPosition;
var storedAimPosition;
var storedAimSize;
var storedAimLineWidth;
var storedAimColor;

// Ui
var uiWindow;
var uiSettings;

function init()
{
    console.log("JAVA: camera: function init()");

    loader.setWorkingDirectory(new QDir(pluginPath));

    loader.addPluginPath(appPath);
    loader.addPluginPath(appPath + "/libs");
    loader.addPluginPath(pluginPath + "/plugins")

    app.settingsLoaded.connect(onAppSettingsLoaded);
    app.settingsSaved.connect(onAppSettingsSaved);
    app.settingsAboutToShow.connect(onAppSettingsAboutToShow);
    app.settingsAccepted.connect(onAppSettingsAccepted);
    app.settingsRejected.connect(onAppSettingsRejected);
    app.settingsSetByDefault.connect(onAppSettingsDefault);
}

function createWindowWidget()
{
    console.log("JAVA: camera: function createWindowWidget()");

    var f = new QFile(pluginPath + "/widget.ui");

    if (f.open(QIODevice.ReadOnly)) {        
        uiWindow = loader.load(f);
        pluginName = uiWindow.windowTitle;
    }
    return uiWindow;
}

function getTitle()
{
    var f = new QFile(pluginPath + "/widget.ui");

    if (f.open(QIODevice.ReadOnly)) {        
        uiWindow = loader.load(f);
    }

    return uiWindow.windowTitle;
}

function createSettingsWidget()
{
    console.log("JAVA: camera: function createSettingsWidget()");

    var f = new QFile(pluginPath + "/settings.ui");

    if (f.open(QIODevice.ReadOnly)) {        
        uiSettings = loader.load(f);
        
    }
    return uiSettings;
}

function onAppSettingsSaved()
{
    console.log("JAVA: camera: function onAppSettingsSaved()");

    settings.setValue("name", uiSettings.findChild("cboCameraName").currentText);
    settings.setValue("resolution", uiSettings.findChild("cboCameraResolution").currentText);
    settings.setValue("zoom", uiSettings.findChild("txtCameraZoom").text);
    settings.setValue("position", uiSettings.findChild("txtCameraPosition").text);
    settings.setValue("aimPosition", uiSettings.findChild("txtCameraAimPosition").text);
    settings.setValue("aimSize", uiSettings.findChild("txtCameraAimSize").value);
    settings.setValue("aimLineWidth", uiSettings.findChild("txtCameraAimLineWidth").value);
    settings.setValue("aimColor", uiSettings.findChild("colCameraAimColor").colorInt);
}

function onAppSettingsLoaded()
{
    console.log("JAVA: camera: function onAppSettingsLoaded()");

    // Load settings
    uiSettings.findChild("cboCameraName").clear();
    uiSettings.findChild("cboCameraName").addItems(uiWindow.findChild("camMain").availableCameras);
//!!! если это значение определено и есть среди возможных, выбрать его 
//   uiSettings.findChild("cboCameraName").currentText = settings.value("name");
    uiSettings.findChild("cboCameraResolution").clear();
    uiSettings.findChild("cboCameraResolution").addItems(uiWindow.findChild("camMain").availableResolutions);
//!!! если это значение определено и есть среди возможных, выбрать его 
 //   uiSettings.findChild("cboCameraResolution").currentText = settings.value("resolution");
    uiSettings.findChild("txtCameraZoom").text = settings.value("zoom", "1.0");
    uiSettings.findChild("txtCameraPosition").text = settings.value("position", "0, 0");
    uiSettings.findChild("txtCameraAimPosition").text = settings.value("aimPosition", "0, 0");
    uiSettings.findChild("txtCameraAimSize").value = settings.value("aimSize", 20);
    uiSettings.findChild("txtCameraAimLineWidth").value = settings.value("aimLineWidth", 1);
    uiSettings.findChild("colCameraAimColor").colorInt = settings.value("aimColor", -65536);

    // Apply settings
    applySettings();

    // Update resolutions list
//    var r = uiSettings.findChild("cboCameraResolution").currentText;
//    uiSettings.findChild("cboCameraResolution").addItems(uiWindow.findChild("camMain").availableResolutions);
//    uiSettings.findChild("cboCameraResolution").currentText = r;

    // Connect signals/slots
    uiWindow.findChild("camMain").posChanged.connect(onPosChanged);
    uiWindow.findChild("camMain").aimPosChanged.connect(onAimPosChanged);
    uiWindow.findChild("camMain").aimSizeChanged.connect(onAimSizeChanged);
    uiWindow.findChild("camMain").aimLineWidthChanged.connect(onAimLineWidthChanged);
    uiWindow.findChild("camMain").aimColorChanged.connect(onAimColorChanged);
    uiWindow.findChild("camMain").zoomChanged.connect(onZoomChanged);
    uiSettings.findChild("cboCameraName").currentTextChanged.connect(onCameraNameChanged);
}

function onAppSettingsAboutToShow()
{
    console.log("JAVA: camera: function onAppSettingsAboutToShow()");

    storedName = uiSettings.findChild("cboCameraName").currentText;
    storedResolution = uiSettings.findChild("cboCameraResolution").currentText;
    storedZoom = uiSettings.findChild("txtCameraZoom").text;
    storedPosition = uiSettings.findChild("txtCameraPosition").text;
    storedAimPosition = uiSettings.findChild("txtCameraAimPosition").text;
    storedAimSize = uiSettings.findChild("txtCameraAimSize").value;
    storedAimLineWidth = uiSettings.findChild("txtCameraAimLineWidth").value;
    storedAimColor = uiSettings.findChild("colCameraAimColor").colorInt;
}

function onAppSettingsAccepted()
{
    console.log("JAVA: camera: function onAppSettingsAccepted()");

    applySettings();
}

function onAppSettingsRejected()
{
    console.log("JAVA: camera: function onAppSettingsRejected()");

    applySettings();
}

function onAppSettingsDefault()
{
    console.log("JAVA: camera: function onAppSettingsDefault()");
//!!! выбрать первую доступную камеру или пусто
    uiSettings.findChild("cboCameraName").currentText = "";
//!!! выбрать первое доступное разрешение или пусто
    uiSettings.findChild("cboCameraResolution").currentText = "1280x720";
    uiSettings.findChild("txtCameraZoom").text = "1.0";
    uiSettings.findChild("txtCameraPosition").text = "0, 0";
    uiSettings.findChild("txtCameraAimPosition").text = "0, 0";
    uiSettings.findChild("txtCameraAimSize").value = "20";
    uiSettings.findChild("txtCameraAimLineWidth").value = "1";
    uiSettings.findChild("colCameraAimColor").colorInt = -65536;
}

function applySettings()
{
    console.log("JAVA: camera: function applySettings()");

    // Resolution
    if (uiSettings.findChild("cboCameraResolution").currentText != "") {
        var l = uiSettings.findChild("cboCameraResolution").currentText.split("x");
        uiWindow.findChild("camMain").resolution = new QSize(parseInt(l[0]), parseInt(l[1]));
    }
    
    // Zoom
    if (uiSettings.findChild("txtCameraZoom").text == "") uiSettings.findChild("txtCameraZoom").text = "1.0";
    uiWindow.findChild("camMain").zoom = parseFloat(uiSettings.findChild("txtCameraZoom").text);

    // Scrolling position
    if (uiSettings.findChild("txtCameraPosition").text == "") uiSettings.findChild("txtCameraPosition").text = "0, 0";
    l = uiSettings.findChild("txtCameraPosition").text.split(",");
    uiWindow.findChild("camMain").pos = new QPoint(parseInt(l[0]), parseInt(l[1]));

    // Aim position
    if (uiSettings.findChild("txtCameraAimPosition").text == "") uiSettings.findChild("txtCameraAimPosition").text = "0, 0";
    l = uiSettings.findChild("txtCameraAimPosition").text.split(",");
    uiWindow.findChild("camMain").aimPos = new QPoint(parseInt(l[0]), parseInt(l[1]));

    // Aim size
    uiWindow.findChild("camMain").aimSize = parseInt(uiSettings.findChild("txtCameraAimSize").value);

    // Aim line width
    uiWindow.findChild("camMain").aimLineWidth = parseInt(uiSettings.findChild("txtCameraAimLineWidth").value);
    
    // Aim color
    uiWindow.findChild("camMain").aimColor = parseInt(uiSettings.findChild("colCameraAimColor").colorInt);

    // Update camera
    uiWindow.findChild("camMain").cameraName = uiSettings.findChild("cboCameraName").currentText;
}

function onCameraNameChanged(name)
{
    console.log("JAVA: camera: function onCameraNameChanged()");

    // Update camera
    uiWindow.findChild("camMain").cameraName = name;
    
    // Update resolutions list
//!!!    var r = uiSettings.findChild("cboCameraResolution").currentText;
    uiSettings.findChild("cboCameraResolution").clear();
    uiSettings.findChild("cboCameraResolution").addItems(uiWindow.findChild("camMain").availableResolutions);
//!!!    uiSettings.findChild("cboCameraResolution").currentText = r;
//!!! Выбрать старое, если такое есть в новом списке, или первое новое
}

function onPosChanged(pos)
{
    console.log("JAVA: camera: function onPosChanged(" + pos + ")");

    uiSettings.findChild("txtCameraPosition").text = pos.x() + ", " + pos.y();
}

function onAimPosChanged(aimPos)
{
    console.log("JAVA: camera: function onAimPosChanged(" + aimPos + ")");

    uiSettings.findChild("txtCameraAimPosition").text = aimPos.x() + ", " + aimPos.y();
}

function onAimSizeChanged(aimSize)
{
    console.log("JAVA: camera: function onAimSizeChanged()");

    uiSettings.findChild("txtCameraAimSize").setValue(aimSize);
}

function onAimLineWidthChanged(aimLineWidth)
{
    console.log("JAVA: camera: function onAimLineWidthChanged()");

    uiSettings.findChild("txtCameraAimLineWidth").setValue(aimLineWidth);
}

function onAimColorChanged(aimColor)
{
    console.log("JAVA: camera: function onAimColorChanged()");

    uiSettings.findChild("colCameraAimColor").colorInt = aimColor;
}

function onZoomChanged(zoom)
{
    console.log("JAVA: camera: function onZoomChanged()");

    uiSettings.findChild("txtCameraZoom").text = zoom.toFixed(3);
}
