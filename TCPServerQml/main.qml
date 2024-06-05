import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls.Basic 2.3
import io.qt.Backend 1.0
import io.qt.Database 1.0
import io.qt.Chatprotocol 1.0
import QtQuick.Layouts

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Server")
    //icon: "qrc:/Assets/server.png"
    property var signalPage: null
    property var signalTabButton: null
    property int idClient: 0

    Database{
        id: db
    }

    Backend {
        id: backend
        onNewClientConnectedTo: id => {
                                    var newTabButton = tabButton.createObject(bar, {text: "Client "+ id});
                                    bar.addItem(newTabButton);
                                    var newPage = tabPageComponent.createObject(stackLayout);
                                    container.append(newPage);

                                }
        onClientDisconnectedFrom: id => {
                                      bar.removeItem(bar.itemAt(id-1));
                                      var tabPage = container.get(id-1);
                                      container.remove(id-1);
                                      tabPage.destroy();
                                  }
        onClientNameChanged: name => {
                                 idClient = backend.getIdClient();
                                 signalTabButton = bar.itemAt(idClient - 1);
                                 signalTabButton.text = name;
                                 signalPage = container.get(idClient-1);
                                 signalPage.textArea.append(db.getTable(name));
                             }
        onStatusChanged: status => {
                             idClient = backend.getIdClient();
                             signalTabButton = bar.itemAt(idClient - 1);
                             switch(status){
                                 case ChatProtocol.Available:
                                 signalTabButton.back.color = "lawngreen";
                                 break;
                                 case ChatProtocol.Away:
                                 signalTabButton.back.color = "gold";
                                 break;
                                 case ChatProtocol.Busy:
                                 signalTabButton.back.color = "tomato";
                                 break;
                                 case ChatProtocol.None:
                                 signalTabButton.back.color = "skyblue";
                                 break;
                                 default:
                                 break;
                             }
                         }
        onTextMessageReceived: message => {
                                   idClient = backend.getIdClient();
                                   signalPage = container.get(idClient - 1);
                                   signalTabButton = bar.itemAt(idClient - 1);
                                   signalPage.textArea.append("From "+ signalTabButton.text + ": " + addMsg(message));
                               }
    }

    header:TabBar {
        id: bar
        width: parent.width
    }

    Component {
        id: tabButton  
        TabButton {
            property alias back: back
            Layout.preferredWidth: window.width / 5
            background: Rectangle {
                id: back
                color: "skyblue"
                radius: 5
            }
        }
    }

    Component {
        id: tabPageComponent

        // TextArea for user input
        ColumnLayout{
            property alias textArea: textArea
            anchors.margins: 10
            spacing: 10
            RowLayout{
                spacing: 10
                width: parent.width

                Button{
                    id: sendButton
                    text: "Send"
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: userInput.height
                    onClicked: {
                        backend.sendMessage(qsTr(userInput.text), bar.currentIndex);
                        textArea.append("From Server: " + addMsg(userInput.text));
                        db.saveNewMessage("From Server" + addMsg(userInput.text));
                        userInput.text = "";
                    }
                    font.pixelSize: 15
                    padding: 10
                }
                TextField{
                    id: userInput
                    Layout.fillWidth: true
                    placeholderText: qsTr("Enter message")
                    font.pixelSize: 15
                    padding: 10
                    background: Rectangle {
                        color: "white"
                        radius: 5
                        border.color: "lightgray"
                    }
                }
            }

            ScrollView{
                TextArea {
                    id: textArea
                    text: "Connection succeeded\n -------"
                    readOnly: true
                    font.pixelSize: 25
                    background: Rectangle {
                        color: "transparent"
                    }
                }
            }
        }
    }

    StackLayout {
        id: stackLayout
        anchors.fill: parent
        //width: parent.width
        currentIndex: bar.currentIndex
        Repeater
        {
            model: ObjectModel
            {
                id: container
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
