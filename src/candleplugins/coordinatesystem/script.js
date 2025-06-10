// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

//script.importExtension("qt.core");
//script.importExtension("qt.gui");
//script.importExtension("qt.widgets");
//script.importExtension("qt.custom");
//script.importExtension("qt.uitools");

// Vars
var appPath = app.path;
var pluginPath = script.path;
var loader = new QUiLoader();
var settings = new QSettings(pluginPath + "/settings.ini", QSettings.IniFormat);
var deviceState = -1;
var senderState = -1;
var currentCS = "G54";
var currentOffsets = "";

// Ui
var uiPanel;
var uiSettings;

function init()
{
    loader.setWorkingDirectory(new QDir(pluginPath));
    loader.addPluginPath(appPath);
    loader.addPluginPath(appPath + "/libs");

    app.deviceStateChanged.connect(onAppDeviceStateChanged);
    app.senderStateChanged.connect(onAppSenderStateChanged);
    app.responseReceived.connect(onAppResponseReceived);
    app.settingsLoaded.connect(onAppSettingsLoaded);
}

function createPanelWidget()
{
    var f = new QFile(pluginPath + "/widget.ui");

    function onCsClicked(cs)
    {
        return function() {app.sendCommands(cs);};
    }

    function onZeroClicked(a)
    {
        return function() {app.sendCommand("".concat("G10 L20 P", currentCS.slice(-1) - 3, " ", a));}
    }

    if (f.open(QIODevice.ReadOnly)) {
        uiPanel = loader.load(f);

        for (var i = 54; i <= 57; i++) {
            uiPanel.findChild("cmdG" + i).clicked.connect(onCsClicked("G" + i));
        }

        uiPanel.findChild("cmdX0").clicked.connect(onZeroClicked("X0"));
        uiPanel.findChild("cmdY0").clicked.connect(onZeroClicked("Y0"));
        uiPanel.findChild("cmdZ0").clicked.connect(onZeroClicked("Z0"));
        uiPanel.findChild("cmdAll0").clicked.connect(onZeroClicked("X0 Y0 Z0"));
    }
    return uiPanel;
}

function onAppSettingsLoaded()
{
    var u = app.settings.units;
    var b = u ? 999 : 9999;

    uiPanel.findChild("txtOffsetX").decimals = u ? 4 : 3;
    uiPanel.findChild("txtOffsetY").decimals = u ? 4 : 3;
    uiPanel.findChild("txtOffsetZ").decimals = u ? 4 : 3;

    uiPanel.findChild("txtOffsetX").mimimum = -b;
    uiPanel.findChild("txtOffsetX").maximum = b;
    uiPanel.findChild("txtOffsetY").mimimum = -b;
    uiPanel.findChild("txtOffsetY").maximum = b;
    uiPanel.findChild("txtOffsetZ").mimimum = -b;
    uiPanel.findChild("txtOffsetZ").maximum = b;
}

function onAppDeviceStateChanged(status)
{
    uiPanel.setEnabled((status == 1) && (senderState == 4));
    
    deviceState = status;
}

function onAppSenderStateChanged(status)
{
    uiPanel.setEnabled((status == 4) && (deviceState == 1));

    senderState = status;
}

function onAppResponseReceived(command, index, response)
{
    function displayOffsets(r) {
        var gx = new RegExp(currentCS + ":([\\d\\.\\-]+),([\\d\\.\\-]+),([\\d\\.\\-]+)");
        var s = r.match(gx);
        if (s) {
            for (var i = 0; i < s.length; i++) {
                uiPanel.findChild("txtOffsetX").value = parseFloat(s[1]);
                uiPanel.findChild("txtOffsetY").value = parseFloat(s[2]);
                uiPanel.findChild("txtOffsetZ").value = parseFloat(s[3]);
            }
        }
    }

    if (command == "$G") {
        var rx = new RegExp("G5[4-9]");
        var s = response.match(rx);
        if (s) {
            uiPanel["cmd" + s[0]].checked = true;
            if (s[0] != currentCS) {
                currentCS = s[0];
                displayOffsets(currentOffsets);
            }
        }
    }

    if (command == "$#") {
        currentOffsets = response;
        displayOffsets(currentOffsets);
    }
}
