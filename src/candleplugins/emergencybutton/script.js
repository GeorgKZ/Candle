// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

// Vars
var appPath = app.path;
var pluginPath = script.path;
var loader = new QUiLoader();
var settings = new QSettings(pluginPath + "/settings.ini", QSettings.IniFormat);
var deviceState = -1;
var senderState = -1;
var holdSent = false;

// Ui
var uiPanel;

function init()
{
    loader.setWorkingDirectory(new QDir(pluginPath));
    loader.addPluginPath(appPath);
    loader.addPluginPath(appPath + "/libs");
    app.deviceStateChanged.connect(onAppDeviceStateChanged);
    app.senderStateChanged.connect(onAppSenderStateChanged);
    app.responseReceived.connect(onAppResponseReceived);
}

function createPanelWidget()
{
    var f = new QFile(pluginPath + "/widget.ui");

    if (f.open(QIODevice.ReadOnly)) {
        uiPanel = loader.load(f);
//      uiPanel.findChild("cmdStop").backgroundColor = new QColor(0xffff0000);

        uiPanel.findChild("cmdStop").clicked.connect(onButtonClicked);
    }
    return uiPanel;
}

function createSettingsWidget()
{
    var f = new QFile(pluginPath + "/settings.ui");

    if (f.open(QIODevice.ReadOnly)) {        
        uiSettings = loader.load(f);
        
    }
    return uiSettings;
}


function onButtonClicked()
{
    console.log("JAVA: emergencybutton::onButtonClicked()");

    app.sendCommand("!", -100, false);
    holdSent = true;
}

function onAppDeviceStateChanged(status)
{    
    console.log("JAVA: emergencybutton::onAppDeviceStateChanged()");

    deviceState = status;
    if (holdSent && (status == 5)) {
        holdSent = false;
        app.sendCommand(String.fromCharCode(24), -100, false);
    }
    if (holdSent && (status == 0)) holdSent = false;
}

function onAppSenderStateChanged(status)
{
    console.log("JAVA: emergencybutton::onAppSenderStateChanged()");
    senderState = status;
}

function onAppResponseReceived(command, index, response)
{ 
    console.log("JAVA: emergencybutton::onAppResponseReceived()");
}
