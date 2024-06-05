import QtQuick 2.15
import QtQuick.Window 2.15
import io.qt.Backend 1.0
import io.qt.DataBase 1.0
import QtQuick.Layouts
import QtQuick.Controls.Basic

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Client")

    Backend{
        id: backend
        onDataReceived: message => {
                            msgList.append("From server: " + addMsg(message));
                        }
    }
    DataBase{
        id: db
    }

    header:RowLayout{
        id: header
        spacing: 10
        width: parent.width
        Button {
            id: btn_connect
            //anchors.left: parent.left
            text: "Connect to server"
            onClicked: {
                msgList.append(addMsg("Connected to server"));
                backend.connectClicked();
                this.enabled = false;
                if(nameCli.text != ""){
                   backend.nameEditted(nameCli.text);
                }
                msgList.append(db.getTable(nameCli.text));
            }
        }

        ComboBox{
            id: cbStatus
            anchors.leftMargin: 10
            width: btn_connect.width
            model: ["None", "Available", "Busy", "Away"]
            onActivated: index => {
                             backend.statusChanged(index);
                         }
        }

        TextField{
            id: nameCli
            Layout.fillWidth: true
            padding: 10
            placeholderText: qsTr("Enter name")
            background: Rectangle {
                color: "white"
                radius: 5
                border.color: "lightgray"
            }
            onEditingFinished: {
                backend.nameEditted(nameCli.text);
            }
        }


    }

    ColumnLayout
    {
        anchors.top: parent.top
        anchors.topMargin: 5
        width: parent.width
        RowLayout {
            spacing: 10
            width: parent.width

            Button {
                id: btn_send
                height: btn_connect.height
                enabled: !btn_connect.enabled
                text: "Send"
                font.pixelSize: 15
                padding: 10
                onClicked: {
                    msgList.append("From "+ nameCli.text + ": " + addMsg(msgToSend.text));
                    backend.sendClicked(msgToSend.text);
                    db.saveNewMessage("From "+ nameCli.text + ": " + addMsg(msgToSend.text))
                    msgToSend.text = "";
                }
            }

            TextField {
                id: msgToSend
                Layout.fillWidth: true
                width: parent.width
                placeholderText: qsTr("Enter message")
                padding: 10
                font.pixelSize: 15
                background: Rectangle {
                    color: "white"
                    radius: 5
                    border.color: "lightgray"
                }
            }
        }

        ScrollView {
            id: scrollView
            TextArea {
                id: msgList
                readOnly: true
                selectByMouse : true
                font.pixelSize: 25
                background: Rectangle {
                    color: "transparent"
                }
            }
        }
    }

    //js
    function addMsg(someText)
    {
        return "[" + currentTime() + "] " + someText;
    }

    function currentTime()
    {
        var now = new Date();
        var nowString = ("0" + now.getHours()).slice(-2) + ":"
                + ("0" + now.getMinutes()).slice(-2) + ":"
                + ("0" + now.getSeconds()).slice(-2);
        return nowString;
    }
}
