// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

// Vars
var appPath = app.path;
var pluginPath = script.path;
var loader = new QUiLoader();
var settings = new QSettings(pluginPath + "/settings.ini", QSettings.IniFormat);
var buttonSize = 48;
var deviceState = -1;
var storedButtons = new Array();
var storedActions = new Array();

// Ui
//var uiPanel;
var uiWindow;
var uiSettings;

function init()
{
    loader.setWorkingDirectory(new QDir(pluginPath));
    loader.addPluginPath(appPath);
    loader.addPluginPath(appPath + "/libs");
//    loader.setLanguageChangeEnabled(true);
    
    app.settingsLoaded.connect(onAppSettingsLoaded);
    app.settingsSaved.connect(onAppSettingsSaved);
    app.settingsAboutToShow.connect(onAppSettingsAboutToShow);
    app.settingsAccepted.connect(onAppSettingsAccepted);
    app.settingsRejected.connect(onAppSettingsRejected);
    app.deviceStateChanged.connect(onAppDeviceStateChanged);
}

//function createPanelWidget()
//{
//    var f = new QFile(pluginPath + "/widget.ui");
//
//    if (f.open(QIODevice.ReadOnly)) {        
//        uiPanel = loader.load(f);
//    }
//    return uiPanel;
//}

function createWindowWidget()
{
    var f = new QFile(pluginPath + "/widget.ui");

    if (f.open(QIODevice.ReadOnly)) {        
        uiWindow = loader.load(f);
    }
    return uiWindow;
}

function createSettingsWidget()
{

console.log("JAVA: usercommands::createSettingsWidget()");

    var f = new QFile(pluginPath + "/settings.ui");

    if (f.open(QIODevice.ReadOnly)) {        
        uiSettings = loader.load(f);
        
        var t = uiSettings.findChild("tblButtons");
        t.verticalHeader().defaultAlignment = Qt.AlignCenter;
        t.setItemDelegateForColumn(0, new CodeDelegate(t));
        t.setItemDelegateForColumn(1, new IconDelegate(pluginPath, t));

        var d = new CodeDelegate(t);
        d.alignment = Qt.AlignLeft | Qt.AlignTop;
        d.adjustHeight = false;
        t.setItemDelegateForColumn(2, d);
        t.minimumHeight = t.verticalHeader().defaultSectionSize * 4 + t.horizontalHeader().height + t.frameWidth * 2;

        uiSettings.findChild("cmdUp").clicked.connect(onCmdUpClicked);
        uiSettings.findChild("cmdDown").clicked.connect(onCmdDownClicked);
        uiSettings.findChild("cmdAdd").clicked.connect(onCmdAddClicked);
        uiSettings.findChild("cmdRemove").clicked.connect(onCmdRemoveClicked);
        uiSettings.findChild("cmdRemoveAll").clicked.connect(onCmdRemoveAllClicked);
    }
    return uiSettings;
}

function onCmdAddClicked()
{

console.log("JAVA: usercommands::onCmdAddClicked()");

    var t = uiSettings.findChild("tblButtons");
    var r = t.rowCount++;

    var h = new QTableWidgetItem();
    h.setTextAlignment(Qt.AlignCenter);
    h.setText("...");

    t.setItem(r, 0, h);
    t.setItem(r, 1, new QTableWidgetItem());
    t.setItem(r, 2, new QTableWidgetItem("(Description: ...)\n(Params: ...)\n"));
//!!!
    t.verticalHeader().setFixedWidth(t.verticalHeader().sizeHint.width() + 11);
}

function onCmdRemoveClicked()
{

console.log("JAVA: usercommands::onCmdRemoveClicked()");

    var t = uiSettings.findChild("tblButtons");
    var r = t.currentRow();
    var c = t.currentColumn();

    t.removeRow(r);
    t.setCurrentCell(r <= (t.rowCount - 1) ? r : t.rowCount - 1, c);
}

function onCmdRemoveAllClicked()
{

console.log("JAVA: usercommands::onCmdRemoveAllClicked()");

    uiSettings.findChild("tblButtons").rowCount = 0;
}

function onCmdUpClicked()
{

console.log("JAVA: usercommands::onCmdUpClicked()");

    var t = uiSettings.findChild("tblButtons");
    var r = t.currentRow();
    var c = t.currentColumn();

    if (r > 0) {
        t.insertRow(r - 1);
        for (var i = 0; i < 3; i++) {
            t.setItem(r - 1, i, t.takeItem(r + 1, i));
        }
        t.removeRow(r + 1);
        t.setCurrentCell(r - 1, c);
    }
}

function onCmdDownClicked()
{

console.log("JAVA: usercommands::onCmdDownClicked()");

    var t = uiSettings.findChild("tblButtons");
    var r = t.currentRow();
    var c = t.currentColumn();

    if (r < t.rowCount - 1) {
        t.insertRow(r + 2);
        for (var i = 0; i < 3; i++) {
            t.setItem(r + 2, i, t.takeItem(r, i));
        }
        t.removeRow(r);
        t.setCurrentCell(r + 1, c);
    }
}

function onAppSettingsLoaded()
{
console.log("JAVA: usercommands::onAppSettingLoaded()");

    buttonSize = app.buttonSize();

    var b = settings.value("buttons");

console.log("JAVA: usercommands::onAppSettingLoaded(), b=" + b);

    
    restoreButtonsTable(b);
    updateButtons();
    updateActions();
}

