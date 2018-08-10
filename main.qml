import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import app.backend 1.0

ApplicationWindow {
    id:root
    visible: true
    width: 640
    height: 480
    title: qsTr("Kinda Web Search")

    Backendbase {
        id: backendBase
    }
    TextEdit {
        id: urlEdit
        text: backendBase.url
        verticalAlignment: Text.AlignVCenter
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 20
        anchors.leftMargin: 40
        width: 150
        onTextChanged:{
            backendBase.url = text
        }
        Rectangle {
            anchors.fill: parent
            anchors.margins: -10
            color: "transparent"
            border.width: 1
        }
    }
    TextEdit {
        id: requestEdit
        text: backendBase.searchRequest
        verticalAlignment: Text.AlignVCenter
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 70
        anchors.leftMargin: 40
        width: 150
        onTextChanged:{
            backendBase.searchRequest = text
        }
        Rectangle {
            anchors.fill: parent
            anchors.margins: -10
            color: "transparent"
            border.width: 1
        }
    }
    TextEdit {
        id: maxthreadpool
        text: backendBase.maxThreadCount;
        verticalAlignment: Text.AlignVCenter
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 120
        anchors.leftMargin: 40
        width: 150

        onTextChanged:{
            backendBase.maxThreadCount = text
        }

        Rectangle {
            anchors.fill: parent
            anchors.margins: -10
            color: "transparent"
            border.width: 1
        }
    }
    TextEdit {
        id: maxSearches
        text: backendBase.maxSearchUrlCount;
        verticalAlignment: Text.AlignVCenter
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 170
        anchors.leftMargin: 40
        width: 150

        onTextChanged:{
            backendBase.maxSearchUrlCount = text
        }
        Rectangle {
            anchors.fill: parent
            anchors.margins: -10
            color: "transparent"
            border.width: 1
        }
    }

    Button {
        text: "Start"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 210
        anchors.leftMargin: 40
        onClicked: {
            backendBase.start()
        }
    }

    ListView {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 120
        anchors.leftMargin: 340

        width: 200; height: 200

        model: backendBase.resultsList
        delegate: Rectangle {
            height: 50
            width: 200
            Text { text: modelData }
        }
    }
}