function onAppSettingsSaved()
{
    console.log("JAVA: onAppSettingsSaved()");

    settings.setValue("buttons", storeButtonsTable());
}

function onAppSettingsAboutToShow()
{
    console.log("JAVA: onAppSettingsAboutToShow()");

    storedButtons = storeButtonsTable();
}

function onAppSettingsAccepted()
{
    updateButtons();
    updateActions();
}

function onAppSettingsRejected()
{
    console.log("JAVA: onAppSettingsRejected()");

    restoreButtonsTable(storedButtons);
}

function onAppDeviceStateChanged(status)
{

console.log("JAVA: usercommands::onAppDeviceStateChanged()");

    var t = uiSettings.findChild("tblButtons");
//    var lay = uiPanel.layout().itemAt(0).layout(); // Widget -> layout -> first layout
    var lay = uiWindow.layout().itemAt(0).layout(); // Widget -> layout -> first layout

    for (var i = 0; i < t.rowCount; i++) {
        lay.itemAt(i).widget().setEnabled(status != -1);
    }

    for (var i = 0; i < storedActions.length; i++) {
        storedActions[i].setEnabled(status != -1);
    }

    deviceState = status;
}

function onButtonClicked(button)
{
console.log("JAVA: usercommands::onButtonClicked()");

    app.sendCommands(uiSettings.findChild("tblButtons").item(button, 2).data(Qt.DisplayRole));
}

function storeButtonsTable()
{
    var t = uiSettings.findChild("tblButtons");
    var b = new Array();

console.log("JAVA: storeButtonsTable() begin with b=" + b);

    for (var i = 0; i < t.rowCount; i++) {
        var q = new Array();
        for (var j = 0; j < 3; j++) {
            var data = t.item(i, j).data(Qt.DisplayRole);
            q.push(data);
        }
        b.push(q);
    }

console.log("JAVA: storeButtonsTable() end");

    return b;
}

function restoreButtonsTable(b)
{

console.log("JAVA: usercommands::restoreButtonsTable()");

    var t = uiSettings.findChild("tblButtons");
    t.rowCount = 0;

    if (b) {
        for (var i = 0; i < b.length; i++) {
            t.insertRow(t.rowCount);
            for (var j = 0; j < b[i].length; j++) {
                var q = new QTableWidgetItem();
                q.setText(b[i][j]);
                if (j == 1) {
                    var c = new QIcon(pluginPath + "/images/" + b[i][j]);
                    q.setData(Qt.DecorationRole, c);
                }
                t.setItem(t.rowCount - 1, j, q);
            }
        }
        t.verticalHeader().setFixedWidth(t.verticalHeader().sizeHint().width() + 11);
    }
}

function updateButtons()
{
console.log("JAVA: usercommands::updateButtons()");

    var t = uiSettings.findChild("tblButtons");
//    var lay = uiPanel.layout().itemAt(0).layout(); // Widget -> layout -> first layout
    var lay = uiWindow.layout().itemAt(0).layout(); // Widget -> layout -> first layout
    var k = lay.count();
    var c = t.rowCount;

    // Delete buttons
    for (var i = 0; i < k; i++) {
        var w = lay.takeAt(0).widget();
        // if (!w.is_nil_self())
        w.deleteLater();
    }

    lay.update();

    // Create new buttons
    function onClicked(i)
    {
        return function() {onButtonClicked(i)};
    }

    for (var i = 0; i < c; i++) {
        var w = new StyledToolButton();
        w.minimumWidth = buttonSize;
        w.minimumHeight = buttonSize;
        w.sizePolicy = new QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed);
        w.iconSize = new QSize(buttonSize * 0.8, buttonSize * 0.8);

        w.icon = t.item(i, 1).data(Qt.DecorationRole);
        w.toolTip = t.item(i, 0).data(Qt.DisplayRole);
        w.clicked.connect(onClicked(i));

        w.enabled = (deviceState != -1);

        lay.addWidget(w, i / 4, i % 4);
    }

    if (c < 4) {
        for (var i = c; i < 4; i++) {
            var w = new StyledToolButton();
            w.minimumWidth = buttonSize;
            w.minimumHeight = buttonSize;
            w.sizePolicy = new QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed);
            w.enabled = false;
            lay.addWidget(w, i / 4, i % 4);    
        }
    }

    lay.update();
}

function updateActions()
{

    console.log("JAVA: usercommands::updateActions()");

    var t = uiSettings.findChild("tblButtons");

    function onTriggered(i)
    {
        return function() {onButtonClicked(i)};
    }

    var l = storedActions.length;
    var n = t.rowCount;

    for (var i = n; i < l; i++) {
        var a = storedActions.pop();
        app.removeAction(a);
        a.deleteLater();
    }
    for (var i = l; i < n; i++) {
//        var a = new QAction(qsTr("User button") + " " + (i + 1), uiPanel);
        var a = new QAction(qsTr("User button") + " " + (i + 1), uiWindow);
        a.objectName = "actUserCommandsButton" + (i + 1);
        a.triggered.connect(onTriggered(i));
        storedActions.push(a);
        app.addAction(a);    
    }

    for (var i = 0; i < storedActions.length; i++) {
        storedActions[i].setEnabled(deviceState != -1);
    }
}
